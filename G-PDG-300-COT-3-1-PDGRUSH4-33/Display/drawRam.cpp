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

float SfmlDisplay::drawCardRam(const std::map<std::string, std::string> &d, float x, float y, float w)
{
    float h = 200.f;
    const CardTheme &theme = this->getTheme("RAM");

    this->drawRect(x, y, w, h, BG_CARD, BG_CARD_BORDER, 1.f);
    this->drawRect(x + 1.f, y + 1.f, w - 2.f, 3.f, theme.accent);
    this->drawCardHeader(theme.icon, "Memory", x, y + 10.f, w, theme.accent);

    float cy = y + 40.f;
    float pad = (float)CARD_PAD;

    auto itUsage = d.find("Usage");
    float ramPercent = 0.f;
    if (itUsage != d.end()) {
        std::stringstream ss(itUsage->second);
        ss >> ramPercent;
    }

    this->drawText("RAM Usage", x + pad, cy, 12, TEXT_MAIN, true);
    this->drawText(std::to_string((int)ramPercent) + "%", x + w - pad - 30.f, cy, 12, theme.accent, true);
    cy += 20.f;
    this->drawProgressBar(x + pad, cy, w - pad * 2.f, 18.f, ramPercent, theme.barFill, BG_BAR);
    cy += 26.f;

    auto drawDetail = [&](const std::string &label, const std::string &key) {
        auto it = d.find(key);
        std::string val = (it != d.end()) ? it->second : "N/A";
        this->drawText(label, x + pad, cy, 11, TEXT_DIM);
        this->drawText(val, x + 140.f, cy, 11, TEXT_MAIN);
        cy += 18.f;
    };
    drawDetail("Total:", "Total");
    drawDetail("Used:", "Used");
    drawDetail("Available:", "Available");

    cy += 6.f;
    this->drawSeparator(x + pad, cy, w - pad * 2.f, BG_CARD_BORDER);
    cy += 10.f;

    auto itSwap = d.find("SwapUsage");
    float swapPercent = 0.f;
    if (itSwap != d.end()) {
        std::stringstream ss(itSwap->second);
        ss >> swapPercent;
    }
    this->drawText("Swap", x + pad, cy, 12, TEXT_MAIN, true);
    this->drawText(std::to_string((int)swapPercent) + "%", x + w - pad - 30.f, cy, 12, TEXT_LABEL);
    cy += 20.f;

    sf::Color swapColor(130, 70, 220);
    this->drawProgressBar(x + pad, cy, w - pad * 2.f, 12.f, swapPercent, swapColor, BG_BAR);
    cy += 18.f;

    drawDetail("Swap Total:", "SwapTotal");

    h = cy - y + 10.f;

    return h;
}
