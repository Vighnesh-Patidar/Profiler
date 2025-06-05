#ifndef MEM_HPP
#define MEM_HPP

#include <string>
#include <vector>


// memory.hpp
class MEM_Usage {
    std::vector<int> pid;

public:
    MEM_Usage();  
    void set_pid(const std::vector<int>& p) { pid = p; }
    std::vector<float> get_usage();
};


#endif