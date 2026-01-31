/*
** EPITECH PROJECT, 2026
** kernel
** File description:
** kernel
*/

#include "IModule.hpp"

class KernelModule: public Krell::IModule
{
    private:
        std::string _name;
        std::string _kernel_name;
    public:
        KernelModule(std::string name);
        void refresh() override;
        const std::string& getData() const override;
        const std::string& getName() const override;
};