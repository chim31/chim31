/*
** EPITECH PROJECT, 2026
** datetime
** File description:
** module
*/

#include "IModule.hpp"

class DateTimeModule: public Krell::IModule
{
    private:
        std::string _name;
        std::string date_time;
    public:
        DateTimeModule(std::string name);
        void refresh() override;
        const std::string& getData() const override;
        const std::string& getName() const override;
};