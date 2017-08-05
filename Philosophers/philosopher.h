#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H
#include <QObject>
#include "shared.h"
#include "config.h"
typedef enum {THINKING,EATING,HUNGRY} PhilosopherStatus; //a variable type to store names of states
class Philosopher: public QObject
{
    Q_OBJECT
public:
    Philosopher(int n, Shared* shared);//Constructor
    ~Philosopher();//Destructor
signals:
  void finished();// is emited,when all data is processed.
  void order(QString message); //Emit this signal with some data to show an order of processing
public slots:
  void process(); //THE MAIN PROCESS
private:
   //  --- PROBLEM RELATED WITH LOGICS STARTS HERE  ---
    int name;       //philosopher's name.( we use digits to name them);
    Shared* shared;  //a pointer to an object of class Shared
                     //all philosophers share the same data object(где находится массив состояний state).
                    //that pointer should be provided to philosophers constructor
    PhilosopherStatus status; //Variable 'status' takes values only which defined on line 6
public:
    PhilosopherStatus GetStatus()// returns status
     {
        return status;
     }
    //  --- PROBLEM RELATED WITH LOGICS ENDS HERE  ---
};

#endif // PHILOSOPHER_H
