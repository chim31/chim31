/*
** EPITECH PROJECT, 2026
** SfmlDisplay
** File description:
** Card renderers: DateTime, System, Generic (string-based)
*/

#include "SfmlDisplay.hpp"
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>

static const sf::Color BG_CARD(35, 36, 64);
static const sf::Color BG_CARD_BORDER(45, 47, 84);
static const sf::Color TEXT_MAIN(224, 224, 236);
static const sf::Color TEXT_DIM(136, 136, 168);
static const sf::Color TEXT_LABEL(160, 162, 200);


float SfmlDisplay::drawCardDateTime(const std::string &data, float x, float y, float w)
{
    float h = 100.f;
    const CardTheme &theme = this->getTheme("Date & Time");

    this->drawRect(x, y, w, h, BG_CARD, BG_CARD_BORDER, 1.f);
    this->drawRect(x + 1.f, y + 1.f, w - 2.f, 3.f, theme.accent);
    this->drawCardHeader(theme.icon, "Date & Time", x, y + 10.f, w,
                         theme.accent);

    std::string dateStr = "--/--/----";
    std::string timeStr = "--:--:--";

    std::size_t spacePos = data.find(' ');
    if (spacePos != std::string::npos) {
        dateStr = data.substr(0, spacePos);
        timeStr = data.substr(spacePos + 1);
    } else if (!data.empty()) {
        dateStr = data;
    }

    this->drawText(timeStr, x + w / 2.f - 60.f, y + 40.f, 30, TEXT_MAIN, true);
    this->drawText(dateStr, x + w / 2.f - 40.f, y + 75.f, 14, TEXT_DIM);
    return h;
}


float SfmlDisplay::drawCardSystem(const std::string &name, const std::string &data, float x, float y, float w)
{
    float h = 66.f;
    const CardTheme &theme = this->getTheme(name);

    this->drawRect(x, y, w, h, BG_CARD, BG_CARD_BORDER, 1.f);
    this->drawRect(x + 1.f, y + 1.f, w - 2.f, 3.f, theme.accent);
    this->drawCardHeader(theme.icon, name, x, y + 10.f, w, theme.accent);

    std::string display = data.empty() ? "N/A" : data;
    this->drawText(display, x + (float)CARD_PAD, y + 40.f, 13, TEXT_MAIN);
    return h;
}

float SfmlDisplay::drawCardGeneric(const std::string &name, const std::string &data, float x, float y, float w)
{
    int lineCount = 1;
    for (char c : data) {
        if (c == '\n')
            lineCount++;
    }
    float lineH = 18.f;
    float h = 44.f + (float)lineCount * lineH;
    const CardTheme &theme = this->getTheme(name);

    this->drawRect(x, y, w, h, BG_CARD, BG_CARD_BORDER, 1.f);
    this->drawRect(x + 1.f, y + 1.f, w - 2.f, 3.f, theme.accent);
    this->drawCardHeader(theme.icon, name, x, y + 10.f, w, theme.accent);

    float cy = y + 40.f;
    std::istringstream stream(data);
    std::string line;
    while (std::getline(stream, line)) {
        this->drawText(line, x + (float)CARD_PAD, cy, 11, TEXT_MAIN);
        cy += lineH;
    }
    return h;
}
