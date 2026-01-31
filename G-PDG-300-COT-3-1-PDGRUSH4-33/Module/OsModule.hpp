/*
** EPITECH PROJECT, 2026
** os
** File description:
** module
*/

#include "IModule.hpp"

class OsModule: public Krell::IModule
{
    private:
        std::string _name;
        std::string _os_name;
    public:
        OsModule(std::string name);
        void refresh() override;
        const std::string& getData() const override;
        const std::string& getName() const override;
};