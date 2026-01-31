/*
** EPITECH PROJECT, 2026
** cpu
** File description:
** module
*/

#include "../CpuModule.hpp"
#include <fstream>
#include <sstream>

CpuModule::CpuModule(int nb_threads) : _name("CPU"), _dataStr("N/A")
{
    (void)nb_threads;
}

void CpuModule::refresh()
{
    std::ifstream file("/proc/stat");
    std::string line;

    if (!std::getline(file, line) || line.compare(0, 3, "cpu") != 0) {
        this->_dataStr = "N/A";
        return;
    }
    std::istringstream ss(line);
    std::string cpu;
    unsigned long user, nice, sys, idle, iowait, irq, softirq, steal;
    ss >> cpu >> user >> nice >> sys >> idle >> iowait >> irq >> softirq >> steal;
    unsigned long total = user + nice + sys + idle + iowait + irq + softirq + steal;
    unsigned long used = total - idle;
    if (total > 0)
        this->_dataStr = std::to_string((used * 100) / total) + "%";
    else
        this->_dataStr = "N/A";
}

const std::string& CpuModule::getData() const
{
    return this->_dataStr;
}

const std::string& CpuModule::getName() const
{
    return this->_name;
}
