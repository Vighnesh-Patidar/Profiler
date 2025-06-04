#ifndef MEM_HPP
#define MEM_HPP

#include <string>
#include <vector>

class MEM_Usage{
    private:
        int pid;
        float usage;
        std::string name;
        int get_pid() const;
        float get_usage() const;
        std::string get_name() const;

    public:
        MEM_Usage(int pid, float usage, const std::string& name);
};

#endif