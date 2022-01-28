add_executable(unit_tests 
    task_runner_test.cpp
    )

target_link_libraries(unit_tests
    PUBLIC
    task_runner_lib
    gtest_main
    gtest
)

add_test(test_all unit_tests COMMAND unit_tests)



