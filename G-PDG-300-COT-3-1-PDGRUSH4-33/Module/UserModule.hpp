/*
** EPITECH PROJECT, 2026
** user
** File description:
** name
*/

#include "IModule.hpp"

class UserModule: public Krell::IModule
{
    private:
        std::string _name;
        std::string _user_name;
    public:
        UserModule(std::string name);
        void refresh() override;
        const std::string& getData() const override;
        const std::string& getName() const override;
};