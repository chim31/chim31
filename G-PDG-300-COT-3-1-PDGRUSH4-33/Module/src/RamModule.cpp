/*
** EPITECH PROJECT, 2026
** fghjk
** File description:
** emacs
*/

#include "../RamModule.hpp"
#include <fstream>
#include <sstream>

RamModule::RamModule(const std::string &name) : _name(name) {}

long RamModule::get_ram_info(const std::string &key) const
{
    std::ifstream file("/proc/meminfo");
    std::string line;

    while (std::getline(file, line)) {
        if (line.compare(0, key.length(), key) == 0) {
            std::stringstream ss(line);
            std::string label;
            long value = 0;
            ss >> label >> value;
            return value;
        }
    }
    return -1;
}

void RamModule::refresh()
{
    long total = this->get_ram_info("MemTotal:");
    long free_mem = this->get_ram_info("MemFree:");
    long available = this->get_ram_info("MemAvailable:");
    long swap_total = this->get_ram_info("SwapTotal:");
    long swap_free = this->get_ram_info("SwapFree:");

    _dataStr.clear();
    if (total > 0) {
        long used = total - available;
        long usage_percent = (used * 100) / total;
        _dataStr += "Total: " + std::to_string(total / 1024) + " MB\n";
        _dataStr += "Used: " + std::to_string(used / 1024) + " MB\n";
        _dataStr += "Free: " + std::to_string(free_mem / 1024) + " MB\n";
        _dataStr += "Available: " + std::to_string(available / 1024) + " MB\n";
        _dataStr += "Usage: " + std::to_string(usage_percent);
    }
    if (swap_total > 0) {
        long swap_used = swap_total - swap_free;
        long swap_percent = (swap_used * 100) / swap_total;
        _dataStr += "\nSwapTotal: " + std::to_string(swap_total / 1024) + " MB";
        _dataStr += "\nSwapUsed: " + std::to_string(swap_used / 1024) + " MB";
        _dataStr += "\nSwapUsage: " + std::to_string(swap_percent);
    } else {
        _dataStr += "\nSwapTotal: 0 MB\nSwapUsage: 0";
    }
}

const std::string &RamModule::getData() const
{
    return _dataStr;
}

const std::string &RamModule::getName() const
{
    return _name;
}
