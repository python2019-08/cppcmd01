#ifdef _HAS_STD_BYTE
#undef _HAS_STD_BYTE
#endif
#define _HAS_STD_BYTE 0
#ifndef _THREAD_POOL_H
#define _THREAD_POOL_H

// #include "ydUtil/Param.h"
// #include "ydNetBus/Node.h"
// #include <osg/ComputeBoundsVisitor>
// #include "structsDefine.h"
// #include <map>
// #include <ydUtil/Block.h>

#include <thread>
#include <future>
#include <queue>
#include <vector>
using namespace std;
// #define M_PI 3.1415926

class ThreadPool
{
public:
	void thread_function()
	{
		while (true)
		{
			std::function<void()> task;

			// 获取任务
			{
				std::unique_lock<std::mutex> lock(queue_mutex);
				condition.wait(lock, [this]
							   { return !task_queue.empty(); });
				task = task_queue.front();
				task_queue.pop();
			}

			// 执行任务
			task();
		}
	}
	void init_thread_pool(size_t threads)
	{
		for (size_t i = 0; i < threads; ++i)
		{
			// std::thread t(thread_function);
			std::thread t(&ThreadPool::thread_function, this);
			t.detach();
		}
	}

	template <typename Func, typename... Args>
	std::future<typename std::invoke_result<Func, Args...>::type> 
		add_task(Func &&f, Args &&...args)
	{
		std::unique_lock<std::mutex> lock(queue_mutex);
		task_queue.push([f, args...]()
						{ return f(args...); });
		condition.notify_one();

		// 使用packaged_task来获取未来
		std::packaged_task<typename std::invoke_result<Func,Args...>::type()> task([f, args...]()
																				{ return f(args...); });
		std::future<typename std::invoke_result<Func,Args...>::type> res = task.get_future();
		lock.unlock();
		task(); // 直接调用task来避免在任务队列中等待
		return res;
	}

private:
	// 线程安全的任务队列
	std::queue<std::function<void()>> task_queue;
	std::mutex queue_mutex;
	std::condition_variable condition;
};
#endif // !DATAANA_COMMON_H
