/*
** EPITECH PROJECT, 2026
** network
** File description:
** module
*/

#include "IModule.hpp"

class NetworkModule: public Krell::IModule
{
    private:
        std::string _name;
        std::string _user_name;
    public:
        NetworkModule(std::string name);
        void refresh() override;
        const std::string& getData() const override;
        const std::string& getName() const override;
};

