#ifndef SHARED_H
#define SHARED_H

#include <QMutex>
#include "config.h"

class Dummy //Dummy class will show, what happens, if mutex is not used.
{            //it replaces QMutex in Share class, but makes nothing
public:
   void lock(){}
   void unlock(){}
};

class Shared
{
public:
     Shared(); //constructor

     //  --- PROBLEM RELATED WITH LOGICS STARTS HERE  ---
private:
    int state[CONFIG_Philospher_AMOUNT];//массив состояний философов
#ifdef  USE_UNSAFE
     Dummy mutex;
#else
     QMutex mutex;
#endif
public:
    void test(int i);
    void TakeForks(int i);
    void PutForks(int i);
   //  --- PROBLEM RELATED WITH LOGICS ENDS HERE  ---
};


#endif // SHARED_H
