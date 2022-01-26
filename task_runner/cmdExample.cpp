#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <numeric>
#include <array>
#include <atomic>
#include <chrono>
#include "task_runner.h"
#include <string>
#include <unordered_map>
#include <cctype>
#include <sstream>
/*
Missing:
Have another task type
Missing comments


*/

void print_help()   {
    std::cout << "Command line example help:" << std::endl;
    std::cout << "Start  - starts a task and prints its ID " << std::endl;
    std::cout << "Pause  - pauses a task with a given ID" << std::endl;
    std::cout << "Resume - resumes a task with a given ID" << std::endl;
    std::cout << "Stop   - Stops a task with a given ID" << std::endl;
    std::cout << "Status - prints the id, the status (paused, running, stopped, completed)" << std::endl;
    std::cout << "Status <task_id> - As above, but for a single task" << std::endl;
    std::cout << "Quit - gracefully shut down" << std::endl;
}


// TODO should be on task_runner.h
enum options{
    eStart,
    eStop,
    eResume,
    ePause,
    eStatus
};

std::unordered_map<std::string, enum options> m_options{ 
    {"start", eStart},
    {"stop", eStop},
    {"resume", eResume},
    {"status", eStatus},
    {"pause", ePause},
};

bool is_number( const std::string inp)   {
    for( auto ele : inp ) {
        if ( std::isdigit(ele) == 0 )   {
            return false;
        }
    }
    return true;
}


int main(int argc, char * argv[])
{
    // Simple command line parser, if it grows bigger I suggest using an external library ( e.g. boost::program_options )
    if ( argc > 2 ) {
        std::cout << "The only supported argument is --help" << std::endl;
        return 0;
    }
    else if ( argc == 2 )   {
        if ( std::string(argv[1]) == "--help" ) {
            print_help();
            return 0;
        }
        else    {
            std::cout << "The only supported argument is --help" << std::endl;
            return 0;
        }
    }


    std::unordered_map<int, std::unique_ptr<TaskRunner> > task_pool;
    signed int task_id_generator = 1;

    // Handling user input 
    while ( 1 )   {        
        // User input process
        std::string line_input, command, t_id;
        int input_task_id = -1;

        std::getline( std::cin, line_input);
        std::stringstream myStream(line_input);

        std::getline( myStream, command, ' ');

        if ( command.compare("quit") == 0 )
            return 0;

        std::getline( myStream, t_id, ' ');

        // Check if task id is valid
        if ( !is_number(t_id) )  {
            std::cout << "Invalid task id, please run --help" << std::endl;
        }

        // Check if a task ID was given
        if ( !t_id.empty() )    {
            input_task_id = stoi(t_id);

            if ( task_pool.find(input_task_id) == task_pool.end() ) {
                std::cout << "The task ID mentioned does not exist" << std::endl<< std::flush;
                continue;
            }
        }

        if ( m_options.find(command) == m_options.end() ) {
            std::cout << "Invalid command, have a look at --help" << std::endl;
            continue;
        }

        switch (m_options[command])
        {
            case eStart:
                task_pool.emplace( std::make_pair(task_id_generator, std::make_unique<TaskRunner>() ) );
                task_pool[task_id_generator]->start_task();
                std::cout << "Task with id " << task_id_generator++ << " has started" <<std::endl;
                break;
            case eStop: // stop
                if ( input_task_id == -1 )    {
                    std::cout << "Please provide a task id, have a look at --help" << std::endl;
                    continue;
                }
                task_pool[input_task_id]->stop_task();
                break;
            case eResume:
                if ( input_task_id == -1 )    {
                    std::cout << "Please provide a task id, have a look at --help" << std::endl;
                    continue;
                }
                task_pool[input_task_id]->resume_task();
                break;
            case ePause:
                if ( input_task_id == -1 )    {
                    std::cout << "Please provide a task id, have a look at --help" << std::endl;
                    continue;
                }
                task_pool[input_task_id]->pause_task();
                break;
            case eStatus:
                if ( input_task_id == -1 )    {
                    for(auto it = task_pool.begin(); it != task_pool.end(); ++it) {
                        std::cout << "Task " << it->first << " is " << it->second->state() << std::endl;
                    }
                }
                else    {
                    std::cout << "Task is " << task_pool[input_task_id]->state() << std::endl;
                }
                break;
            default:
                abort ();
        }

    }

}