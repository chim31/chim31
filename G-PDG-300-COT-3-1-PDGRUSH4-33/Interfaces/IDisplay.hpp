/*
** EPITECH PROJECT, 2026
** idisplay
** File description:
** idisplay
*/

#ifndef IDISPLAY_HPP_
#define IDISPLAY_HPP_

#include <string>
#include <vector>
#include "../Interfaces/IModule.hpp"

namespace Krell
{
    class IDisplay
    {
        public:
            virtual ~IDisplay() = default;
            virtual bool isRun() const = 0;
            virtual const std::string &getName() const = 0;
            virtual void init(const std::vector<Krell::IModule *> &modules) = 0;
            virtual void update_display(std::vector<Krell::IModule *> &modules) = 0;
            virtual void stop() = 0;
    };
}

#endif /* !IDISPLAY_HPP_ */