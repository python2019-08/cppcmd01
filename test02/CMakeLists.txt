# Set the project name
project(test02)

# Add a library with the above sources
SET(test02_Src)
LIST(APPEND  test02_Src
    src/TestDerive.cpp  
    src/TestObserver.cpp  
    src/TestRegex.cpp  
    src/test_shared_from_this.cpp
)
# message(STATUS "..........test02_Src=${test02_Src}") 

add_library(${PROJECT_NAME} ${test02_Src})
add_library(TestCxx::t02 ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/src
)
