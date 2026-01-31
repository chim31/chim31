/*
** EPITECH PROJECT, 2026
** cpu
** File description:
** module
*/

#include "IModule.hpp"

class CpuModule: public Krell::IModule
{
    private:
        std::vector<double> _usages;
    public:
        CpuModule(int nb_threads);
        void refresh() override;
        const std::string& getData() const override;
        const std::string& getName() const override;
};

class CpuGlobal: public Krell::IModule
{
    private:
        double u;
        double ni;
        double sy;
        double id;
        double wa;
        double hi;
        double si;
        double st;
        std::string model;
        int physical;
        int logic;
        int frequence;
        int nu_threads;
    public:
        CpuGlobal(std::string name);
        void refresh() override;
        const std::string& getData() const override;
        const std::string& getName() const override;
};