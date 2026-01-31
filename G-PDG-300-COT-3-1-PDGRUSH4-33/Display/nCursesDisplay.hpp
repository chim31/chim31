/*
** EPITECH PROJECT, 2026
** ncruses
** File description:
** ncurse
*/

#include "ADisplay.hpp"

class nCursesDisplay: public ADisplay {
    public:
    void update_display(const std::vector<Krell::IModule*>&modules) override;
};