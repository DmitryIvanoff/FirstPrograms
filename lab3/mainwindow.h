#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QNetworkAccessManager>
#include <QtCore>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QFile>
#include <QProgressBar>
#include <QMessageBox>
#include <QtXmlPatterns>
#include "musicitem.h"
//#include <QtQml>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QNetworkAccessManager* man;
    Ui::MainWindow *ui;
    QNetworkReply* reply;
    QNetworkRequest* request;
    QFile page;
    QVector<MusicItem*> items;
    QProgressBar* m_pb;
    void parse(QFile*);
private slots:
    void readyRead();
    void onFinished();
    void onDownloaded();
    void slotDownloadProgress(qint64,qint64);
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
};



#endif // MAINWINDOW_H
