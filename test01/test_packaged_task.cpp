#include "test_packaged_task.h"

#include <iostream>
#include <future>
#include <thread>


int test_packaged_task() 
{
    // 创建一个 packaged_task
    std::packaged_task<int()> task([]() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return 7;
        });

    // 获取与之关联的 future
    std::future<int> result = task.get_future();

    // 在另一个线程中运行任务
    std::thread(std::move(task)).detach();

    // 等待任务完成并获取结果
    try {
        std::cout << "Result: " << result.get() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}