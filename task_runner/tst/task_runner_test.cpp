#include <gtest/gtest.h>
#include "task_runner.h"

//https://github.com/kaizouman/gtest-cmake-example

/*
test scenarious
calling pause twice
calling stop twice

example
https://github.com/bmorcos/gtest-example

https://github.com/allen-hunter/Google-Unit-Test-Example

https://www.youtube.com/watch?v=16FI1-d2P4E
*/

class TaskRunnerTest : public ::testing::Test   {
protected:

	virtual void SetUp() {
        task.start_task();  
	}

	virtual void TearDown() {
        task.stop_task();
	}

public:
    TaskRunner task;

};


TEST_F(TaskRunnerTest, TaskRunning) {
    EXPECT_TRUE (task.state() == "Running");
}

TEST_F(TaskRunnerTest, TaskPaused) {
    task.pause_task();
    EXPECT_TRUE (task.state() == "Paused");
}

TEST_F(TaskRunnerTest, TaskResumed) {
    task.pause_task();
    // read input, 
    EXPECT_TRUE (task.state() == "Paused");
    task.resume_task();
    EXPECT_TRUE (task.state() == "Running");
}

TEST_F(TaskRunnerTest, TaskStopped) {
    task.stop_task();
    // read input, 
    EXPECT_TRUE (task.state() == "Stopped");
}

TEST_F(TaskRunnerTest, TaskStoppedWhenPaused) {
    task.pause_task();
    EXPECT_TRUE (task.state() == "Paused");
    task.stop_task();
    EXPECT_TRUE (task.state() == "Stopped");
}

TEST_F(TaskRunnerTest, TaskStoppedWhenResumed) {
    task.pause_task();
    EXPECT_TRUE (task.state() == "Paused");
    task.resume_task();
    EXPECT_TRUE (task.state() == "Running");
    task.stop_task();
    EXPECT_TRUE (task.state() == "Stopped");
}

TEST_F(TaskRunnerTest, TaskPausedWhenStopped) {
    task.stop_task();
    EXPECT_TRUE (task.state() == "Stopped");
    task.pause_task();
    EXPECT_TRUE (task.state() == "Stopped");
}

TEST_F(TaskRunnerTest, TaskPausedTwice) {
    task.pause_task();
    EXPECT_TRUE (task.state() == "Paused");
    task.pause_task();
    EXPECT_TRUE (task.state() == "Paused");  	
}

TEST_F(TaskRunnerTest, TaskStoppedTwice) {
    task.stop_task();
    EXPECT_TRUE (task.state() == "Stopped");
    task.stop_task();
    EXPECT_TRUE (task.state() == "Stopped");
}

TEST_F(TaskRunnerTest, TaskResumedTwice) {
    task.pause_task();
    EXPECT_TRUE (task.state() == "Paused");
    task.resume_task();
    EXPECT_TRUE (task.state() == "Running");
    task.resume_task();
    EXPECT_TRUE (task.state() == "Running");
}




/*
Test all transitions
call double command ( pause resume stop )

EXPECT_CALL().Times.WillOnce.WillOnce ( or WillRepeated)

have a mocking component
ApplicationManager : public Mock<ApplicationManger>

MOCK_METHOD0()

*/