#include <QCoreApplication>
#include <Qthread>
#include <QTextCodec>
#include <QObject>
#include <QDebug>
#include "master.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("866"));
    Master waiter;
    waiter.startAll();
    return a.exec();
}
