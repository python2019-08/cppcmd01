cmake_minimum_required (VERSION 3.5)

project(cppcmd01)

include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})


set(OPTIMIZE_LEVEL 0)

add_compile_options(
    -fPIC
    -g
    -fpermissive  # to support not decleare function using in template.
    -fshort-wchar
    -O${OPTIMIZE_LEVEL} # Default -O2
    -g
    -std=c++17
    -DNTG_DEVEL
    -D_FORTIFY_SOURCE=2
    -fexceptions

    -fno-omit-frame-pointer
    -funwind-tables -feliminate-unused-debug-types
    -fstack-protector-strong
)

# Add sub directories
add_subdirectory(test01)
add_subdirectory(test02) 


# Create the executable
add_executable(${PROJECT_NAME} main_cppcmd01.cpp)

# Link the static library from test01 using its alias TestCxx::t01
# Link the header only library from test02 using its alias TestCxx::t02
# This will cause the include directories for that target to be added to this project
target_link_libraries(${PROJECT_NAME}
    TestCxx::t01
    TestCxx::t02
)


target_include_directories( ${PROJECT_NAME}  PUBLIC
    ${PROJECT_SOURCE_DIR}/
    ${PROJECT_SOURCE_DIR}/3rd/argparse/include
)