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
	//// ���10000������
	//for (int i = 0; i < 10000; ++i)
	//{
	//	futures.push_back(threadPool.enqueue(threadHandleFun2, i, "str"));
	//}
	//// �ȴ������������
	//for (auto& future : futures)
	//{
	//	future.wait();
	//}
	// �ȴ�����������ɲ���ȡ���
	for (auto& future : futures)
	{
		int result = future.get();
		std::cout << result << std::endl;
	}
}
