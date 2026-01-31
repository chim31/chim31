/*
** EPITECH PROJECT, 2026
** sfml
** File description:
** sfml
*/

#include "ADisplay.hpp"

class SfmlDisplay: public ADisplay {
    public:
    void update_display(const std::vector<Krell::IModule*>&modules) override;
};