/*
** EPITECH PROJECT, 2026
** SfmlDisplay
** File description:
** SFML display - Background, Sidebar, Header, Card dispatcher
*/

#include "SfmlDisplay.hpp"
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>

static const sf::Color BG_MAIN(26, 27, 46);
static const sf::Color BG_CARD(35, 36, 64);
static const sf::Color BG_CARD_BORDER(45, 47, 84);
static const sf::Color BG_SIDEBAR(22, 23, 42);
static const sf::Color BG_HEADER(30, 31, 54);
static const sf::Color BG_BAR(40, 42, 70);
static const sf::Color TEXT_MAIN(224, 224, 236);
static const sf::Color TEXT_DIM(136, 136, 168);
static const sf::Color TEXT_LABEL(160, 162, 200);
static const sf::Color ACCENT_CYAN(0, 212, 170);
static const sf::Color ACCENT_BLUE(77, 142, 255);

void SfmlDisplay::drawBackground()
{
    sf::RectangleShape stripe;
    stripe.setSize(sf::Vector2f((float)WIN_W, 3.f));
    stripe.setPosition(0.f, (float)HEADER_H - 1.f);
    stripe.setFillColor(sf::Color(0, 212, 170, 60));
    this->_window->draw(stripe);
}

void SfmlDisplay::drawSidebar(const std::vector<Krell::IModule *> &modules)
{
    this->drawRect(0, 0, (float)SIDEBAR_W, (float)WIN_H, BG_SIDEBAR);

    this->drawText("MyGKrellm", 16.f, 14.f, 18, ACCENT_CYAN, true);
    this->drawText("System Monitor", 16.f, 36.f, 11, TEXT_DIM);

    this->drawSeparator(16.f, 58.f, (float)SIDEBAR_W - 32.f, sf::Color(45, 47, 84));

    float y = 72.f;
    for (std::size_t i = 0; i < modules.size(); i++) {
        const std::string &name = modules[i]->getName();
        const CardTheme &theme = this->getTheme(name);

        sf::CircleShape dot(3.f);
        dot.setFillColor(theme.accent);
        dot.setPosition(20.f, y + 6.f);
        this->_window->draw(dot);

        this->drawText(name, 34.f, y, 12, TEXT_MAIN);
        y += 24.f;
    }

    this->drawSeparator(16.f, (float)WIN_H - 50.f, (float)SIDEBAR_W - 32.f, sf::Color(45, 47, 84));
    this->drawText("Scroll to navigate", 16.f, (float)WIN_H - 38.f, 10, TEXT_DIM);
    this->drawText("A:Add  R:Remove", 16.f, (float)WIN_H - 22.f, 10, TEXT_DIM);
}

void SfmlDisplay::drawHeader()
{
    this->drawRect(0, 0, (float)WIN_W, (float)HEADER_H, BG_HEADER);
    this->drawText("Dashboard", (float)SIDEBAR_W + 18.f, 16.f, 18, TEXT_MAIN, true);
    this->drawRect((float)SIDEBAR_W, (float)HEADER_H - 2.f, (float)WIN_W - (float)SIDEBAR_W, 2.f, sf::Color(0, 212, 170, 40));
}

float SfmlDisplay::drawCard(Krell::IModule *mod, float x, float y, float w)
{
    const std::string &name = mod->getName();
    const std::string &data = mod->getData();

    if (y > (float)WIN_H + 100.f || y < (float)HEADER_H - 400.f)
        return 80.f;

    if (name == "Date & Time")
        return this->drawCardDateTime(data, x, y, w);
    if (name == "CPU")
        return this->drawCardCpu(data, x, y, w);
    if (name == "RAM")
        return this->drawCardRam(data, x, y, w);
    if (name == "Network")
        return this->drawCardNetwork(data, x, y, w);
    if (name == "Battery")
        return this->drawCardBattery(data, x, y, w);
    if (name == "Hostname" || name == "User"
        || name == "Operating System" || name == "Kernel")
        return this->drawCardSystem(name, data, x, y, w);
    return this->drawCardGeneric(name, data, x, y, w);
}
