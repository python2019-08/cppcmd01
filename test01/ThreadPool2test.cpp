#include "ThreadPool2test.h"
#include "ThreadPool2.h"
#include <iostream>

int threadHandleFun2(int arg1, std::string str)
{
	return arg1;
}

//ThreadPool2 threadPool(10);

void thread_test2()
{


	std::vector<std::future<int>> futures;
	//// 添加10000个任务
	//for (int i = 0; i < 10000; ++i)
	//{
	//	futures.push_back(threadPool.enqueue(threadHandleFun2, i, "str"));
	//}
	//// 等待所有任务完成
	//for (auto& future : futures)
	//{
	//	future.wait();
	//}
	// 等待所有任务完成并获取结果
	for (auto& future : futures)
	{
		int result = future.get();
		std::cout << result << std::endl;
	}
}
