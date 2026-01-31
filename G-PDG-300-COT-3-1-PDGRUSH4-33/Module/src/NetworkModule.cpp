/*
** EPITECH PROJECT, 2026
** network
** File description:
** module
*/

#include "../NetworkModule.hpp"
#include <fstream>
#include <sstream>

NetworkModule::NetworkModule(std::string name) : _name(name), _user_name("N/A")
{
}

void NetworkModule::refresh()
{
    std::ifstream file("/proc/net/dev");
    std::string line;

    this->_user_name = "N/A";
    if (!file.is_open())
        return;
    std::getline(file, line);
    std::getline(file, line);
    if (!std::getline(file, line))
        return;
    std::istringstream ss(line);
    std::string iface;
    unsigned long rx = 0, tx = 0;
    ss >> iface;
    if (iface.back() == ':')
        iface.pop_back();
    ss >> rx;
    for (int i = 0; i < 7 && ss; i++) {
        unsigned long tmp;
        ss >> tmp;
    }
    ss >> tx;
    if (ss)
        this->_user_name = iface + " RX:" + std::to_string(rx / 1024) + "kB TX:" + std::to_string(tx / 1024) + "kB";
}

const std::string& NetworkModule::getData() const
{
    return this->_user_name;
}

const std::string& NetworkModule::getName() const
{
    return this->_name;
}
