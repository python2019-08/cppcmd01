#include "TestDerive.h"



void TestDerive::test_derive()
{

    MyBase a1, a2;
    MyBase a3 = a1 + a2;

    std::cout << "----------Base  b;----------" << std::endl;
    MyBase  b;

    std::cout << "----------MyVVDClass  mc;--------" << std::endl;
    MyVVDClass  mc;
    std::cout << "-------------" << std::endl;

    std::cout << "sizeof(mc)=" << std::setbase(10) << sizeof(mc) << std::endl;
    std::cout << "sizeof(VirtualDerivedA)=" << sizeof(VirtualDerivedA) << std::endl;


    std::cout << "=======VirtualDerivedA  da;=============" << std::setbase(16) << 1 << std::endl;
    VirtualDerivedA  da;
    std::cout << "sizeof(da)=" << std::setbase(10) << sizeof(da) << std::endl;

    std::cout << "=======DerivedC  c1;===========" << std::setbase(16) << 1 << std::endl;
    DerivedC  c1;
    std::cout << "sizeof(c1)=" << std::setbase(10) << sizeof(c1) << std::endl;
    std::cout << "-------------" << std::endl;

}
