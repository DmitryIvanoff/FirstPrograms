#include "biginteger.h"
BigInteger::BigInteger()
{
   sign=false;
}

BigInteger::BigInteger(long long value)
{
     long long temp=value;
     if (temp<0)
     {
        sign=true;
        temp=(-1)*value;
     }
     while (temp>0)
     {
         number.push_back(temp%10);
         temp=temp/10;
     }
    // print();

}

BigInteger::BigInteger(const BigInteger &bInt)
{
    if (!bInt.number.empty())
    {
        this->number.clear();
    }
    this->sign=bInt.sign;
    std::vector<int>::const_iterator NumIt;
    NumIt=bInt.number.cbegin();
    while(NumIt!=bInt.number.cend())
    {
        this->number.push_back(*NumIt);
        ++NumIt;
    }
}

BigInteger::BigInteger(std::string str)
{
    if (!str.empty())
    {
        std::string::const_iterator StrIt;
        StrIt=str.cend();
        while(StrIt!=str.cbegin())
        {
            --StrIt;
            char symbol=*StrIt;
            if (symbol=='-')
            {
                sign=true;
            }
            else
                number.push_back(atoi(&symbol));
        }
    }
    //print();

}

BigInteger::~BigInteger()
{
    number.clear();
    memset(&number,0,sizeof(number));
}

BigInteger BigInteger::operator=(const BigInteger &bInt)
{
    if (!bInt.number.empty())
    {
        this->number.clear();
    }
    this->sign=bInt.sign;
    std::vector<int>::const_iterator NumIt;
    NumIt=bInt.number.cbegin();
    while(NumIt!=bInt.number.cend())
    {
        this->number.push_back(*NumIt);
        ++NumIt;
    }
}

BigInteger BigInteger::operator+(BigInteger bInt)
{
    size_t size_a=this->number.size();
    size_t size_b=bInt.number.size();
    size_t length=0;
    std::vector<int>& a=this->number;
    std::vector<int>& b=bInt.number;   //результат будет содержаться в b (т.е. в bInt)
    if (size_a > size_b)
        length = size_a + 1;
    else
        length = size_b + 1;
    b.resize(length);
    a.resize(length);
    for (int i = 0; i < length-1; i++)
    {
        b[i]+= a[i];
        b[i + 1] += (b[i] / 10);
        b[i] %= 10;
    }
    if (b[length - 1] == 0)
    {
        b.pop_back();
    }
    a.resize(size_a);                //восстанавливаем размер (т.к. наше число не меняется, а результат содержится в bInt)
    return bInt;
}

void BigInteger::operator+=(BigInteger bInt)
{
    size_t size_a=this->number.size();
    size_t size_b=bInt.number.size();
    size_t length=0;
    std::vector<int>& a=bInt.number;
    std::vector<int>& b=this->number;//результат будет содержаться в b (т.е. в данном экземпляре)
    if (size_a > size_b)            //здесь устанавливаем возможную длину результата (старший разряд результата равен 0)
        length = size_a + 1;
    else
        length = size_b + 1;
    b.resize(length);
    a.resize(length);
    for (int i = 0; i < length-1; i++)
    {
        b[i]+= a[i];              // суммируем последние разряды чисел
        b[i + 1] += (b[i] / 10);  // если есть разряд для переноса, переносим его в следующий разряд
        b[i] %= 10;               // если есть разряд для переноса он отсекается
    }

    if (b[length - 1] == 0)        //если самый первый(старший) разряд результата так и остался равным 0, то уменьшаем длину результата
    {
        b.pop_back();
    }
}

void BigInteger::operator*=(BigInteger bInt)
{
    size_t size_a=this->number.size();
    size_t size_b=bInt.number.size();
    size_t length=0;
    std::vector<int>& a=this->number;
    std::vector<int>& b=bInt.number;
    std::vector<int> c;
    length = size_a + size_b+1;
    c.resize(length);
    for (int i = 0; i < size_a; i++)
        for (int j = 0; j < size_b; j++)
            c[i + j] += a[i] * b[j];

    for (int i = 0; i < length-1; i++)
    {
        c[i + 1] +=  c[i] / 10;
        c[i] %= 10;
    }

    while ((length>1)&&(c[length-1] == 0))
    {
        c.pop_back();
        --length;
    }
    this->number.clear();
    this->sign=bInt.sign^this->sign;
    std::vector<int>::const_iterator NumIt;
    NumIt=c.cbegin();
    while(NumIt!=c.end())
    {
        this->number.push_back(*NumIt);
        ++NumIt;
    }


}

BigInteger BigInteger::operator*(BigInteger bInt)
{
    size_t size_a=this->number.size();
    size_t size_b=bInt.number.size();
    size_t length=0;
    BigInteger res;

    std::vector<int>& a=this->number;
    std::vector<int>& b=bInt.number;
    std::vector<int>& c=res.number;
    length = size_a + size_b+1;

    c.resize(length);
    for (int i = 0; i < size_a; i++)
        for (int j = 0; j < size_b; j++)
            c[i + j] += a[i] * b[j];

    for (int i = 0; i < length-1; i++)
    {
        c[i + 1] +=  c[i] / 10;
        c[i] %= 10;
    }
    while ((length>1)&&(c[length-1] == 0))
    {
        c.pop_back();
        --length;
    }
    res.sign=bInt.sign^this->sign;
    return res;
}

void BigInteger::print()
{
    std::vector<int>::const_iterator NumIt;
    NumIt=number.cend();
    if (!number.empty())
    {
        if (sign)
        {
            std::cout<<"-";
        }
        while(NumIt!=number.cbegin())
        {
            --NumIt;
            std::cout<<*NumIt;
        }
    }
    else
    {
        std::cout<<0;
    }

}


