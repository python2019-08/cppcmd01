#ifdef _HAS_STD_BYTE
#undef _HAS_STD_BYTE
#endif
#define _HAS_STD_BYTE 0
#ifndef _THREAD_POOL2_H
#define _THREAD_POOL2_H

#include <vector>
#include <thread>
#include <future>
#include <queue>
#include <mutex>
#include <functional>
#include <condition_variable>

class ThreadPool2
{
public:
	ThreadPool2(size_t threads) : threadSize_(threads)
	{
		init_thread_pool();
	}

	~ThreadPool2()
	{
		//for (auto &t : threads_)
		//{
		//	t.join();
		//}
	}

	template <class F, class... Args>
	auto enqueue(F &&f, Args &&...args) -> std::future<typename std::result_of<F(Args...)>::type>
	{
		using return_type = typename std::result_of<F(Args...)>::type;

		auto task = std::make_shared<std::packaged_task<return_type()>>(
			std::bind(std::forward<F>(f), std::forward<Args>(args)...));

		std::future<return_type> res = task->get_future();
		{
			std::unique_lock<std::mutex> lock(queue_mutex);
			tasks_.emplace([task]()
						   { (*task)(); });
		}
		condition_.notify_one();
		return res;
	}

private:
	void thread_function()
	{
		while (true)
		{
			std::function<void()> task;
			{
				std::unique_lock<std::mutex> lock(queue_mutex);
				condition_.wait(lock, [this]
								{ return !tasks_.empty(); });
				task = tasks_.front();
				tasks_.pop();
			}
			task();
		}
	}

	void init_thread_pool()
	{
		for (size_t i = 0; i < threadSize_; ++i)
		{
			//threads_.emplace_back(&ThreadPool2::thread_function, this);
			std::thread t(&ThreadPool2::thread_function, this);
			t.detach();
		}
	}

	//std::vector<std::thread> threads_;
	std::queue<std::function<void()>> tasks_;
	std::mutex queue_mutex;
	std::condition_variable condition_;
	int threadSize_;
};
#endif //_THREAD_POOL2_H