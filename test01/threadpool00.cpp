#include "threadpool00.h"
#include <iostream>
#include <string>

//ThreadPool00 pool(4);
int threadFunc00(int answer)
{
    return answer;
}
void threadpool_test00()
{
    // create thread pool with 4 worker threads


    // enqueue and store future
    //auto result = pool.enqueue([](int answer) -> int
    //    { 
    //        return answer; 
    //    }, 
    //    42);

    // get result from future
    //result.share().wait_for(std::chrono::seconds(1));
    std::cout << "result.get()...01" << std::endl;
    std::cout << "intRet" << std::endl;

    std::cout << "result.get()...02" << std::endl;
}