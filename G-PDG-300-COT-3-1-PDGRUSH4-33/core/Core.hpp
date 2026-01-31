/*
** EPITECH PROJECT, 2026
** core
** File description:
** core
*/

#include "../Module/AModule.hpp"
#include "../Display/IDisplay.hpp"

class MonitorCore {
    protected:
    std::vector<Krell::IModule*> _modules;
    std::vector<Krell::IDisplay*> _display;
    public:
        MonitorCore();
        ~MonitorCore();
        /*void init();ADisplay::
        void run();*/
};