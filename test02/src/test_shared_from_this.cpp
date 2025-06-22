#include "test_shared_from_this.h"
#include <memory>
#include <string>
#include <thread>
//作者：风满楼
//链接：https ://www.zhihu.com/question/30957800/answer/2920976448

class Bar : std::enable_shared_from_this<Bar>
{
public:
    Bar(std::string data) : data_(std::move(data)) {}

    template<typename CallBack>
    void start(CallBack&& cb) {
        int testInt = 11;
        thd_ = std::thread(
            [this,ti=testInt, self = shared_from_this(), notify_cb = std::move(cb)] 
            {
            notify_cb(data_);
            });
    }

private:
    std::thread thd_;
    std::string data_;
};


 