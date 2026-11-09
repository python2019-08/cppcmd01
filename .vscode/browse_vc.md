### 目录说明
```bash
(base) a@a:~/a2/zdev/cpp/cppcmd01$ ls .vscode/
browse.vc.db       browse.vc.db-wal       launch.json
browse.vc.db.lock  browse_vc.md           settings.json
browse.vc.db-shm   c_cpp_properties.json  tasks.json
```
这是 **VSCode C/C++ 插件（Microsoft C/C++ Extension）** 的工作区配置 + 索引缓存目录，是 C++ 开发最经典的一套配置文件。

#### 1. 数据库文件（索引缓存，可删）
- `browse.vc.db`：C/C++ 插件的**符号索引数据库**（sqlite），用来实现跳转、查找引用、符号预览
- `browse.vc.db-shm` / `browse.vc.db-wal`：sqlite 的 WAL 日志文件
- `browse.vc.db.lock`：数据库锁文件
> ✅ 作用：加速代码跳转、全局搜索符号
> ✅ 可以直接删掉，重启 VSCode 插件会自动重建；代码量大的时候这个库会很占空间
> ❗ 不要手动编辑

#### 2. 四个核心 json 配置文件（重点，你写C++编译调试都靠它们）
1. **`c_cpp_properties.json`**
    告诉 C/C++ 插件：头文件路径、C++标准、宏定义、编译器路径、includePath、defines。
    > 只给**语法高亮、智能提示、跳转**用，**不负责编译**！
    > 很多新手踩坑：这里配置对了，只是不飘红；编译失败要看 tasks.json / cmake。

2. **`tasks.json`**
    定义**编译任务**：调用 g++/clang++/cl.exe / cmake，编译源码、生成可执行文件。
    快捷键 `Ctrl+Shift+B` 就是跑这里注册的 task。

3. **`launch.json`**
    定义**调试配置**：gdb/lldb/msvc 调试器，指定要调试哪个程序、传命令行参数、环境变量。
    F5 调试的时候读取这个文件。

4. **`settings.json`**
    工作区级别的 VSCode 全局设置：格式化工具（clang-format）、文件排除、插件参数、终端配置等。

---
### 常见配套两种场景
- 简单单文件/小项目：手写 tasks + launch（就是你现在这套）
- 大型项目（Autoware、ROS、C++工程）：一般改用 **CMakeLists.txt + cmake-tools 插件**，会额外生成 `cmake-variants.json` 等，不再手写 tasks。

### 常用操作
- 想清理索引、符号乱跳：直接 `rm .vscode/browse.vc.db*`
- 生成这几个json：`Ctrl+Shift+P` → `C/C++: Edit Configurations (UI)`、`Tasks: Configure Task`、`Debug: Open launch.json`

