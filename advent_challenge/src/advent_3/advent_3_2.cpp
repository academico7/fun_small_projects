#include<iostream>
#include <fstream>
#include <errno.h>
#include <string.h>
#include <vector>
#include <bitset>
#include <array>
#include <algorithm>
#include <iterator>

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
    
    101011101011
    101010011011

    vector of 
   */
  
        auto str = inp_int.to_string();
        std::reverse(str.begin(), str.end());
        inp_int = std::bitset<12>(str);

        bit_container.push_back(inp_int);
    }
    std::vector<int> oxygen_index(bit_container.size());
    std::vector<int> co2_index(bit_container.size());
    std::generate(oxygen_index.begin(), oxygen_index.end(), [n = 0]() mutable{return n++;});
    std::generate(co2_index.begin(), co2_index.end(), [n = 0]() mutable{return n++;});

    int bit_pos = 0;
    int bit_common = 0;

    // find all the numbers that have '1' within the bit_pos
    // auto it = std::find_if(std::begin(bit_container), std::end(bit_container), [bit_pos](auto i){return i[bit_pos] == 1;});
    // while ( it != std::end(bit_container) ) {
    //     oxygen_index.emplace_back(std::distance(std::begin(bit_container), it));
    //     it = std::find_if(std::next(it), std::end(bit_container), [bit_pos](auto i){return i[bit_pos] == 1;});
    // }
// go through the 1st bit pos of all the nrs
// Check which is more common
// Insert those indexes in the Oxygen or Co2 


    while ( oxygen_index.size() != 1 )    {

        std::vector<int> true_indexes;
        std::vector<int> false_indexes;

        for( auto ele : oxygen_index) {
                if ( bit_container[ele][bit_pos] == 1 ) {
                    true_indexes.push_back(ele);
                    bit_common++;
                }
                else    {
                    false_indexes.push_back(ele);
                    bit_common--;
                }
            
        }
        

        // if there are more 1's then remove the 0's
        if ( bit_common > 0 )   {
            oxygen_index.erase( remove_if( begin(oxygen_index),end(oxygen_index),
                                [&](auto x){return find(begin(false_indexes),end(false_indexes),x)!=end(false_indexes);}), end(oxygen_index) );
        }
        // if there are more 0's then remove the 1's
        else if ( bit_common < 0 )  {
            oxygen_index.erase( remove_if( begin(oxygen_index),end(oxygen_index),
                                [&](auto x){return find(begin(true_indexes),end(true_indexes),x)!=end(true_indexes);}), end(oxygen_index) );
 
        }
        // if they are equal , remove the 0's
        else    {
        oxygen_index.erase( remove_if( begin(oxygen_index),end(oxygen_index),
                                [&](auto x){return find(begin(false_indexes),end(false_indexes),x)!=end(false_indexes);}), end(oxygen_index) );
        }

        // I have the first oxygen and 
        bit_pos++;
        bit_common=0;
    }

    for ( auto &ele : oxygen_index ) {
        std::cout << ele << std::endl;
    }

bit_pos=0;
    while ( co2_index.size() != 1 )    {

        std::vector<int> true_indexes;
        std::vector<int> false_indexes;

        for( auto ele : co2_index) {
                if ( bit_container[ele][bit_pos] == 1 ) {
                    true_indexes.push_back(ele);
                    bit_common++;
                }
                else    {
                    false_indexes.push_back(ele);
                    bit_common--;
                }
            
        }
        

        // if there are more 1's then remove the 0's
        if ( bit_common > 0 )   {
            co2_index.erase( remove_if( begin(co2_index),end(co2_index),
                                [&](auto x){return find(begin(true_indexes),end(true_indexes),x)!=end(true_indexes);}), end(co2_index) );
        }
        // if there are more 0's then remove the 1's
        else if ( bit_common < 0 )  {
            co2_index.erase( remove_if( begin(co2_index),end(co2_index),
                                [&](auto x){return find(begin(false_indexes),end(false_indexes),x)!=end(false_indexes);}), end(co2_index) );
 
        }
        // if they are equal , remove the 0's
        else    {
        co2_index.erase( remove_if( begin(co2_index),end(co2_index),
                                [&](auto x){return find(begin(true_indexes),end(true_indexes),x)!=end(true_indexes);}), end(co2_index) );
        }

        // I have the first oxygen and 
        bit_pos++;
        bit_common=0;
    }

    for ( auto &ele : co2_index ) {
        std::cout << ele << std::endl;
    }

    auto str = bit_container[oxygen_index.at(0)].to_string();
    std::reverse(str.begin(), str.end());

    std::cout << " oxygen  number " << std::bitset<12>(str);

    str = bit_container[co2_index.at(0)].to_string();
    std::reverse(str.begin(), str.end());
    std::cout << " co2  number " << std::bitset<12>(str);


} 

// 6 and 9

    //std::cout << "ola " << *it << std::endl;




    //std::cout << inp_int << std::endl;
    // for ( int i = 0 ; i < inp_int.size()  ; i++ ) {
    //     //std::cout << inp_int[i] << std::endl;
    //     if ( inp_int[i] )   {
    //         //std::cout << " bit_counter before " << bit_counter[i] << std::endl;
    //         bit_counter[i] = ++bit_counter[i];
    //         //std::cout << "pos TRUE - " << i << " bit_counter " << bit_counter[i] << std::endl;
    //     }
    //     else    {
    //         //std::cout << " bit_counter before " << bit_counter[i] << std::endl;
    //         bit_counter[i] = --bit_counter[i];
    //         //std::cout << "pos FALSE - " << i << " bit_counter " << bit_counter[i] << std::endl;
    //     }
// 001000010101
    //std::cout << inp_int << std::endl;
    //}

    // for ( int i = 0; i < bit_counter.size(); i++ )  {
    //     std::cout << bit_counter[i] << std::endl;
    //     gamma[i] = bit_counter[i] > 0 ? 1 : 0;
    //     //std::cout << "gamma " << gamma[i] << std::endl;
    //     epsilon[i] = !gamma[i];
    //     //std::cout << "epsilon " << epsilon[i] << std::endl;
    // }

    //     auto str = gamma.to_string();
    //     std::reverse(str.begin(), str.end());
    //     gamma = std::bitset<12>(str);
    //     str = epsilon.to_string();
    //     std::reverse(str.begin(), str.end());
    //     epsilon = std::bitset<12>(str);

    // for ( int i = 0; i < epsilon.size(); i++ )  {
    //     std::cout << epsilon[i];
    // }

    // std::cout << " decimal epsilon " << epsilon.to_ulong() << std::endl;

    // std::cout << std::endl;
    // for ( int i = 0; i < gamma.size(); i++ )  {
    //     std::cout <<  gamma[i];
    // }

    // std::cout << " decimal gamma " << gamma.to_ulong() << std::endl;

    // std::cout << "final " << epsilon.to_ulong() * gamma.to_ulong() << std::endl;

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
