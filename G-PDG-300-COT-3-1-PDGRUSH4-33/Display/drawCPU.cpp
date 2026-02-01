/*
** EPITECH PROJECT, 2026
** SfmlDisplay
** File description:
** Card renderer: CPU (string-based)
**   getData() format: "42%"
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

float SfmlDisplay::drawCardCpu(const std::string &data, float x, float y, float w)
{
    const CardTheme &theme = this->getTheme("CPU");
    float h = 100.f;

    this->drawRect(x, y, w, h, BG_CARD, BG_CARD_BORDER, 1.f);
    this->drawRect(x + 1.f, y + 1.f, w - 2.f, 3.f, theme.accent);
    this->drawCardHeader(theme.icon, "CPU", x, y + 10.f, w, theme.accent);

    float cy = y + 40.f;
    float pad = (float)CARD_PAD;

    float totalUsage = 0.f;
    std::string displayStr = data;

    if (!data.empty() && data != "N/A") {
        std::string numStr = data;
        if (!numStr.empty() && numStr.back() == '%')
            numStr.pop_back();
        std::stringstream ss(numStr);
        ss >> totalUsage;
        displayStr = data;
    }

    this->drawText("Usage:", x + pad, cy, 12, TEXT_MAIN, true);
    this->drawText(displayStr, x + w - pad - 40.f, cy, 14, theme.accent, true);
    cy += 22.f;
    this->drawProgressBar(x + pad, cy, w - pad * 2.f, 18.f, totalUsage, theme.barFill, BG_BAR);
    cy += 28.f;
    
    return h;
}
