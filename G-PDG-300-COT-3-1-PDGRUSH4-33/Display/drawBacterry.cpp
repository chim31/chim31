/*
** EPITECH PROJECT, 2026
** SfmlDisplay
** File description:
** Card renderer: Battery (string-based)
**   getData() format: "85% Discharging" or "N/A"
*/

#include "SfmlDisplay.hpp"
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>

static const sf::Color BG_CARD(35, 36, 64);
static const sf::Color BG_CARD_BORDER(45, 47, 84);
static const sf::Color BG_BAR(40, 42, 70);
static const sf::Color TEXT_MAIN(224, 224, 236);
static const sf::Color TEXT_DIM(136, 136, 168);
static const sf::Color TEXT_LABEL(160, 162, 200);

float SfmlDisplay::drawCardBattery(const std::string &data, float x, float y, float w)
{
    float h = 100.f;
    const CardTheme &theme = this->getTheme("Battery");

    this->drawRect(x, y, w, h, BG_CARD, BG_CARD_BORDER, 1.f);
    this->drawRect(x + 1.f, y + 1.f, w - 2.f, 3.f, theme.accent);
    this->drawCardHeader(theme.icon, "Battery", x, y + 10.f, w, theme.accent);

    float cy = y + 40.f;
    float pad = (float)CARD_PAD;

    if (data.empty() || data == "N/A") {
        this->drawText("No battery detected", x + pad, cy, 12, TEXT_DIM);
        return h;
    }

    float capacity = 0.f;
    std::string status = "Unknown";

    std::size_t percentPos = data.find('%');
    if (percentPos != std::string::npos) {
        std::string numStr = data.substr(0, percentPos);
        std::stringstream ss(numStr);
        ss >> capacity;
        if (percentPos + 2 <= data.length())
            status = data.substr(percentPos + 2);
    } else {
        status = data;
    }
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
    return h;
}
