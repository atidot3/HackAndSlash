#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

namespace Ui {
class MainWindow;
}

class Config;
class QDownloader;

enum LAUNCHER_STATE
{
    CHECK,
    UDPDATE,
    REPAIR,
    START,
    UNINSTALL,
    ERROR
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Start(QDownloader *tmp);
    void UpdateProgressBar(int value);
    void SetFileToDownload(QString str);
    void SetFileToDownloadNumber(QString str);
    void DownloadDone();
    void ChangeToRepair();
    void ChangeToUpdating();
    void ChangeToReady();
    void ChangeState(LAUNCHER_STATE _state);
private slots:
    void on_actionRepair_Game_triggered();

    void on_actionExit_triggered();

    void on_actionRemove_installation_triggered();

    void on_pushButton_clicked();

private:
    QDownloader *down;
    Ui::MainWindow *ui;
public:
    LAUNCHER_STATE state;
    void UpdateRepairStatut(int currentFile, int MaxFile);
    void ChangeToCheck();
    void ChangeToUninstall();
    void SetWebLauncher(QString url);
};

#endif // MAINWINDOW_H
