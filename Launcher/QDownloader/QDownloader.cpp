#include "qdownloader.h"

QDownloader::QDownloader(QObject *parent) :
    QObject(parent)
{
    manager = new QNetworkAccessManager;
    downloadedCount = 0;
    totalCount = 0;
    window.show();
    Start();
    window.Start(this);
}
QDownloader::~QDownloader()
{
    manager->deleteLater();
    delete conf;
}
void QDownloader::Start()
{
    conf = new Config();
    if (conf->LoadXml() == false)
    {
        QMessageBox msgBox;
        msgBox.setText("config.xml not found.");
        msgBox.exec();
        exit(-1);
    }
    manifest = conf->server;
    manifest.append("LauncherManifest.txt");
    window.SetWebLauncher(conf->LauncherUrl);
    DownloadManifest();
}
void QDownloader::startNextDownload()
{
    if (downloadQueue.isEmpty())
    {
        printf("%d/%d files downloaded successfully\n", downloadedCount, totalCount);
        QString line = QString::number(downloadedCount);
        line.append(" / ");
        line.append(QString::number(totalCount));
        window.SetFileToDownloadNumber(line);
        window.DownloadDone();
        totalCount = downloadedCount = 0;
        window.ChangeState(LAUNCHER_STATE::START);
        emit finished();
        return;
    }

    QString url = downloadQueue.dequeue();
    QString filename = FileNameQueue.dequeue();

    /*output.setFileName(filename);
    if (!output.open(QIODevice::WriteOnly))
    {
        startNextDownload();
        return;                 // skip this download
    }
    QUrl urlBis(url);
    qDebug() << url << urlBis << "??????";
    QNetworkRequest request;
    request.setUrl(urlBis);
    currentDownload = manager->get(request);
    connect(currentDownload, SIGNAL(downloadProgress(qint64,qint64)),
            SLOT(downloadProgress(qint64,qint64)));
    connect(currentDownload, SIGNAL(finished()),
            SLOT(downloadFinished()));
    connect(currentDownload, SIGNAL(readyRead()),
            SLOT(downloadReadyRead()));

    // prepare the output*/
    setFile(url, filename);
    downloadTime.start();
}
void QDownloader::append(const QString &url, const QString &name)
{
    if (downloadQueue.isEmpty())
    {
        QTimer::singleShot(0, this, SLOT(startNextDownload()));
    }

    downloadQueue.enqueue(url);
    FileNameQueue.enqueue(name);
    ++totalCount;
    QString line = QString::number(downloadedCount);
    line.append(" / ");
    line.append(QString::number(totalCount));
    window.SetFileToDownloadNumber(line);
}
void QDownloader::DownloadManifest()
{
    QString path = QDir::currentPath();
    path.append("/");
    setFileManifest(manifest, path, "LauncherManifestTmp.txt");
}
void QDownloader::setFileManifest(QString fileURL, QString savePath, QString fileName)
{
    QString RemovePath = QDir::currentPath();
    RemovePath.append(savePath);
    RemovePath.append(fileName);

    QFile *RemovedPath = new QFile(RemovePath);
    RemovedPath->remove();
    RemovedPath->close();

    QDir dir(savePath);
    if(dir.exists(savePath) == false)
       dir.mkdir(savePath);
    savePath.append(fileName);


    QNetworkRequest request;
    request.setUrl(QUrl(fileURL));
    reply = manager->get(request);

    file = new QFile;
    file->setFileName(savePath);
    file->open(QIODevice::WriteOnly);

    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(onDownloadProgress(qint64,qint64)));
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(onFinished(QNetworkReply*)));
    connect(reply,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
    connect(reply,SIGNAL(finished()),this,SLOT(onReplyFinishedManifest()));
}
void QDownloader::setFile(QString fileURL, QString savePath)
{
    bool exist = QDir(savePath).exists();
    if (exist == false)
    {
        QDir().mkpath(savePath);
    }

    QString filePath = fileURL;
    QStringList filePathList = filePath.split('/');
    QString fileName = filePathList.at(filePathList.count() - 1);
    savePath.append(fileName);

    QNetworkRequest request;
    request.setUrl(QUrl(fileURL));
    reply = manager->get(request);

    file = new QFile;
    file->setFileName(savePath);
    file->open(QIODevice::WriteOnly);

    qDebug() << "file url" << fileURL << "savepath" << savePath;
    window.UpdateProgressBar(0);
    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(onDownloadProgress(qint64,qint64)));
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(onFinished(QNetworkReply*)));
    connect(reply,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
    connect(reply,SIGNAL(finished()),this,SLOT(onReplyFinished()));
}
void QDownloader::onDownloadProgress(qint64 bytesRead,qint64 bytesTotal)
{
    double speed = bytesRead * 1000.0 / downloadTime.elapsed();
    QString unit;
    if (speed < 1024)
    {
        unit = "bytes/sec";
    } else if (speed < 1024*1024)
    {
        speed /= 1024;
        unit = "kB/s";
    }
    else
    {
        speed /= 1024*1024;
        unit = "MB/s";
    }
    //qDebug() << speed << unit << bytesRead << "/" << bytesTotal;
    float moRead = bytesRead / 1024 / 1024;
    float moTotal = bytesTotal / 1024 / 1024;
    if (bytesRead > 0)
    {
       float downloaded_Size = (float)moRead;
       float total_Size = (float)moTotal;
       float progress = (downloaded_Size/total_Size) * 100;
       window.UpdateProgressBar(progress);
       QString current = QString::number(moRead);
       current.append(" mo / ");
       current.append(QString::number(moTotal));
       current.append(" mo  ");
       current.append(QString::number((moRead / moTotal) * 100));
       current.append(" %");
       current.append("   ");
       current.append(QString::number(speed));
       current.append(unit);
       window.SetFileToDownload(current);
    }
}
void QDownloader::onFinished(QNetworkReply * reply)
{
    switch(reply->error())
    {
        case QNetworkReply::NoError:
        {
            //qDebug("file is downloaded successfully.");
        }break;
        default:{
            qDebug(reply->errorString().toLatin1());
        };
    }
    if(file->isOpen())
    {
        file->close();
        file->deleteLater();
    }
}
void QDownloader::onReadyRead()
{
    file->write(reply->readAll());
}
void QDownloader::onReplyFinishedManifest()
{
    if(file->isOpen())
    {
        file->close();
        file->deleteLater();
    }
    QString path = QDir::currentPath();
    path.append("/LauncherManifest.txt");

    /*QFile *RemovedPath = new QFile(path);
    if (RemovedPath->exists())
    {
        RemovedPath->remove();
        RemovedPath->close();
        window.ChangeState(LAUNCHER_STATE::UDPDATE);
    }*/
    if (conf->LoadConfig() == false)
    {
        if (window.state == LAUNCHER_STATE::ERROR)
        {
            ProcessUpdate();
        }
        else
        {
            window.ChangeState(LAUNCHER_STATE::UDPDATE);
        }
    }
    else
        window.ChangeState(LAUNCHER_STATE::START);
}

