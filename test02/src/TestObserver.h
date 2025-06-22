#pragma once
#include <memory>
#include <iostream>
#include <list>
#include <algorithm>

class Observer;
// ���󱻹۲���
class Subject {
public:
    Subject() : m_nState(0) {}

    virtual ~Subject()
    {
        std::cout << "~Subject() destroyed !" << std::endl;
    }

    virtual void Attach(const std::shared_ptr<Observer> pObserver) = 0;

    virtual void Detach(const std::shared_ptr<Observer> pObserver) = 0;

    virtual void Notify() = 0;

    virtual int GetState() { return m_nState; }

    void SetState(int state) {
        std::cout << "Subject updated !" << std::endl;
        m_nState = state;
    }

protected:
    std::list<std::shared_ptr<Observer>> m_pObserver_list;
    int m_nState;
};

// ����۲���
class Observer {
public:
    virtual ~Observer()
    {
        std::cout << "~Observer() destroyed !" << std::endl;
    }

    Observer(const std::shared_ptr<Subject> pSubject, 
            const std::string& name = "unknown")
        : m_pSubject(pSubject), m_strName(name) {}

    virtual void Update() = 0;

    virtual const std::string& name() { return m_strName; }

protected:
    std::shared_ptr<Subject> m_pSubject;
    std::string m_strName;
};

//���屻�۲���
class ConcreteSubject : public Subject {
public:
    void Attach(const std::shared_ptr<Observer> pObserver) override 
    { 
        auto iter = std::find(m_pObserver_list.begin(), m_pObserver_list.end(), pObserver);
        if (iter == m_pObserver_list.end()) {
            std::cout << "Attach observer" << pObserver->name() << std::endl;
            m_pObserver_list.emplace_back(pObserver);
        }

    }

    void Detach(const std::shared_ptr<Observer> pObserver) override {
        std::cout << "Detach observer" << pObserver->name() << std::endl;
        m_pObserver_list.remove(pObserver);
    }

    //ѭ��֪ͨ���й۲���
    void Notify() override 
    {
        auto it = m_pObserver_list.begin();
        while (it != m_pObserver_list.end()) 
        {
            (*it++)->Update();
        }
    }
};


//����۲���1
class Observer1 : public Observer 
{
public:
    Observer1(const std::shared_ptr<Subject> pSubject, 
              const std::string& name = "unknown")
        : Observer(pSubject, name) {}

    void Update() override 
    {
        std::cout << "Observer1_" << m_strName 
            << " get the update.New state is: " << m_pSubject->GetState() 
            << std::endl;
    }
};

//����۲���2
class Observer2 : public Observer {
public:
    Observer2(const std::shared_ptr<Subject> pSubject, 
            const std::string& name = "unknown")
        : Observer(pSubject, name) {}

    void Update() override {
        std::cout << "Observer2_" << m_strName << " get the update.New state is: "
            << m_pSubject->GetState() << std::endl;
    }
};


int testObserver2();
