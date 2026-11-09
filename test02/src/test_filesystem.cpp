#include "test_filesystem.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int test_filesystem() 
{
    // 打印当前文件，不带后缀
    std::cout << fs::path(__FILE__).stem() << std::endl;
    return 0;
}
