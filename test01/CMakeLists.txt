# Set the project name
project(test01)

# Add a library with the above sources
SET(test01_Src)
LIST(APPEND  test01_Src
    MyClock.cpp  
    TestDerived01Class.cpp  
    threadpool00.cpp  
    ThreadPool2test.cpp  
    ThreadPoolTest.cpp
    test_packaged_task.cpp
)

# message(STATUS "........test01_Src=${test01_Src}")

add_library(${PROJECT_NAME} ${test01_Src})
add_library(TestCxx::t01 ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/
)
