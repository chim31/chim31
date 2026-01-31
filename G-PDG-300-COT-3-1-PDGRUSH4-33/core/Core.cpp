/*
** EPITECH PROJECT, 2026
** core
** File description:
** core
*/

#include "Core.hpp"
#include "../Module/HostnameModule.hpp"
#include "../Module/UserModule.hpp"
#include "../Module/OsModule.hpp"
#include "../Module/KernelModule.hpp"
#include "../Module/DateTimeModule.hpp"
#include "../Module/CpuModule.hpp"
#include "../Module/RamModule.hpp"
#include "../Module/NetworkModule.hpp"
#include "../Module/BatteryModule.hpp"
#include "../Display/SfmlDisplay.hpp"
#include <iostream>
#include <string>
#include <cstring>

MonitorCore::MonitorCore() : _displayHidden(false)
{
}

MonitorCore::~MonitorCore()
{
    for (auto x : this->_modules)
        delete x;
    for (auto x : this->_display)
        delete x;
}

void MonitorCore::addModule(Krell::IModule *module)
{
    if (module)
        _modules.push_back(module);
}

void MonitorCore::removeModule(Krell::IModule *module)
{
    if (!module)
        return;
    for (auto it = _modules.begin(); it != _modules.end(); ++it) {
        if (*it == module) {
            _modules.erase(it);
            delete module;
            return;
        }
    }
}

void MonitorCore::addDisplay(Krell::IDisplay *display)
{
    if (display)
        _display.push_back(display);
}

void MonitorCore::hideDisplay()
{
    _displayHidden = true;
}

void MonitorCore::showDisplay()
{
    _displayHidden = false;
}

bool MonitorCore::isDisplayHidden() const
{
    return _displayHidden;
}

std::vector<Krell::IModule*> &MonitorCore::getModules()
{
    return _modules;
}

const std::vector<Krell::IModule*> &MonitorCore::getModules() const
{
    return _modules;
}

static void usage()
{
    std::cout << "Usage: GKrellM" << std::endl;
    std::cout << "--graphical or -g for graphical interface" << std::endl;
    std::cout << "--text or -t for ncurses interface" << std::endl;
    std::cout << "-l option to specify modules to load" << std::endl;
}

static bool isDisplayFlag(const char *arg)
{
    return strcmp(arg, "--text") == 0 || strcmp(arg, "-t") == 0
        || strcmp(arg, "--graphical") == 0 || strcmp(arg, "-g") == 0;
}

static bool isOptionFlag(const char *arg)
{
    return strcmp(arg, "-l") == 0 || isDisplayFlag(arg)
        || strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0;
}

static void addDefaultModules(MonitorCore &core)
{
    core.addModule(new HostModule("Hostname"));
    core.addModule(new UserModule("User"));
    core.addModule(new OsModule("Operating System"));
    core.addModule(new KernelModule("Kernel"));
    core.addModule(new DateTimeModule("Date & Time"));
    core.addModule(new CpuModule(1));
    core.addModule(new RamModule("RAM"));
    core.addModule(new NetworkModule("Network"));
    core.addModule(new BatteryModule("Battery"));
}

static void parseArgs(int ac, char **av, int &display_count, std::vector<std::string> &moduleNames)
{
    for (int i = 1; i < ac; i++) {
        if (strcmp(av[i], "-h") == 0 || strcmp(av[i], "--help") == 0) {
            usage();
            exit(0);
        }
        if (isDisplayFlag(av[i])) {
            display_count++;
        }
        if (strcmp(av[i], "-l") == 0) {
            if (i == ac - 1) {
                std::cerr << "Error: -l requires at least one module name" << std::endl;
                exit(84);
            }
            i++;
            while (i < ac && !isOptionFlag(av[i])) {
                moduleNames.push_back(av[i]);
                i++;
            }
            i--;
        }
    }
}

static void validateArgs(int display_count, const std::vector<std::string> &moduleNames)
{
    if (display_count > 1) {
        std::cerr << "Error: only one display mode (--text/-t or --graphical/-g)" << std::endl;
        exit(84);
    }
    for (const auto &name : moduleNames) {
        if (!Krell::isValidModuleName(name)) {
            std::cerr << "Error: invalid module name \"" << name << "\"" << std::endl;
            exit(84);
        }
    }
}

static void createModules(MonitorCore &core, const std::vector<std::string> &moduleNames)
{
    if (moduleNames.empty()) {
        addDefaultModules(core);
        return;
    }
    for (const auto &name : moduleNames) {
        switch (Krell::moduleTypeFromString(name)) {
            case Krell::ModuleType::Hostname: core.addModule(new HostModule("Hostname")); break;
            case Krell::ModuleType::User: core.addModule(new UserModule("User")); break;
            case Krell::ModuleType::Os: core.addModule(new OsModule("Operating System")); break;
            case Krell::ModuleType::Kernel: core.addModule(new KernelModule("Kernel")); break;
            case Krell::ModuleType::DateTime: core.addModule(new DateTimeModule("Date & Time")); break;
            case Krell::ModuleType::Cpu: core.addModule(new CpuModule(1)); break;
            case Krell::ModuleType::Ram: core.addModule(new RamModule("RAM")); break;
            case Krell::ModuleType::Network: core.addModule(new NetworkModule("Network")); break;
            case Krell::ModuleType::Battery: core.addModule(new BatteryModule("Battery")); break;
            default: break;
        }
    }
}

static void runDisplay(int ac, char **av, MonitorCore &core, int display_count)
{
    if (display_count > 0) {
        bool graphical = false;
        for (int i = 1; i < ac; i++) {
            if (strcmp(av[i], "--graphical") == 0 || strcmp(av[i], "-g") == 0) graphical = true;
        }

        if (graphical) {
            SfmlDisplay *disp = new SfmlDisplay("GKrellM");
            core.addDisplay(disp);
            disp->init(core.getModules());
            
            while (disp->isRun()) {
                for (auto mod : core.getModules())
                    mod->refresh();
                disp->update_display(core.getModules());
            }
        }
    }
}

int main(int ac, char **av)
{
    int display_count = 0;
    std::vector<std::string> moduleNamesFromArgs;

    parseArgs(ac, av, display_count, moduleNamesFromArgs);
    validateArgs(display_count, moduleNamesFromArgs);

    MonitorCore core;
    createModules(core, moduleNamesFromArgs);
    runDisplay(ac, av, core, display_count);

    return 0;
}