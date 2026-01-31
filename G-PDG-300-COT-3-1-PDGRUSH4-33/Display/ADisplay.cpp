/*
** EPITECH PROJECT, 2026
** display
** File description:
** disp
*/

#include "ADisplay.hpp"

ADisplay::ADisplay(const std::string &name) : _name(name), _isrun(false)
{
}

bool ADisplay::isRun() const
{
    return this->_isrun;
}

const std::string &ADisplay::getName() const
{
    return this->_name;
}
