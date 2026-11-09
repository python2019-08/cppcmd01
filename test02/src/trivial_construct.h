#pragma once
#include <iostream>
#include <iomanip>

class MyTrivialBase
{
protected:
    int baseVal = 99;
    int baseVal1 = 16;
public:
    MyTrivialBase() {
        std::cout << "in MyTrivialBase,&baseVal=" << std::setbase(16) << (long)&baseVal
            << ",this=" << (long)this << std::endl;
    }

    MyTrivialBase(int a) {
    }

    void F2() {
        std::cout << "in MyTrivialBase F2" << std::endl;
    }

 
};
