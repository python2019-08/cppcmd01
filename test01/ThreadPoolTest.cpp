#include "ThreadPoolTest.h"
#include "ThreadPool.h"
#include <iostream>
#include <string>

std::string threadHandleFun(int arg1, std::string arg2)
{
	std::string str = std::to_string(arg1) + ":" + arg2;
	return str;
}

void thread_test()
{
	ThreadPool threadPool;
	threadPool.init_thread_pool(10); // 初始化大小为10的线程池
	std::vector<std::future<std::string>> futures;

	// 添加10000个任务
	for (int i = 0; i < 10; ++i)
	{ 
		futures.push_back(
			threadPool.add_task(threadHandleFun, i, std::to_string(i))
		);
	}

	// 等待所有任务完成
	for (auto& future : futures)
	{
		future.wait();
	}
	// 等待所有任务完成并获取结果
	for (auto& future : futures)
	{
		std::string result = future.get();
		//std::cout << result << std::endl;
	}

	std::cout << "end of thread_test" << std::endl;
}