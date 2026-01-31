/*
** EPITECH PROJECT, 2026
** hostname
** File description:
** hostname
*/

#include "../HostnameModule.hpp"
#include <unistd.h>
#include <climits>

HostModule::HostModule(std::string name)
{
    this->_name = name;
}

void HostModule::refresh()
{
    char host_buff[HOST_NAME_MAX];

    if (gethostname(host_buff, sizeof(host_buff)) == 0)
        this->_hostname = host_buff;
    else {
        this->_hostname = "";
        perror("Error");
        return;
    }
}

const std::string& HostModule::getData() const
{
    return this->_hostname;
}

const std::string& HostModule::getName() const
{
    return this->_name;
}