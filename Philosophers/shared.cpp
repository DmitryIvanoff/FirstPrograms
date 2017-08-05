#include "shared.h"
#include "config.h"
#include <QThread>
#include <QSemaphore>
#define N 5
#define LEFT (i+N-1)%N
#define RIGHT (i+1)%N
#define THINKING 0
#define HUNGRY 1
#define EATING 2
QSemaphore s[CONFIG_Philospher_AMOUNT];//в начальный момент времени все семафоры(мьютексы) равны 0
//functions test(),takeforks,putforks use a shared critical section.
//this critical section is protected with mutex, a QMutex object, mutex in UNLOCKED
//at the moment of creation.
Shared::Shared()
{
  for (int i=0;i<CONFIG_Philospher_AMOUNT;i++)
  {
     state[i]=THINKING;
  }
}
void Shared::test(int i)
{
    if (state[i]==HUNGRY && state[LEFT]!=EATING && state[RIGHT]!=EATING)
    {
       state[i]=EATING;
       s[i].release(1);  //QSemaphore s[i] is being UNLOCKED
    }
}
void Shared::TakeForks(int i)
{
   mutex.lock();        //mutex object is used to protect state[]. Mutex is being locked. Critical section.
   state[i] = HUNGRY;  // to write we must be sure, no one is reading it.
   test(i);       //attempt to eat if neighbours are not eating now.
   mutex.unlock();      //mutex is unlocked;
   s[i].acquire(1); //поток блокируется, если философу не досталось вилок, и ждет,пока другие(соседи) потоки "не освободят" его
                    //в процедуре putforks за освобождение этого потока отвечают test(LEFT) и test(RIGHT)
                  //(In case of failure, thread is locked with QSemaphore s[i]
                  //and waiting for til neighbours call him;at the beginning semaphores s[i] are LOCKED i.e. equal'0'
}
void Shared::PutForks(int i)
{
    mutex.lock();    //critical section
    state[i] = THINKING;
    test(LEFT);
    test(RIGHT);
    mutex.unlock(); //release mutex
}
