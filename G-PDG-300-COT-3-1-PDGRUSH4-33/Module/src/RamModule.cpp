/*
** EPITECH PROJECT, 2026
** fghjk
** File description:
** emacs
*/

#include "../RamModule.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>


RamModule::RamModule(std::string name): _name(name) {}

long get_ram_info(const std::string &info)
{
    std::ifstream file("/proc/meminfo");
    std::string line;
    while (std::getline(file, line)) {
        if (line.compare(0, info.length(), info) == 0) {
            std::stringstream ss (line);
            std::string name;
            long value;
            ss >> name >> value;
            file.close();
            return value;
        }
    }
    file.close();
    return -1;
}

void RamModule::refresh()
{
    ram_total = std::to_string(get_ram_info("MemTotal:") / 1024);
    free_ram = std::to_string(get_ram_info("MemFree:") / 1024);
    avail_ram = std::to_string(get_ram_info("MemAvailable:") / 1024);
}

const std::string& RamModule::getData() const
{
    std::string total = "MemTotal: " + ram_total + "," + "MemFree: " + free_ram + "," + "MemAvailable: " + avail_ram;
    return total;
}

const std::string& RamModule::getName() const
{
    return _name;
}
