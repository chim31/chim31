/*
** EPITECH PROJECT, 2026
** os
** File description:
** os
*/

#include "../OsModule.hpp"


OsModule::OsModule(std::string name)
{
    this->_name = name;
}

void OsModule::refresh()
{
    std::ifstream file("/etc/os-release");
    std::string search_term = "PRETTY_NAME=";
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line) == 0) {
            if (line.find(search_term) == 0) {
                size_t start = line.find('"') + 1;
                size_t end = line.find_last_of('"');
                this->_os_name = line.substr(start, end - start);
                break;
            } else {
                this->_os_name = "Unknown OS";
            }
        }
    }
}

const std::string& OsModule::getData() const
{
    return this->_os_name;
}

const std::string& OsModule::getName() const
{
    return this->_name;
}