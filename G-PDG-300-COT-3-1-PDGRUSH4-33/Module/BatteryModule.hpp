/*
** EPITECH PROJECT, 2026
** battery
** File description:
** module
*/

#include "IModule.hpp"

class BatteryModule: public Krell::IModule
{
    private:
        std::string _name; //name
        int _percent; //percentage
        int _time; //remaining time
        std::string _charging; //charging state
        int charge_rate; //power usage or charging speed
    public:
        BatteryModule(std::string name);
        void refresh() override;
        const std::string& getData() const override;
        const std::string& getName() const override;
};
