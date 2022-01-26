cmake_minimum_required(VERSION 3.5)
project(task_runner_example)
set(CMAKE_CXX_FLAGS -pthread)

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

# Will download external CMakeable project from git repo, branch "master" and install it in $DEPS_ROOT
# This also will create "googletest.git" target, which we'll use as dependency for our test project
#ExtProjectGit("https://github.com/google/googletest.git" "master" ${DEPS_ROOT} CMAKE_ARGS "${_OPT_CMAKE_ARGS}")
