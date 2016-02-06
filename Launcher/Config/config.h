#ifndef CONFIG_H
#define CONFIG_H

#include <QMainWindow>
#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QDir>
#include <QXmlStreamReader>

#include "../QDownloader/QDownloader.h"

class QDownloader;

class Config : public QObject
{
    Q_OBJECT
public:
    explicit Config(QObject *parent = 0);
    bool    LoadConfig();
    void    ParseStringManifest(QString str);
    void    ParseManifest(QDownloader *down);
    bool    isFileExist();
    void    RenameManifest();
    bool    IsManifestEmpty();
    QString GetPathToPlace(QString str);
    bool LoadXml();
signals:
private:
    QString     manifest;
    QDownloader *downloader;

    QXmlStreamReader xmlReader;
public:
    int totalfile;
    QString server;
    QString LauncherUrl;
    void ParseStringManifestUninstall(QString str);
    void UninstallParseManifest(QDownloader *down);
public slots:
};

#endif // CONFIG_H
