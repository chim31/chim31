/*
** EPITECH PROJECT, 2026
** SfmlDisplay
** File description:
** Card renderer: Network (string-based)
**   getData() format: "eth0 RX:16354kB TX:1523kB"
**   or "N/A" if unavailable
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

float SfmlDisplay::drawCardNetwork(const std::string &data, float x, float y, float w)
{
    const CardTheme &theme = this->getTheme("Network");
    float h = 90.f;

    this->drawRect(x, y, w, h, BG_CARD, BG_CARD_BORDER, 1.f);
    this->drawRect(x + 1.f, y + 1.f, w - 2.f, 3.f, theme.accent);
    this->drawCardHeader(theme.icon, "Network", x, y + 10.f, w, theme.accent);

    float cy = y + 40.f;
    float pad = (float)CARD_PAD;

    if (data.empty() || data == "N/A") {
        this->drawText("No network data", x + pad, cy, 12, TEXT_DIM);
        return h;
    }

    std::string ifaceName;
    std::string rxVal;
    std::string txVal;

    std::size_t spacePos = data.find(' ');
    if (spacePos != std::string::npos) {
        ifaceName = data.substr(0, spacePos);
    } else {
        ifaceName = data;
    }

    std::size_t rxPos = data.find("RX:");
    if (rxPos != std::string::npos) {
        std::size_t rxEnd = data.find(' ', rxPos);
        if (rxEnd == std::string::npos)
            rxEnd = data.length();
        rxVal = data.substr(rxPos + 3, rxEnd - rxPos - 3);
    }

    std::size_t txPos = data.find("TX:");
    if (txPos != std::string::npos) {
        std::size_t txEnd = data.find(' ', txPos);
        if (txEnd == std::string::npos)
            txEnd = data.length();
        txVal = data.substr(txPos + 3, txEnd - txPos - 3);
    }

    sf::CircleShape dot(3.f);
    dot.setFillColor(theme.accent);
    dot.setPosition(x + pad, cy + 5.f);
    this->_window->draw(dot);
    this->drawText(ifaceName, x + pad + 12.f, cy, 13, TEXT_MAIN, true);
    cy += 22.f;

    float colW = (w - pad * 3.f) / 2.f;
    this->drawText("RX:", x + pad + 12.f, cy, 11, TEXT_DIM);
    this->drawText(rxVal.empty() ? "N/A" : rxVal, x + pad + 40.f, cy, 11, sf::Color(52, 211, 153));
    this->drawText("TX:", x + pad + 12.f + colW, cy, 11, TEXT_DIM);
    this->drawText(txVal.empty() ? "N/A" : txVal, x + pad + 40.f + colW, cy, 11, sf::Color(255, 140, 66));

    return h;
}
