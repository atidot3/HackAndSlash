#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDownloader/QDownloader.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    state = LAUNCHER_STATE::UDPDATE;
    /*setStyleSheet("background:transparent;");
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowFlags( Qt::FramelessWindowHint );*/
    ui->setupUi(this);
}
void MainWindow::SetWebLauncher(QString url)
{
    ui->webView->setUrl(url);
}

void MainWindow::Start(QDownloader *tmp)
{
    this->setFixedSize(this->maximumSize());
    ui->pushButton->setEnabled(false);
    ui->pushButton->setText("CHECK");
    down = tmp;
}
void MainWindow::UpdateRepairStatut(int current, int max)
{
    QString currentFile = QString::number(current);
    currentFile.append(" / ");
    currentFile.append(QString::number(max));
    ui->label_2->setText(currentFile);
    if (current > 0)
    {
        ui->label_3->setText(QString::number((current/max) * 100));
        ui->progressBar->setValue((current/max) * 100);
    }
}
void MainWindow::ChangeToReady()
{
    ui->pushButton->setEnabled(true);
    ui->pushButton->setText("PLAY");
    ui->progressBar->setValue(100);
    ui->label->hide();
    ui->label_2->hide();
    ui->label_3->hide();
}
void MainWindow::ChangeToUpdating()
{
    ui->pushButton->setEnabled(true);
    ui->pushButton->setText("INSTALLATION");
    ui->label->hide();
    ui->label_2->hide();
    ui->label_3->hide();
}
void MainWindow::ChangeToRepair()
{
    ui->progressBar->setValue(0);
    ui->label->show();
    ui->label_2->show();
    ui->label_3->show();
    ui->pushButton->setEnabled(false);
    ui->pushButton->setText("REPAIR");
    UpdateRepairStatut(0,0);
    //down->OnEventRepairGame();
}
void MainWindow::ChangeToUninstall()
{
    ui->progressBar->setValue(0);
    ui->label->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->pushButton->setEnabled(false);
    ui->pushButton->setText("UNINSTALL");
}

void MainWindow::ChangeState(LAUNCHER_STATE _state)
{
    state = _state;
    switch (state)
    {
        case CHECK:
        {
            ChangeToUpdating();
            break;
        }
        case UDPDATE:
        {
            ChangeToUpdating();
            break;
        }
        case REPAIR:
        {
            ChangeToRepair();
            break;
        }
        case START:
        {
            ChangeToReady();
            break;
        }
        case UNINSTALL:
        {
            ChangeToUninstall();
            break;
        }
    }
}
void MainWindow::UpdateProgressBar(int value)
{
    ui->progressBar->setValue(value);
}
void MainWindow::DownloadDone()
{
    ui->progressBar->setValue(100);
    ui->label->hide();
    ui->label_2->hide();
}
void MainWindow::SetFileToDownload(QString str)
{
    ui->label_2->setText(str);
}
void MainWindow::SetFileToDownloadNumber(QString str)
{
    ui->label_3->setText(str);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionRepair_Game_triggered()
{
    ChangeToRepair();
}

void MainWindow::on_actionExit_triggered()
{
    delete down;
    exit(0);
}

void MainWindow::on_actionRemove_installation_triggered()
{
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Uninstall", "Are you sure you want to uninstall the entire game folder ?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes)
      {
        qDebug() << "Yes was clicked";
        ChangeToUninstall();
        down->onUninstall();
      }
      else
      {
        qDebug() << "Yes was *not* clicked";
      }
}
void MainWindow::on_pushButton_clicked()
{
    switch (state)
    {
        case UDPDATE:
        {
            ui->progressBar->setValue(0);
            ui->label->show();
            ui->label_2->show();
            ui->label_3->show();
            ui->label->setText("File downloaded: ");
            ui->pushButton->setEnabled(false);
            down->ProcessUpdate();
            break;
        }
        case START:
        {
            QString exe = QDir::currentPath();
            exe.append("HackAndSlash.exe");
            QFile file(exe);
            if(file.open(QIODevice::ReadOnly))
            {
                system(exe.toStdString().c_str());
            }
            else
            {
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, "Error", "executable file not found, do you want to repair the game ?\nIt's possible for the Launcher to freeze for some times, don't close it.",
                                          QMessageBox::Yes|QMessageBox::No);
                if (reply == QMessageBox::Yes)
                {
                    ChangeToRepair();
                    down->ProcessUpdate();
                }
            }
            break;
        }
    }
}

