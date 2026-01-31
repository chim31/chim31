/*
** EPITECH PROJECT, 2026
** core
** File description:
** core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include "Interfaces/IModule.hpp"
#include "Interfaces/IDisplay.hpp"
#include <vector>

class MonitorCore {
    protected:
        std::vector<Krell::IModule*> _modules;
        std::vector<Krell::IDisplay*> _display;
        bool _displayHidden;
    public:
        MonitorCore();
        ~MonitorCore();

        void addModule(Krell::IModule *module);
        void removeModule(Krell::IModule *module);
        void addDisplay(Krell::IDisplay *display);
        void hideDisplay();
        void showDisplay();
        bool isDisplayHidden() const;

        std::vector<Krell::IModule*> &getModules();
        const std::vector<Krell::IModule*> &getModules() const;
};

#endif /* !CORE_HPP_ */