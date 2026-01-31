/*
** EPITECH PROJECT, 2026
** module
** File description:
** module
*/

#ifndef IMODULE_HPP_
#define IMODULE_HPP_

#include <string>
#include <vector>

namespace Krell
{
    enum class ModuleType
    {
        Hostname,
        User,
        Os,
        Kernel,
        DateTime,
        Cpu,
        Ram,
        Network,
        Battery,
        Unknown
    };

    inline bool isValidModuleName(const std::string &name)
    {
        return name == "Hostname" || name == "User" || name == "Os"
            || name == "Kernel" || name == "DateTime" || name == "Cpu"
            || name == "Ram" || name == "Network" || name == "Battery";
    }

    inline ModuleType moduleTypeFromString(const std::string &name)
    {
        if (name == "Hostname") return ModuleType::Hostname;
        if (name == "User") return ModuleType::User;
        if (name == "Os") return ModuleType::Os;
        if (name == "Kernel") return ModuleType::Kernel;
        if (name == "DateTime") return ModuleType::DateTime;
        if (name == "Cpu") return ModuleType::Cpu;
        if (name == "Ram") return ModuleType::Ram;
        if (name == "Network") return ModuleType::Network;
        if (name == "Battery") return ModuleType::Battery;
        return ModuleType::Unknown;
    }

    class IModule
    {
        public:
            virtual ~IModule() = default;
            virtual void refresh() = 0;
            virtual const std::string &getName() const = 0;
            virtual const std::string &getData() const = 0;
    };
}

#endif /* !IMODULE_HPP_ */
