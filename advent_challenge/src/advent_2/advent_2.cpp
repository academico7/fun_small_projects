#include<iostream>
#include <fstream>
#include <errno.h>
#include <string>
#include <string.h>

int main(){

    std::ifstream f_in("/mnt/c/repo/fun/advent_challenge/src/advent_2/input_2.txt", std::ios::in );
    std::string inp_str;
    int inp_int;

    if ( !f_in )
        std::cout << "Unable to open file, reason: " << strerror(errno) << std::endl;

    int horizontal = 0;
    int depth = 0;
    int aim = 0;
    while (f_in >> inp_str) 
    {
        std::cout << inp_str << std::endl;
        if ( inp_str.find("forward") == 0 )  {
            f_in >> inp_int;
            horizontal += inp_int;
            depth += (aim * inp_int);
        }
        else if ( inp_str.find("up") == 0 )  {
            f_in >> inp_int;
            aim -= inp_int;
        }
        else if ( inp_str.find("down") == 0 )  {
            f_in >> inp_int;
            aim += inp_int;
        }
    }

    std::cout << "depth " << depth << " horizontal " << horizontal << " total " << (depth * horizontal) << std::endl;
}