void QDownloader::ProcessUpdate()
{
    conf->ParseManifest(this);
}

void QDownloader::onReplyFinished()
{
    file->close();
    if (reply->error())
    {
        // download failed
        fprintf(stderr, "Failed: %s\n", qPrintable(reply->errorString()));
    } else
    {
        ++downloadedCount;
    }
    QString line = QString::number(downloadedCount);
    line.append(" / ");
    line.append(QString::number(totalCount));
    window.SetFileToDownloadNumber(line);
    reply->deleteLater();
    startNextDownload();
}

void QDownloader::OnEventRepairGame()
{
    QString path = QDir::currentPath();
    path.append("/LauncherManifest.txt");

    QFile *RemovedPath = new QFile(path);
    RemovedPath->remove();
    RemovedPath->close();
    path = QDir::currentPath();
    path.append("/LauncherManifestTmp.txt");

    RemovedPath = new QFile(path);
    RemovedPath->remove();
    RemovedPath->close();

    window.state = LAUNCHER_STATE::REPAIR;

    DownloadManifest();
}
void QDownloader::onUninstall()
{
    conf->UninstallParseManifest(this);
    QString path = QDir::currentPath();
    path.append("/LauncherManifest.txt");

    QFile *RemovedPath = new QFile(path);
    RemovedPath->remove();
    RemovedPath->close();
    window.ChangeState(LAUNCHER_STATE::UDPDATE);
}
