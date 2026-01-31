/*
** EPITECH PROJECT, 2026
** hostname
** File description:
** hostname
*/

#include "IModule.hpp"


class HostModule: public Krell::IModule
{
    private:
        std::string _name;
        std::string _hostname;
    public:
        HostModule(std::string name);
        void refresh() override;
        const std::string& getData() const override;
        const std::string& getName() const override;
};