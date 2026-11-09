# std::async
<!-- doubaoAI -->
`std::async` 是 C++11 引入的异步任务工具，头文件：`<future>`
简单说：**启动一个异步任务，返回一个 std::future，用来后续拿结果、捕获异常**

```cpp
#include <future>
#include <iostream>

int work(int a, int b)
{
    return a + b;
}

int main()
{
    // 启动异步任务
    auto fut = std::async(work, 10, 20);

    // 阻塞等待，获取返回值
    int res = fut.get();
    std::cout << res << "\n";
    return 0;
}
```

## 第一个重点：启动策略（std::launch）

`std::async` 第一个可选参数是 launch 标记，两个核心枚举：

1. **std::launch::async**：强制在**独立新线程**马上跑
2. **std::launch::deferred**：延迟执行，**直到调用 .get() / .wait() 的时候，才在当前线程跑**（不新开线程）
3. 默认：`std::launch::async | std::launch::deferred`，由标准库自己选择（非常容易踩坑！）

```cpp
// 强制新开线程
auto fut = std::async(std::launch::async, work, 1,2);
// 延迟执行
auto fut2 = std::async(std::launch::deferred, work, 3,4);
```

> 
> ⚠️ 默认策略坑：库可能选择 deferred，**不会新建线程**，你以为是并发，实际是串行！
> 写并发代码，想要一定开线程，**尽量显式写 std::launch::async**

## std::future 常用接口

- `.get()`：阻塞等待任务完成，拿到返回值；任务抛异常会在这里 rethrow
- `.wait()`：只等完成，不拿结果，无返回
- `.wait_for(std::chrono::xxx)`：限时等待，返回 `std::future_status`
  - `ready`：完成
  - `timeout`：超时
  - `deferred`：延迟任务还没触发
- `.valid()`：判断 future 是否绑定了共享状态

## 关键特性 & 大坑

1. **future 的移动语义，不能拷贝**

```cpp
auto f1 = std::async(work,1,2);
// auto f2 = f1; // 编译报错，不能拷贝
auto f2 = std::move(f1); // ✅ 只能move
```

2. **std::async 返回的 future 析构时会阻塞！**> 
> 这是最经典的坑！
> 临时对象 `std::async(...).get()` 没问题；
> 如果是临时 `std::async(...)` 不接收、不保存future，**析构会直接阻塞主线程等任务结束**

```
// ❌ 危险写法，等价于同步执行！
std::async(std::launch::async, work, 1,2);
// 临时future销毁，~future()阻塞等待任务结束
```

3. 异常传递
任务函数里面 throw 的异常，会存到共享状态，直到 `.get()` 的时候抛出：

```cpp
auto fut = std::async([](){ throw std::runtime_error("oops"); });
try {
    fut.get();
} catch(const std::exception& e) {
    std::cerr << e.what();
}
```

4. 和 std::thread 的区别

- `std::thread`：一定开线程，没有内置返回值，需要手动传参、用promise传结果；join()/detach()
- `std::async`：封装更高层，自带 future 拿结果；但默认策略不确定、析构阻塞；**不是线程池！**> 
> 注意：`std::async` **不是线程池**，多次async(launch::async)会创建大量线程，线程多了会有调度开销。大量并发任务优先用线程池。

## std::promise / std::packaged_task 顺带对比（都是future配套）

- `std::packaged_task`：把一个函数包装成可调用对象，自带future，可以手动调度（丢进线程池）
- `std::promise`：手动设置值/异常，给另一端的future，适合跨线程回调赋值

## 简单封装示例（C++17）

```cpp
#include <future>
#include <chrono>
#include <iostream>

int long_task(int x)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    return x * x;
}

int main()
{
    auto fut = std::async(std::launch::async, long_task, 9);
    std::cout << "do other things...\n";

    auto st = fut.wait_for(std::chrono::milliseconds(200));
    if(st == std::future_status::ready)
    {
        std::cout << "result: " << fut.get() << "\n";
    }
    else
    {
        std::cout << "not ready yet, wait full\n";
        std::cout << fut.get() << "\n";
    }
    return 0;
}
```

## 什么时候不推荐用 std::async

- 需要可控线程数量、大量任务（优先线程池 + packaged_task）
- 你不想 future 析构自动阻塞
- 需要常驻后台、分离的任务（适合 std::thread + detach，但detach有风险）

如果你需要，我可以给：

1. 基于 `std::async` 写一个简易线程池
2. 或者写一个不会在析构阻塞的 async 包装器

要不要顺带讲 `std::shared_future`？