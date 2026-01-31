/*
** EPITECH PROJECT, 2026
** AModule
** File description:
** Abstract class for modules, factorizes common behavior
*/

#ifndef AMODULE_HPP_
#define AMODULE_HPP_

#include "../Interfaces/IModule.hpp"

class AModule : public Krell::IModule
{
    protected:
        std::string _name;
    public:
        AModule(const std::string &name);
        virtual ~AModule() = default;
        const std::string &getName() const override;
        virtual const std::string &getData() const = 0;
        virtual void refresh() override = 0;
};

#endif /* !AMODULE_HPP_ */
