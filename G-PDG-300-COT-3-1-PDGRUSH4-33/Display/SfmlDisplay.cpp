/*
** EPITECH PROJECT, 2026
** SfmlDisplay
** File description:
** SFML display - Modern dark dashboard with card-based layout
**
** Color palette:
**   Background:  #1a1b2e (deep navy)
**   Card bg:     #232440 (dark slate)
**   Card border: #2d2f54 (subtle border)
**   Sidebar:     #16172a (darker navy)
**   Header:      #1e1f36
**   Text main:   #e0e0ec
**   Text dim:    #8888a8
**   Accent cyan: #00d4aa
**   Accent blue: #4d8eff
**   CPU orange:  #ff8c42
**   RAM purple:  #a855f7
**   Net green:   #34d399
**   Battery yel: #fbbf24
**   Date pink:   #f472b6
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

float SfmlDisplay::drawCardDateTime(const std::map<std::string, std::string> &d, float x, float y, float w)
{
    float h = 100.f;
    const CardTheme &theme = this->getTheme("Date & Time");

    this->drawRect(x, y, w, h, BG_CARD, BG_CARD_BORDER, 1.f);
    this->drawRect(x + 1.f, y + 1.f, w - 2.f, 3.f, theme.accent);
    this->drawCardHeader(theme.icon, "Date & Time", x, y + 10.f, w, theme.accent);

    auto itTime = d.find("Time");
    auto itDate = d.find("Date");
    
    std::string timeStr = (itTime != d.end()) ? itTime->second : "--:--:--";
    std::string dateStr = (itDate != d.end()) ? itDate->second : "--/--/----";
    
    this->drawText(timeStr, x + w / 2.f - 60.f, y + 40.f, 30, TEXT_MAIN, true);
    this->drawText(dateStr, x + w / 2.f - 40.f, y + 75.f, 14, TEXT_DIM);
    return h;
}

float SfmlDisplay::drawCardSystem(const std::string &name, const std::map<std::string, std::string> &d, float x, float y, float w)
{
    float lineH = 22.f;
    float h = 44.f + (float)d.size() * lineH;
    const CardTheme &theme = this->getTheme(name);

    this->drawRect(x, y, w, h, BG_CARD, BG_CARD_BORDER, 1.f);
    this->drawRect(x + 1.f, y + 1.f, w - 2.f, 3.f, theme.accent);
    this->drawCardHeader(theme.icon, name, x, y + 10.f, w, theme.accent);

    float cy = y + 40.f;
    for (auto &pair : d) {
        this->drawText(pair.first + ":", x + (float)CARD_PAD, cy, 12, TEXT_LABEL);
        this->drawText(pair.second, x + 140.f, cy, 12, TEXT_MAIN);
        cy += lineH;
    }
    return h;
}

float SfmlDisplay::drawCardGeneric(const std::string &name, const std::map<std::string, std::string> &d, float x, float y, float w)
{
    float lineH = 20.f;
    float h = 44.f + (float)d.size() * lineH;
    const CardTheme &theme = this->getTheme(name);

    this->drawRect(x, y, w, h, BG_CARD, BG_CARD_BORDER, 1.f);
    this->drawRect(x + 1.f, y + 1.f, w - 2.f, 3.f, theme.accent);
    this->drawCardHeader(theme.icon, name, x, y + 10.f, w, theme.accent);

    float cy = y + 40.f;
    for (auto &pair : d) {
        this->drawText(pair.first + ": " + pair.second, x + (float)CARD_PAD, cy, 11, TEXT_MAIN);
        cy += lineH;
    }
    return h;
}
