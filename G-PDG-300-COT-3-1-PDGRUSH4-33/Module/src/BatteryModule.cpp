/*
** EPITECH PROJECT, 2026
** battery
** File description:
** module
*/

#include "../BatteryModule.hpp"
#include <fstream>
#include <sstream>

BatteryModule::BatteryModule(std::string name)
    : _name(name), _dataStr("N/A"), _percent(0), _time(0), _charging("Unknown"), charge_rate(0)
{
}

void BatteryModule::refresh()
{
    std::ifstream cap("/sys/class/power_supply/BAT0/capacity");
    std::ifstream status("/sys/class/power_supply/BAT0/status");

    this->_dataStr = "N/A";
    if (cap.is_open()) {
        cap >> this->_percent;
        this->_dataStr = std::to_string(this->_percent) + "%";
    }
    if (status.is_open()) {
        status >> this->_charging;
        this->_dataStr += " " + this->_charging;
    }
}

const std::string& BatteryModule::getData() const
{
    return this->_dataStr;
}

const std::string& BatteryModule::getName() const
{
    return this->_name;
}
