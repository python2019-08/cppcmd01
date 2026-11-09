#include "test_async.h"

#include <future>
#include <thread>

#include <type_traits> 
#include <iostream>

// std::async 不保存返回值
void testAsync01() {
    std::async(std::launch::async,  []{
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Async task completed" << std::endl;
    });
    // 注意：这里没有保存返回的 std::future
}

// ====================================
int testAsync02_work(int a, int b)
{
    return a + b;
}

int testAsync02()
{
    // 启动异步任务
    auto fut = std::async(testAsync02_work, 10, 20);

    // 阻塞等待，获取返回值
    int res = fut.get();
    std::cout << res << "\n";
    return 0;
}