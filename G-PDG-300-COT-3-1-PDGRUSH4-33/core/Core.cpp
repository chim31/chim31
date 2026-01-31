/*
** EPITECH PROJECT, 2026
** core
** File description:
** core
*/

#include "Core.hpp"

MonitorCore::~MonitorCore()
{
    for (auto x: this->_modules)
        delete x;
    for (auto x: this->_display)
        delete x;
}