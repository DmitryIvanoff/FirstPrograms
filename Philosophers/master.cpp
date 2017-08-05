#include <QDebug>
#include <QString>
#include <QDateTime>
#include "master.h"
#include "philosopher.h"
Master::Master()
{
   inOrder = "";
   inOrderCount = 0;
   //Creating, configuring and starting all threads
   for (int i=0;i<Philosopher_AMOUNT;i++)
   {
      threads[i]=new QThread;
      philosophers[i]=new Philosopher(i,&shared);
      philosophers[i]->moveToThread(threads[i]); //move pointer on object philosopher[i] to thread threads[i];
       //order messages. For example to get order to start
      connect(philosophers[i],SIGNAL(order(QString)),this,SLOT(orderString(QString)));
      connect(this,SIGNAL(start()),philosophers[i],SLOT(process()));
      connect(philosophers[i],SIGNAL(finished()),threads[i],SLOT(quit()));
      connect(philosophers[i],SIGNAL(finished()),philosophers[i],SLOT(deleteLater()));
      connect(threads[i],SIGNAL(finished()),threads[i],SLOT(deleteLater()));
      threads[i]->start();
   }
   //Creating a timer
   timer = new QTimer(this);
   //connect timer's signal to master's update slot
   connect(timer,SIGNAL(timeout()),this,SLOT(update()));
   timer->start(PERIODIC_TIMEOUT_MSEC); //From that moment,
                                        //the update slot os called every PERIODIC_TIMEOUT
}
// - - DESTRUCTOR - -
Master::~Master()
{
    delete timer; // то же самое что и dispose в PASCAL
}
void Master::startAll()
{
  qDebug()<<__FILE__<<" function "<<__FUNCTION__<<" line: "<<__LINE__;
  emit start(); //emit a start signal.
                //All workers will get this signal at the same time
}
  //Implementation of orderString slot
void Master::orderString(QString msg)
{
      inOrder = inOrder + msg;
      inOrderCount++;
      if (inOrderCount == Philosopher_AMOUNT)
      {
         qDebug()<<inOrder;
         inOrder="";
         inOrderCount = 0;
      }

}
//Master::update() is connected to timer in constructor
//timer will emit a signal every PERIODIC_TIME, calling Master::update()
void Master::update()
{
    qDebug()<<QDateTime::currentDateTime().toString()<<"STATUS ="
    <<checkPhils(); //call checkPhils() to run real logics
}
bool Master::checkPhils()
{
    bool logicOK = true;
 //--- PROBLEM RELATED TO LOGICS STARTS HERE ---
    int eatingCount = 0;
    QString s="";
    for (int i = 0;i<Philosopher_AMOUNT;i++)
    {
        if (philosophers[i]->GetStatus() == EATING)
        {
            eatingCount++;
            s = s + "Eat ";
        }
        if (philosophers[i]->GetStatus() == HUNGRY)
        {
            s = s + "Hung ";
        }
        if (philosophers[i]->GetStatus() == THINKING)
        {
            s = s + "Think ";
        }
    }
    if (eatingCount>2)
          logicOK = false;
    qDebug()<<s;
    return logicOK;
}
//--- PROBLEM RELATED TO LOGICS ENDS HERE ---
