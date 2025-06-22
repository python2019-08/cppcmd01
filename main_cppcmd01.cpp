// cppcmd01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "test01/ThreadPoolTest.h"
#include "test01/ThreadPool2test.h"
#include "test01/threadpool00.h"
#include "test01/TestDerived01Class.h"
#include "test01/MyClock.h"

#include <argparse/argparse.hpp>

int parseArguments(int argc, char* argv[], bool& aPlayDogBark )
{
    argparse::ArgumentParser argP("DiagnosticTool", "1.0");

    argP.add_argument("-d", "--PlayDogBark")
        .help("Play dog bark.")
        .default_value(true)
        .implicit_value(true); 

    try
    {
        argP.parse_args(argc, argv); // Example: ./main -abc 1.95 2.47
    }
    catch (const std::runtime_error& err)
    {
        std::cerr << "argparse.parse_args()runtime_error: " 
                  << err.what() 
                  << std::endl;
        //std::cerr << "argparse.parse_args()error: " << argP;
        return -1;
    }
    catch (const std::exception& e) {
        std::cerr << "argparse.parse_args()exception: " 
            << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "argparse.parse_args() catch (...)" << std::endl;
    }

    aPlayDogBark = argP.get<bool>("-d"); // true 
    return 0;
}

#include <bitset>
#include <string>

std::string testXXX(const int decimal)
{
    return std::bitset<11>(decimal).to_string();
}

int main(int argc, char* argv[])
{
    std::string  xx = testXXX(777747);
    TestDerived01Class::testDerivedClass();

    bool isPlayDogBark = false;
    int ret = parseArguments(argc, argv, isPlayDogBark);
    if (ret < 0)
    {
        return -1;
    }

    MyClock::run(isPlayDogBark);
     
    return 0;
}

 
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
