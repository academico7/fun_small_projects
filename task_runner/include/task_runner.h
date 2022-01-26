#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <numeric>
#include <array>
#include <atomic>
#include <chrono>
#include <unordered_map>

//todo add namespace

enum t_state{
    tRunning,
    tPaused,
    tStopped,
    tCompleted,
    tNotStarted
};

std::unordered_map< enum t_state, std::string> state_options{ 
    { tRunning, "Running" },
    { tPaused, "Paused"},
    { tStopped, "Stopped"},
    { tCompleted, "Completed"},
    { tNotStarted, "NotStarted"},
};

class TaskRunner
{
    std::thread t;
    std::condition_variable cv;
    std::mutex _m;
    std::atomic<t_state> task_state{tNotStarted};

void completed();

void wait();

bool is_paused() const { return task_state == tPaused;};

bool is_stopped() const { return task_state == tStopped;};

public:

TaskRunner(const TaskRunner& t) {};

TaskRunner() {};

std::string state() const { return state_options[task_state]; };

void task();

void start_task();

void stop_task();

void pause_task();

void resume_task();

~TaskRunner();

};