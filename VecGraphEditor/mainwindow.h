#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include "myellipse.h"
#include "myline.h"
#include "myrect.h"
#include <QGraphicsScene>
#include <QLabel>
#include <QScrollBar>
#include <math.h>
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
    virtual void mouseMoveEvent(QMouseEvent* me);
    // virtual void mousePressEvent(QMouseEvent*);
    bool eventFilter(QObject *, QEvent *);
private slots:
    void selectedGraphicsItem(QAbstractGraphicsShapeItem*);

    void on_commandLinkButton_2_clicked();

    void on_commandLinkButton_3_clicked();

    void on_commandLinkButton_4_clicked();

    void on_commandLinkButton_clicked();
    void deleteItem(QGraphicsItem*);

    void on_commandLinkButton_5_clicked();
    void setX1(QString);
    void setY1(QString);
    void setX2(QString);
    void setY2(QString);
    void setW(QString);
    void setH(QString);
    void setColor(QColor);
signals:
private:
    QColorDialog* palitra;
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    MyLine* line;
    MyRect* rec;
    MyEllipse* ellipse;
    QLabel* lbl_y;
    QLabel* lbl_x;
    QCursor* cursor;
    QAbstractGraphicsShapeItem* currentItem;
    QAbstractGraphicsShapeItem* selectedItem;
};


#endif // MAINWINDOW_H
