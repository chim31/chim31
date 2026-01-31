/*
** EPITECH PROJECT, 2026
** display
** File description:
** disp
*/

#include "ADisplay.hpp"

ADisplay::ADisplay(std::string name): _name(name)
{

}

bool ADisplay::isRun() const
{
    return this->_isrun;
}

std::string& ADisplay::getName() const
{
    return this->_name;
}