#include <gtest/gtest.h>
#include "task_runner.h"

/*
TODO: the test is based on an internal class state, 
could be relevant to add some verification that the task is doing its job
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