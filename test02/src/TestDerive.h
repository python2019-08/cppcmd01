#pragma once

#include <string>
#include <vector>
#include <cerrno>
#include <memory>
#include <cstdlib>
#include <iomanip>
#include <utility>
#include <iostream>
#include <stdexcept>
// #include <gsl/gsl>




class MyBase
{
protected:
    int baseVal = 99;
    int baseVal1 = 16;
public:
    MyBase() {
        std::cout << "in MyBase,&baseVal=" << std::setbase(16) << (long)&baseVal
            << ",this=" << (long)this << std::endl;
    }

    MyBase(int a) {
    }

    virtual void virtualF2() {
        std::cout << "in MyBase virtualF2" << std::endl;
    }


    virtual void virtualF1() {
        std::cout << "in MyBase virtualF1" << std::endl;
    }


    virtual ~MyBase() {
        std::cout << "~MyBase" << std::endl;
    }

    friend MyBase operator+(MyBase& a, MyBase& b)
    {
        return (MyBase(a.baseVal + b.baseVal));
    }

    void set_baseVal(int a)
    {
        baseVal = a;
    }
};



class VirtualDerivedA :public virtual MyBase
{
protected:
    int _a = 1;
    int _a1 = 1;
public:

    VirtualDerivedA()
    {
        std::cout << "in VirtualDerivedA,&baseVal=" << (long)&baseVal
            << "&_a = " << (long)&_a
            << ",this=" << (long)this << std::endl;
    }

    virtual ~VirtualDerivedA() {
        std::cout << "~VirtualDerivedA" << std::endl;
    }

    virtual void virtualF1() override {
        std::cout << "VirtualDerivedA::virtualF1" << std::endl;
    }

    virtual void virtualF2() override {
        std::cout << "VirtualDerivedA::virtualF2" << std::endl;
    }
};



class VirtualDerivedB : public virtual MyBase
{
protected:
    int _b = 1;
    int _b1 = 1;
public:
    virtual ~VirtualDerivedB() {
        std::cout << "~VirtualDerivedB" << std::endl;
    }

    VirtualDerivedB()
    {
        std::cout << "in VirtualDerivedB,&baseVal=" << (long)&baseVal
            << "&_b = " << (long)&_b
            << ",this=" << (long)this << std::endl;
    }

};

class MyVVDClass :VirtualDerivedA, VirtualDerivedB
{
public:
    MyVVDClass()
    {
        std::cout << "in MyVVDClass,&baseVal =" << (long)&baseVal
            << "&_a = " << (long)&_a
            << ",this=" << (long)this << std::endl;
    }

    virtual ~MyVVDClass() {
        std::cout << "~MyVVDClass" << std::endl;
    }


    virtual void virtualF1() override {
        std::cout << "MyVVDClass::virtualF1" << std::endl;
    }

    virtual void virtualF2() override {
        std::cout << "MyVVDClass::virtualF2" << std::endl;
    }
};

//============================================================
class DerivedC :protected MyBase
{
    int _c = 1;
    int _c1 = 1;


public:
    DerivedC()
    {
        std::cout << "in DerivedC,&baseVal=" << (long)&baseVal
            << "&_c = " << (long)&_c
            << ",this=" << (long)this << std::endl;
    }
};

class TestDerive
{
public:
    TestDerive()
    {

    }

    void test()
    {
        for (size_t i = 0; i < 6; i++)
        {
            if (nullptr == _MyBaseArr[i])
            {
                _MyBaseArr[i] = std::make_shared<MyBase>();
            }
        }
    }

    void test_derive();
private:

    std::shared_ptr<MyBase>  _MyBaseArr[6] = { nullptr, };
};