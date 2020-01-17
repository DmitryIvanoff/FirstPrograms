#include <QCoreApplication>
#include <biginteger.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    BigInteger Int(10);
    BigInteger Int2(Int);
    BigInteger Int3(1000);
    //Int3=Int+Int2;
    //Int3+=BigInteger("20000000000000000000000000000000000000");
    Int3=Int*Int2;
   // Int3*=BigInteger("55555555555555555555");
    Int3.print();
    return a.exec();
}
