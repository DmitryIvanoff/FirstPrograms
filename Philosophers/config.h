#ifndef CONFIG
#define CONFIG
const int CONFIG_Philospher_AMOUNT=5;//number of threads to create
const int PERIODIC_TIMEOUT_MSEC = 1000;// timeout for timer
                                     //periodic calls for master::update();
const int WAITING_DELAY_MSEC = 1000;
const int EATING_DELAY_MSEC = 2000;
const int THINKING_DELAY_MSEC = 1000;
//#define USE_UNSAFE
#endif // CONFIG

