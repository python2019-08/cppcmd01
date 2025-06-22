#pragma once
#include <cstdio>

class MyBaseClass {//����
public:
    virtual  void Print()
    {
        printf("This is the base class.");
    }
};
class MyDerived01Class :public MyBaseClass//������
{
    // C#�С�override�����ܸ��㴫�ݣ�����C++�п���
public:
    void Print() //override
    {
        MyBaseClass::Print();
        printf("This is the derived 01 class.");
    }
};

class MyDerived02Class :public MyDerived01Class
{
public:
    void Print()override
    {
        printf("This is the derived 02 class.\n");
    }
};

class TestDerived01Class
{
public:
    static void testDerivedClass()
    {
        MyDerived02Class* derived = new MyDerived02Class();//MyDerived02Class
        MyBaseClass* mybc = (MyBaseClass*)derived;
        //ʹ��MyBaseClass
        derived->Print();
        mybc->Print();
    }

};

