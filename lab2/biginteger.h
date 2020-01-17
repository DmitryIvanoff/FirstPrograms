#ifndef BIGINTEGER_H
#define BIGINTEGER_H
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
class BigInteger
{
    typedef unsigned char byte;
public:
    BigInteger();
    BigInteger(long long value);
    BigInteger(const BigInteger& bInt);
    BigInteger(std::string);
    ~BigInteger();
    void operator+= (BigInteger bInt);
    void operator*= (BigInteger bInt);
    BigInteger operator* (BigInteger bInt);
    BigInteger operator= (const BigInteger& bInt);
    BigInteger operator+ (BigInteger bInt);
    void print();


private:
    std::vector<int> number;
    bool sign=false;              //false- число неотрицательное,true - отрицательное
};

#endif // BIGINTEGER_H
