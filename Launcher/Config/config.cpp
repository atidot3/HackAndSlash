#include "config.h"

Config::Config(QObject *parent) : QObject(parent)
{
    totalfile = 0;
}
bool Config::isFileExist()
{
    QString path = QDir::currentPath();
    path.append("/LauncherManifest.txt");
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Text))
    {
        QString Newpath = QDir::currentPath();
        Newpath.append("/LauncherManifestTmp.txt");
        QFile::rename(Newpath, path);
        qDebug() << "file not found" << path;
        return false;
    }
    manifest = file.readAll();
    file.close();
    return true;
}
void Config::RenameManifest()
{
    QString path = QDir::currentPath();
    path.append("/LauncherManifest.txt");
    QFile::remove(path);
    QString Newpath = QDir::currentPath();
    Newpath.append("/LauncherManifestTmp.txt");
    QFile::rename(Newpath, path);
}
bool Config::IsManifestEmpty()
{
    if (manifest.isEmpty())
    {
        QString path = QDir::currentPath();
        path.append("/LauncherManifest.txt");
        QFile::remove(path);
        QString Newpath = QDir::currentPath();
        Newpath.append("/LauncherManifestTmp.txt");
        QFile::rename(Newpath, path);
        qDebug() << "file is empty" << path;
        return false;
    }
    return true;
}
bool    Config::LoadXml()
{
    QString path = QDir::currentPath();
    path.append("/config.xml");
    QFile file(path);
    bool ok = false;
    if(file.open(QIODevice::ReadOnly))
    {
        xmlReader.setDevice(&file);
        xmlReader.readNextStartElement();
        if (xmlReader.readNextStartElement() && xmlReader.name() == "Patch_IP")
        {
            server = xmlReader.readElementText();
            ok = true;
        }
        if (xmlReader.readNextStartElement() && xmlReader.name() == "LauncherUrl")
        {
            LauncherUrl = xmlReader.readElementText();
            ok = true;
        }
        return ok;
    }
    return false;
}

bool    Config::LoadConfig()
{
    if (isFileExist() == false)
        return false;
    if (IsManifestEmpty() == false)
        return false;
    // GET THE MD5 FROM LOCAL FILE
    QString fileLocalPath = QDir::currentPath();
    fileLocalPath.append("/LauncherManifest.txt");
    QByteArray dataLocal;
    QFile FileLocal(fileLocalPath);
    if (FileLocal.open( QIODevice::ReadOnly ))
    {
        dataLocal = FileLocal.readAll();
    }
    else
        return false;
    QByteArray localFile = QCryptographicHash::hash(dataLocal,QCryptographicHash::Sha1).toHex();
    // GET THE MD5 FROM DOWNLOADED FILE
    QString fileDownloadedPath = QDir::currentPath();
    fileDownloadedPath.append("/LauncherManifestTmp.txt");
    QByteArray dataDownloaded;
    QFile FileDownloaded(fileDownloadedPath);
    if (FileDownloaded.open( QIODevice::ReadOnly ))
    {
        dataDownloaded = FileDownloaded.readAll();
    }
    else
        return false;
    QByteArray downloadedFile = QCryptographicHash::hash(dataDownloaded,QCryptographicHash::Sha1).toHex();

    qDebug() << localFile << downloadedFile;


    if (localFile == downloadedFile)
    {
        FileLocal.close();
        FileDownloaded.close();
        return true;
    }
    FileLocal.close();
    FileDownloaded.close();

    RenameManifest();
    return false;
}
void    Config::ParseManifest(QDownloader *down)
{
    downloader = down;
    QString path = QDir::currentPath();
    path.append("/LauncherManifest.txt");
    QFile file(path);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream flux(&file);
        while(!flux.atEnd())
        {
            ParseStringManifest(flux.readLine());
        }
    }
    else
    {
        down->window.state = LAUNCHER_STATE::ERROR;
        down->DownloadManifest();
    }
    file.close();
}
void    Config::UninstallParseManifest(QDownloader *down)
{
    downloader = down;
    QString path = QDir::currentPath();
    path.append("/LauncherManifest.txt");
    QFile file(path);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream flux(&file);
        while(!flux.atEnd())
        {
            ParseStringManifestUninstall(flux.readLine());
        }
    }
    else
    {
        down->window.state = LAUNCHER_STATE::ERROR;
        down->DownloadManifest();
        qDebug() << path << " cant be opended";
    }
    file.close();
    downloader->window.ChangeToUpdating();
}

