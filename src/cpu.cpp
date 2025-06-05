#include "cpu.hpp"
#include <string>
#include <algorithm>
#include <vector>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#define PROC "/proc"


#include "cpu.hpp"
#include "memory.hpp"
#include <iomanip>

CPU_Usage::CPU_Usage() {
    std::vector<std::string> P_name = get_name();
    std::vector<int> P_ID = get_pids();
    std::vector<float> P_usage = get_usage();

    // Fetch memory usage
    MEM_Usage mem;
    mem.set_pid(P_ID);
    std::vector<float> mem_usage = mem.get_usage();

    std::cout << "------------------------------------------ Process Statistics -------------------------------------------\n";
    std::cout << std::left
              << std::setw(25) << "Process Name"
              << std::setw(15) << "PID"
              << std::setw(20) << "CPU Usage (%)"
              << std::setw(20) << "Mem Usage (MB)"
              << "\n";

    std::cout << std::string(80, '-') << "\n";

    size_t count = std::min({P_name.size(), P_ID.size(), P_usage.size(), mem_usage.size()});
    for (size_t i = 0; i < count; ++i) {
        std::cout << std::left
                  << std::setw(25) << P_name[i]
                  << std::setw(15) << P_ID[i]
                  << std::setw(20) << std::fixed << std::setprecision(2) << P_usage[i]
                  << std::setw(20) << std::fixed << std::setprecision(2) << mem_usage[i]
                  << "\n";
    }
}

std::vector<int> CPU_Usage::get_pids(){

    DIR* dir = opendir(PROC);
    
    std::vector<int> pids;

    if(!dir) return pids;

    struct dirent* entry;

    while((entry = readdir(dir)) != nullptr){
        std::string name = entry->d_name;

        if(!name.empty() && std::all_of(name.begin(), name.end(), ::isdigit)){
            pids.push_back(std::stoi(name));
        }
    }
    return pids;
}



std::vector<float> CPU_Usage::get_usage(){
    
    DIR* dir = opendir(PROC);

    std::vector<float> Usage_List;

    std::vector<int> pids = CPU_Usage::get_pids();

    for(int i : pids){
       
        std::string stat_path = std::string(PROC) + "/" + std::to_string(i) + "/stat";
       
        std::fstream file(stat_path, std::ios::in);
       
        if(!file.is_open()){
            std::cout << "Unable to open /stat for PID " << i << " please confirm the existence of the file." << std::endl;  
            continue;
        }



        std::string line;

        std::getline(file, line);
        
        file.close();

        
        std::istringstream iss(line);
        
        std::string token;
        
        std::vector<std::string> fields;

        
        while(iss >> token){
            fields.push_back(token);     
        }
        
        
        if(fields.empty()) continue;

        try{
            long utime = std::stoi(fields[13]);
            long ltime = std::stoi(fields[14]);
            float total_time = static_cast<float>(utime + ltime);
            Usage_List.push_back(total_time);
        }   catch(...){
            continue;
        }

    }
    return Usage_List;
}




std::vector<std::string> CPU_Usage::get_name() {
    std::vector<std::string> Process_Names;

    std::vector<int> pids = CPU_Usage::get_pids();

    for (int pid : pids) {

        std::string file_path = std::string(PROC) + "/" + std::to_string(pid) + "/stat";

        std::ifstream file(file_path);


        if (!file.is_open()) {
        
            std::cerr << "Unable to open /stat for PID " << pid << std::endl;
        
            continue;
        
        }
  
        std::string line;
        
        std::getline(file, line);

        
        size_t start = line.find('(');
        
        size_t end = line.find(')');
        
        if (start != std::string::npos && end != std::string::npos && end > start) {
        
            std::string name = line.substr(start + 1, end - start - 1);
        
            Process_Names.push_back(name);
        
        }
    
    }


    return Process_Names;

}
