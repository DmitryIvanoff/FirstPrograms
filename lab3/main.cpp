#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(640,480);
    w.setWindowTitle("MusicSiteParsing");
    w.setWindowIcon(QIcon(":/icon.png"));
    w.show();
    return a.exec();
}
