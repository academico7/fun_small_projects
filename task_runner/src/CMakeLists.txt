
add_library(task_runner_lib SHARED 
    task_runner.cpp
)

set_target_properties(task_runner_lib PROPERTIES PUBLIC_HEADER include/task_runner.h)

target_include_directories(task_runner_lib  PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

include(GNUInstallDirs)

install(TARGETS task_runner_lib LIBRARY DESTINATION bin)

