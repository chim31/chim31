/*
** EPITECH PROJECT, 2026
** username
** File description:
** username
*/

#include "../UserModule.hpp"

UserModule::UserModule(std::string name)
{
    this->_name = name;
}

void UserModule::refresh()
{
    const char *user_ = std::getenv("USER");

    if (user_)
        this->_user_name = user_;
    else
        this->_user_name = "";
}

const std::string& UserModule::getData() const
{
    return this->_user_name;
}

const std::string& UserModule::getName() const
{
    return this->_name;
}