#ifndef QDOWNLOADER_H
#define QDOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QStringList>
#include <QDir>
#include "../Config/config.h"
#include "../mainwindow.h"
#include <QQueue>
#include <QTimer>
#include <QUiLoader>

class Config;

class QDownloader : public QObject
{
    Q_OBJECT
public:
    explicit QDownloader(QObject *parent = 0);
    virtual ~QDownloader();
    void Start();

    void setFile(QString fileURL, QString savePath);
    void DownloadManifest();
    void setFileManifest(QString fileURL, QString savePath, QString filename);
    void append(const QString &url, const QString &name);
    void OnEventRepairGame();
    void onUninstall();
    void ProcessUpdate();
public:
    MainWindow window;
private:
    QNetworkAccessManager   *manager;
    QNetworkReply           *reply;
    QFile                   *file;
    Config                  *conf;
    QString                 manifest;
    bool                    customPath;
    QQueue<QString> downloadQueue;
    QQueue<QString> FileNameQueue;
    QNetworkReply *currentDownload;
    QFile output;
    QTime downloadTime;

    int downloadedCount;
    int totalCount;
private slots:
    void startNextDownload();

    void onDownloadProgress(qint64,qint64);
    void onFinished(QNetworkReply*);
    void onReadyRead();
    void onReplyFinished();
    void onReplyFinishedManifest();
signals:
    void finished();
};

#endif // QDOWNLOADER_H
