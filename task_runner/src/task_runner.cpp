#include "task_runner.h"



// TODO have an enum with different types of threads, 
//count all prime number until X
//

void TaskRunner::task()   {
    auto previous_time = std::chrono::steady_clock::now();
    auto start_time = std::chrono::steady_clock::now();

    while ( task_state != tStopped )    {

        TaskRunner::wait();

        int c = 0;
        std::array<int,100000> a;
        std::iota(a.begin(), a.end(), c++);
        for (auto &ele : a )   {
            auto current_time = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(current_time - previous_time).count() >= 3)   {
                previous_time = current_time;
                std::cout << ele << std::endl;
            }
        }

        if ( std::chrono::duration_cast<std::chrono::seconds>(previous_time - start_time).count() >= 10 )    {
            TaskRunner::completed();
            break;
        }
    }

}

void TaskRunner::completed()    {
    task_state = tCompleted;
    std::cout << "Task Completed" << std::endl;
    // should this be joined?
}

void TaskRunner::wait() {
    while( task_state == tPaused )  {
        std::unique_lock<std::mutex> lock(_m);
        cv.wait(lock);
    }
}


void TaskRunner::start_task()   {
    if ( task_state == tNotStarted )   {
        t = std::thread(&TaskRunner::task, this);
        task_state = tRunning;
    }
    else    {
        std::cout << "Cannot start a task that has already been started" << std::endl;
    }
}


void TaskRunner::stop_task()   {
    // Ensure we actually resume task before we stop, to not be so abrupt
    if ( task_state == tPaused )    {
        TaskRunner::resume_task();
    }
    
    if ( task_state == tRunning )   {
        task_state = tStopped;
        std::cout << "Task Stopped" << std::endl;
    }
    else    {
        std::cout << "Cannot stop a task that is not running or paused" << std::endl;
    }
}

void TaskRunner::pause_task()   {
    if ( task_state == tRunning )   {
        task_state = tPaused;
        std::cout << "Task Paused" << std::endl;
    }
    else    {
        std::cout << "Cannot pause a task that is not running " << std::endl;
    }
}

void TaskRunner::resume_task()   {
    if ( task_state == tPaused )   {
            cv.notify_one();
            task_state = tRunning;
        std::cout << "Task Resumed" << std::endl;
    }
    else    {
        std::cout << "Cannot resume a task that is not paused " << std::endl;
    }
}


TaskRunner::~TaskRunner()   {
    TaskRunner::stop_task();

    if ( t.joinable() ) {
        t.join();
    }
}
