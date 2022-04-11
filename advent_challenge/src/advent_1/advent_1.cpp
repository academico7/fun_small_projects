#include <iostream>
#include <fstream>
#include <errno.h>
#include <string.h>
#include <vector>
#include <numeric>

int main(){

    std::ifstream f_in("/mnt/c/repo/fun/advent_challenge/src/input_1.txt", std::ios::in );
    int inp;

    if ( !f_in )
        std::cout << "Unable to open file, reason: " << strerror(errno) << std::endl;

    int increase_count = 0;
    std::vector<int> window; 

/*
    store the 2 last elements
    check when to start and check when to finish comparing the sliding windows
    have a count
*/
    int window_count = 0;
    int window_sum = 0;
    int prev_window_sum = 0;
    while (f_in >> inp) 
    {
        window.push_back(inp);
        window_count++;

        

        if ( window_count > 2 )    {
            
            window_sum = std::accumulate(window.end() - 3 , window.end(), 0);

            if ( window_sum > prev_window_sum && prev_window_sum != 0 ) {
                increase_count++;
            }
            prev_window_sum = window_sum;
        }



    }
    
    std::cout << " Increase count " << increase_count << std::endl;
}

