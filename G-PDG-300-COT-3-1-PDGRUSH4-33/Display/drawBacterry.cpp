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


float SfmlDisplay::drawCardBattery(const std::map<std::string, std::string> &d, float x, float y, float w)
{
    float h = 120.f;
    const CardTheme &theme = this->getTheme("Battery");

    this->drawRect(x, y, w, h, BG_CARD, BG_CARD_BORDER, 1.f);
    this->drawRect(x + 1.f, y + 1.f, w - 2.f, 3.f, theme.accent);
    this->drawCardHeader(theme.icon, "Battery", x, y + 10.f, w, theme.accent);

    float cy = y + 40.f;
    float pad = (float)CARD_PAD;

    auto itCap = d.find("Capacity");
    float capacity = 0.f;
    if (itCap != d.end()) {
        std::stringstream ss(itCap->second);
        ss >> capacity;
    }

    auto itStatus = d.find("Status");
    std::string status = (itStatus != d.end()) ? itStatus->second : "N/A";

    this->drawText("Status: " + status, x + pad, cy, 12, TEXT_MAIN);
    this->drawText(std::to_string((int)capacity) + "%", x + w - pad - 35.f, cy, 14, theme.accent, true);
    cy += 24.f;

    sf::Color barColor = theme.barFill;
    if (capacity < 20.f)
        barColor = sf::Color(239, 68, 68);
    else if (capacity < 50.f)
        barColor = sf::Color(251, 191, 36);
    else
        barColor = sf::Color(52, 211, 153);

    this->drawProgressBar(x + pad, cy, w - pad * 2.f, 18.f, capacity, barColor, BG_BAR);
    cy += 30.f;

    auto drawDetail = [&](const std::string &label, const std::string &key) {
        auto it = d.find(key);
        if (it != d.end() && it->second != "N/A") {
            this->drawText(label, x + pad, cy, 10, TEXT_DIM);
            this->drawText(it->second, x + 110.f, cy, 10, TEXT_LABEL);
            cy += 16.f;
        }
    };
    drawDetail("Energy Now:", "EnergyNow");
    drawDetail("Energy Full:", "EnergyFull");
    drawDetail("Power Draw:", "PowerDraw");

    return cy - y + 8.f;
}
