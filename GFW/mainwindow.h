#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myitem.h"
#include <QtGui>
#include <QtCore>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMessageBox>
#include <QColorDialog>
#include <cstring>
#include <cstdio>
using namespace std;
namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    virtual bool eventFilter(QObject *, QEvent *);
private slots:

    void on_actionSave_triggered();

    void on_comboBox_4_activated(int index);

    void on_comboBox_activated(int index);

    void setColor(QColor);//задает цвет для рисования в myItem.picture

    void on_commandLinkButton_clicked();

    void on_lineEdit_editingFinished();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    MyItem* item;
    QColorDialog* palitra;
    void gfCleanupScene();
    bool gfInitScene();
    void gfOnLMouseClick( int x, int y );
    void gfOnMouseMove(int x, int y );
    void gfOnRMouseClick( int x, int y );
    void gfOnLMouseRelease(int x,int y);
    void gfOnKeyDown(int);
    QAction* SavePicture;
    QPointF p;
    QTimer* timer;



};

#endif // MAINWINDOW_H
