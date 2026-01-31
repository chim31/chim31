/*
** EPITECH PROJECT, 2026
** ram
** File description:
** module
*/

#include "IModule.hpp"

class RamModule: public Krell::IModule
{
private:
    std::string _name;
    std::string ram_total;
    std::string free_ram;
    std::string avail_ram;
public:
    RamModule(std::string name);
    void refresh() override;
    const std::string& getData() const override;
    const std::string& getName() const override;
};
