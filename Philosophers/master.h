#ifndef MASTER_H
#define MASTER_H

#include <QObject>
#include <QThread>
#include <QTimer>

#include "philosopher.h"
#include "shared.h"
#include "config.h"

//Master class definition. It use signals, and must be successor of QObject
class Master: public QObject
{
    Q_OBJECT
public:
    static const int Philosopher_AMOUNT = CONFIG_Philospher_AMOUNT; //number of threads created
    Master();  //Constructor
    ~Master(); //Destructor
    void startAll(); //will trigger a barrier, allowing all philosophers to live
    bool checkPhils(); // call this function to check philosopher status and logic consistanty
                       //(функция для проверки статуса философов и правильности логики работы потоков)
private:
    QThread* threads[Philosopher_AMOUNT]; //threads for Philosophers (массив указателей на объекты класса QThread)
    Philosopher* philosophers[Philosopher_AMOUNT]; // (массив указателей на объекты класса Philosopher)
    Shared shared;  // data shared for all philosophers
    QTimer* timer; // Timer to call periodic events, like logic state checks.
    QString inOrder; //data of ordered signals
    int inOrderCount; //Count for ordered signals
public slots:
   void orderString(QString);
   void update(void); // timer will emit signal to this slot every PERIODIC_TIMEOUT_MSEC
 signals:
   void start(); //startAll() will emit this signal to allow data processing.

};

#endif // MASTER_H
