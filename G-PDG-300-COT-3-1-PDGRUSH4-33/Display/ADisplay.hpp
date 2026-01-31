/*
** EPITECH PROJECT, 2026
** adisplay
** File description:
** adisplay
*/

#ifndef ADISPLAY_HPP_
#define ADISPLAY_HPP_

#include "../Interfaces/IDisplay.hpp"

class ADisplay : public Krell::IDisplay
{
    protected:
        std::string _name;
        bool _isrun;
    public:
        ADisplay(const std::string &name);
        virtual ~ADisplay() = default;
        bool isRun() const override;
        const std::string &getName() const override;
};

#endif /* !ADISPLAY_HPP_ */
