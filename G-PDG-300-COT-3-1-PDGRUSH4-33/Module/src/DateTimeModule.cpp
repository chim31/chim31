/*
** EPITECH PROJECT, 2026
** date
** File description:
** time
*/

#include "../DateTimeModule.hpp"


DateTimeModule::DateTimeModule(std::string name)
{
    this->_name = name;
}

void DateTimeModule::refresh()
{
    std::time_t now = std::time(nullptr);

    std::tm* localtime = std::localtime(&now);
    std::stringstream ss;

    ss << std::put_time(localtime, "%d/%m/%Y %H:%M:%S");
    ss.str >> this->date_time;
}

const std::string& DateTimeModule::getData() const
{
    return this->date_time;
}

const std::string& DateTimeModule::getName() const
{
    return this->_name;
}