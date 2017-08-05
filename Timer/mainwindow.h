#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTime>
#include <QTimer>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void timeout();

    void on_pushButton_3_clicked();

private:
    QIcon icon;
    void StartCount();
    Ui::MainWindow *ui;
    QTime* time;
    QTimer* timer;
};

#endif // MAINWINDOW_H
