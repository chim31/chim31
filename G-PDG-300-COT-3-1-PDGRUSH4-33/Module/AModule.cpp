/*
** EPITECH PROJECT, 2026
** AModule
** File description:
** Abstract module implementation
*/

#include "AModule.hpp"

AModule::AModule(const std::string &name) : _name(name)
{
}

const std::string &AModule::getName() const
{
    return this->_name;
}
