#include<iostream>
#include <fstream>
#include <errno.h>
#include <string.h>
#include <vector>
#include <bitset>
#include <array>
#include <algorithm>

int main(){

    std::ifstream f_in("/mnt/c/repo/fun/advent_challenge/src/advent_3/input_3.txt", std::ios::in );
    std::bitset<12> inp_int;
    std::vector<std::bitset<12> > bit_container;
    std::array<int, 12> bit_counter = {0};
    std::bitset<12> gamma;
    std::bitset<12> epsilon;

    if ( !f_in )
        std::cout << "Unable to open file, reason: " << strerror(errno) << std::endl;

    while (f_in >> inp_int)
    {

        auto str = inp_int.to_string();
        std::reverse(str.begin(), str.end());
        inp_int = std::bitset<12>(str);

        //std::cout << inp_int << std::endl;
        for ( int i = 0 ; i < inp_int.size()  ; i++ ) {
            //std::cout << inp_int[i] << std::endl;
            if ( inp_int[i] )   {
                //std::cout << " bit_counter before " << bit_counter[i] << std::endl;
                bit_counter[i] = ++bit_counter[i];
                //std::cout << "pos TRUE - " << i << " bit_counter " << bit_counter[i] << std::endl;
            }
            else    {
                //std::cout << " bit_counter before " << bit_counter[i] << std::endl;
                bit_counter[i] = --bit_counter[i];
                //std::cout << "pos FALSE - " << i << " bit_counter " << bit_counter[i] << std::endl;
            }
        }
    // 001000010101
        //std::cout << inp_int << std::endl;
    }
    for ( int i = 0; i < bit_counter.size(); i++ )  {
        std::cout << bit_counter[i] << std::endl;
        gamma[i] = bit_counter[i] > 0 ? 1 : 0;
        //std::cout << "gamma " << gamma[i] << std::endl;
        epsilon[i] = !gamma[i];
        //std::cout << "epsilon " << epsilon[i] << std::endl;
    }

        auto str = gamma.to_string();
        std::reverse(str.begin(), str.end());
        gamma = std::bitset<12>(str);
        str = epsilon.to_string();
        std::reverse(str.begin(), str.end());
        epsilon = std::bitset<12>(str);

    for ( int i = 0; i < epsilon.size(); i++ )  {
        std::cout << epsilon[i];
    }

    std::cout << " decimal epsilon " << epsilon.to_ulong() << std::endl;

    std::cout << std::endl;
    for ( int i = 0; i < gamma.size(); i++ )  {
        std::cout <<  gamma[i];
    }

    std::cout << " decimal gamma " << gamma.to_ulong() << std::endl;

    std::cout << "final " << epsilon.to_ulong() * gamma.to_ulong() << std::endl;

    /*
    1st
    gama rate - most common bit per  pos
    1st positiong - bit 0
    2nd pos - bit 1

    epsilon rate - least common bit per  pos

    */

   /*
   2nd 

    1st bit of each unmber
        consider the bit criteria
        if we end up with one number left - thts the one!
        if Not, shift one bit to the right and repear
    
    bit criteria:
        oxygen - most common value of the current bit position, keep those numbers
            if euqlly common, keep 1 over 0
        
        Co2 - least common - keep those numbers
            if equally least common, keep 0, keep
   */
}