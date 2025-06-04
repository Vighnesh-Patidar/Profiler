#ifndef CPU_HPP
#define CPU_HPP

#include <string>
#include <vector>

class CPU_Usage{
    private:
        std::vector<int> pid;
        std::vector<int> usage;
        std::vector<std::string> name;

    public:
        CPU_Usage();

        std::vector<int> get_pids();
        std::vector<float> get_usage();
        std::vector<std::string> get_name();

};


#endif