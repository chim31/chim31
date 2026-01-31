/*
** EPITECH PROJECT, 2026
** kernel
** File description:
** kernel
*/

#include "../KernelModule.hpp"


KernelModule::KernelModule(std::string name)
{
    this->_name = name;
}

void KernelModule::refresh()
{
    struct utsname buff;

    if (uname(&buff) != 0) {
        perror("uname");
        return;
    }
    this->_kernel_name = std::string(buff.release);
}

const std::string& KernelModule::getData() const
{
    return this->_kernel_name;
}

const std::string& KernelModule::getName() const
{
    return this->_name;
}