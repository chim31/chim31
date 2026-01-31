/*
** EPITECH PROJECT, 2026
** ram
** File description:
** module
*/

#include "IModule.hpp"

class RamModule : public Krell::IModule
{
private:
    std::string _name;
    std::string _dataStr;
    long get_ram_info(const std::string &key) const;
public:
    RamModule(const std::string &name);
    void refresh() override;
    const std::string &getData() const override;
    const std::string &getName() const override;
};
