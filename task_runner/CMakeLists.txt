cmake_minimum_required(VERSION 3.5)
project(task_runner_example)
set(CMAKE_CXX_FLAGS "-pthread -Wall -Wextra -O3")

enable_testing()

add_subdirectory(src)
add_subdirectory(tst)
add_subdirectory(lib/googletest)

add_executable(${PROJECT_NAME} cmdExample.cpp)

# Specify here the libraries this program depends on
target_link_libraries(${PROJECT_NAME}
    task_runner_lib
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
