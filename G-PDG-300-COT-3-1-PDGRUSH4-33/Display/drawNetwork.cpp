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

float SfmlDisplay::drawCardNetwork(const std::map<std::string, std::string> &d, float x, float y, float w)
{
    const CardTheme &theme = this->getTheme("Network");

    auto itCount = d.find("InterfaceCount");
    int count = 0;
    if (itCount != d.end()) {
        std::stringstream ss(itCount->second);
        ss >> count;
    }

    float h = 44.f + (float)count * 84.f + 10.f;

    this->drawRect(x, y, w, h, BG_CARD, BG_CARD_BORDER, 1.f);
    this->drawRect(x + 1.f, y + 1.f, w - 2.f, 3.f, theme.accent);
    this->drawCardHeader(theme.icon, "Network", x, y + 10.f, w, theme.accent);

    float cy = y + 40.f;
    float pad = (float)CARD_PAD;

    for (int i = 0; i < count; i++) {
        std::string prefix = "iface" + std::to_string(i);
        auto itName = d.find(prefix + "_name");
        std::string ifName = (itName != d.end()) ? itName->second : "?";

        sf::CircleShape dot(3.f);
        dot.setFillColor(theme.accent);
        dot.setPosition(x + pad, cy + 5.f);
        this->_window->draw(dot);
        this->drawText(ifName, x + pad + 12.f, cy, 13, TEXT_MAIN, true);
        cy += 20.f;

        auto getVal = [&](const std::string &suffix) -> std::string {
            auto it = d.find(prefix + suffix);
            return (it != d.end()) ? it->second : "0";
        };

        float colW = (w - pad * 3.f) / 2.f;
        this->drawText("RX:", x + pad + 12.f, cy, 10, TEXT_DIM);
        this->drawText(getVal("_rx_bytes") + " B", x + pad + 40.f, cy, 10, sf::Color(52, 211, 153));
        this->drawText("TX:", x + pad + 12.f + colW, cy, 10, TEXT_DIM);
        this->drawText(getVal("_tx_bytes") + " B", x + pad + 40.f + colW, cy, 10, sf::Color(255, 140, 66));
        cy += 16.f;

        this->drawText("Packets:", x + pad + 12.f, cy, 10, TEXT_DIM);
        this->drawText(getVal("_rx_packets"), x + pad + 70.f, cy, 10, TEXT_LABEL);
        this->drawText("Packets:", x + pad + 12.f + colW, cy, 10, TEXT_DIM);
        this->drawText(getVal("_tx_packets"), x + pad + 70.f + colW, cy, 10, TEXT_LABEL);
        cy += 16.f;

        this->drawText("Errors:", x + pad + 12.f, cy, 10, TEXT_DIM);
        this->drawText(getVal("_rx_errors"), x + pad + 60.f, cy, 10, getVal("_rx_errors") != "0" ? sf::Color(239, 68, 68) : TEXT_DIM);
        cy += 18.f;

        if (i < count - 1)
            this->drawSeparator(x + pad, cy, w - pad * 2.f, BG_CARD_BORDER);
        cy += 8.f;
    }
    return cy - y + 4.f;
}
