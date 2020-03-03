
#ifndef UTILITY_HPP_
#define UTILITY_HPP_

#include <chrono>


template <class F>
int timed_run(F &&f){
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    //call the function
    f();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::seconds>(end - begin).count();
} 


#endif 