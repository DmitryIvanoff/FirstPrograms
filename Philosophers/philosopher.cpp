#include <QThread>
#include <QDebug>
#include "philosopher.h"
#include "config.h"

// - - CONSTRUCTOR - -
Philosopher::Philosopher(int n, Shared *shared)
{
  this->name=n;               //name is a number
  this->shared = shared;      //we use 'this->shared' language feature to set this object property named 'shared to
}                             //value of parameter named 'shared'
// - - DESTRUCTOR - -
Philosopher::~Philosopher()
{
}
// - - PROCESS - -
void Philosopher::process()
{
    emit order(QString ("%1").arg(name));
    // - - PROBLEMS WITH LOGICS STARTS HERE - -
    while (true)
    {
        status = THINKING;
        QThread::msleep(THINKING_DELAY_MSEC);        //философ думает
        status = HUNGRY;
        shared->TakeForks(name);   //пробует взять вилку или блокируется
        status = EATING;
        QThread::msleep(EATING_DELAY_MSEC); //философ ест
        shared->PutForks(name);
        status = THINKING;;
        QThread::msleep(WAITING_DELAY_MSEC); //to keep CPU cool
    }
    // - - PROBLEMS WITH LOGICS ENDS HERE - -
    emit finished();
}

