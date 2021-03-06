#### Task Runner
Task Runer is a simple C++ library that allows the user to manage an arbitrary number of asynchronous tasks.

GitHub - https://github.com/academico7/fun_small_projects/tree/main/task_runner

#### Dependencies
git 

Cmake 3.16

C++ compiler GNU 9.3

POSIX platform

### How to build, run the test example and the unit tests
From task_runner/ , create your build directory

>cd task_runner && mkdir _build && cd _build

Run CMake to setup the Makefile:

>cmake .\.

Build the test executables

>cmake --build .

Run command line example of task runner

>./task_runner_example

Run tests

>make test -j 

or

>./tst/unit_tests

#### Instruction Description
The command line example can receive the following instructions as inputs:

Prints help messages and instructions
>./task_runner_example --help

Starts and waits for instructions

>./task_runner_example

Once the program is running, it should read instructions from the standard input. These instructions should have the following format:

>- Starts a task and prints its ID

>start

>- Pause the task with the given id and print a confirmation message

>pause <task_id>

>- Resume task with the given id (if paused) and print a confirmation message

>resume <task_id>

>- Stop the task with the given id (if not stopped) and print a confirmation

>stop <task_id>

>- Prints the id, the status (paused, running, stopped, completed)

>status 

>- As above, but for a single task

>status <task_id>

>- Gracefully shut down

>quit

 