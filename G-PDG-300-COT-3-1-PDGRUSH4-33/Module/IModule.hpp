/*
** EPITECH PROJECT, 2026
** module
** File description:
** module
*/
#include <iostream>

namespace Krell
{
    class IModule;
};

class Krell::IModule {
    public:
        virtual ~IModule() = default;
        virtual void refresh() = 0;
        virtual const std::map <std::string, std::string>& getData() const = 0;
        virtual const std::string& getName() const = 0;
};