QString Config::GetPathToPlace(QString str)
{
    QStringList filePathList = str.split('\\');
    int len = filePathList.count();
    QString fileName = "";
    for(int i = 0; i < len - 1; i++)
    {
         fileName.append(filePathList.at(i));
         fileName.append("/");
    }
    return fileName;
}

void    Config::ParseStringManifest(QString str)
{
    QRegExp rx("[:]");// match a comma or a space
    QStringList list = str.split(rx, QString::SkipEmptyParts);
    QString name = list.at(0);
    QString md5 = list.at(1);
    //qDebug() << "md5:" << md5 << "from file:" << name;

    QStringList filePathList = name.split('\\');
    QString fileName = filePathList.at(filePathList.count() - 1);

    QString path = QDir::currentPath();

    for (int i = 0; i < filePathList.count(); i++)
    {
        path.append(filePathList.at(i));
        if (i != filePathList.count() - 1)
            path.append("/");

        if (i == filePathList.count() - 1) // THIS IS THE FILE
        {
            QFile file(path);
            if(!file.open(QIODevice::ReadOnly)) // FILE DOESNT EXIST
            {
                QString Dlpath = server;
                Dlpath.append(name);
                QString pathTodownload = GetPathToPlace(str);
                QString DlpathToPlace = QDir::currentPath();
                DlpathToPlace.append(pathTodownload);
                Dlpath.replace('\\', '/');
                //qDebug() << "directory:" << DlpathToPlace;
                //qDebug() << "file:" << Dlpath;
                downloader->append(Dlpath, DlpathToPlace);
            }
            else // check MD5 for download or not
            {
                QByteArray dataLocal;
                QFile FileLocal(path);
                if (FileLocal.open( QIODevice::ReadOnly ))
                {
                    dataLocal = FileLocal.readAll();
                    QByteArray localFile = QCryptographicHash::hash(dataLocal,QCryptographicHash::Md5).toHex();
                    localFile = localFile.toUpper();
                    if (localFile != md5)
                    {
                        QString Dlpath = server;
                        Dlpath.append(name);
                        QString pathTodownload = GetPathToPlace(str);
                        QString DlpathToPlace = QDir::currentPath();
                        DlpathToPlace.append(pathTodownload);
                        Dlpath.replace('\\', '/');
                        downloader->append(Dlpath, DlpathToPlace);
                    }
                }
            }
            //qDebug() << path;
        }
        else // this is the directory
        {
            QDir dir(path);
            if(dir.exists(path) == false)
            {
               // qDebug() << "creating directory" << path;
            }
        }
    }
}

void    Config::ParseStringManifestUninstall(QString str)
{
    QRegExp rx("[:]");// match a comma or a space
    QStringList list = str.split(rx, QString::SkipEmptyParts);
    QString name = list.at(0);
    QString md5 = list.at(1);

    QStringList filePathList = name.split('\\');
    QString path = QDir::currentPath();
    for (int i = 0; i < filePathList.count(); i++)
    {
        path.append(filePathList.at(i));
        if (i != filePathList.count() - 1)
        {
            path.append("/");
            QDir dir(path);
            if(dir.exists(path))
            {
                if (filePathList.at(i) != "")
                {
                    QDir DirToRemove(path);
                    DirToRemove.removeRecursively();
                }
            }
        }
        else
        {
            QFile file(path);
            file.remove();
        }
    }
}
