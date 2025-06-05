#include "memory.hpp"
#include "cpu.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <dirent.h>
#include <unistd.h>
#include <algorithm>
#define PROC "/proc"

CPU_Usage Usage;


MEM_Usage::MEM_Usage() {
    // Just initialize PID list — don't fetch or print anything yet
    pid = Usage.get_pids();  // CPU_Usage Usage is a global or shared instance
    std::sort(pid.begin(), pid.end());
}


std::vector<float> MEM_Usage::get_usage() {
    DIR* dir = opendir(PROC);
    std::vector<float> UsageList;
    long page_size_kb = sysconf(_SC_PAGESIZE) / 1024;


    for (int i : pid) {
        std::string stat_path = std::string(PROC) + "/" + std::to_string(i) + "/stat";
        std::fstream file(stat_path, std::ios::in);

        if (!file.is_open()) {
            std::cout << "Unable to open /stat for PID " << i << " please confirm the existence of the file." << std::endl;
            continue;
        }

        std::string line;
        std::getline(file, line);
        file.close();

        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> fields;

        while (iss >> token) {
            fields.push_back(token);
        }

        if (fields.size() < 24) {
            continue;
        }

        long rss_pages = std::stol(fields[23]);
        float rss_kb = rss_pages * page_size_kb;
        float rss_mb = rss_kb / 1024.0f;

        UsageList.push_back(rss_mb);
    }

    return UsageList;
}

