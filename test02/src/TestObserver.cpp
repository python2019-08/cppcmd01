#include "TestObserver.h"


int testObserver2()
{

    std::shared_ptr<Subject> pSubject = std::make_shared<ConcreteSubject>();// 创建被观察者

    // 创建观察者
    std::shared_ptr<Observer> pObserver1_1 = std::make_shared<Observer1>(pSubject, "1");
    std::shared_ptr<Observer> pObserver1_2 = std::make_shared<Observer1>(pSubject, "2");
    std::shared_ptr<Observer> pObserver1_3 = std::make_shared<Observer1>(pSubject, "3");

    std::shared_ptr<Observer> pObserver2_4 = std::make_shared<Observer2>(pSubject, "4");
    std::shared_ptr<Observer> pObserver2_5 = std::make_shared<Observer2>(pSubject, "5");
    std::shared_ptr<Observer> pObserver2_6 = std::make_shared<Observer2>(pSubject, "6");

    // 注册观察者
    pSubject->Attach(pObserver1_1);
    pSubject->Attach(pObserver1_2);
    pSubject->Attach(pObserver1_3);
    pSubject->Attach(pObserver2_4);
    pSubject->Attach(pObserver2_5);
    pSubject->Attach(pObserver2_6);

    pSubject->SetState(2);// 改变状态
    pSubject->Notify();

    std::cout << std::string(50, '-') << std::endl;

    // 注销观察者
    pSubject->Detach(pObserver1_1);
    pSubject->Detach(pObserver1_2);

    pSubject->SetState(3);
    pSubject->Notify();

    return 0;
}
