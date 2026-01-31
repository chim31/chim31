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


float SfmlDisplay::drawCardCpu(const std::map<std::string, std::string> &d, float x, float y, float w)
{
    const CardTheme &theme = this->getTheme("CPU");

    int coreCount = 0;
    for (auto &pair : d) {
        if (pair.first.find("Core") == 0)
            coreCount++;
    }
    float infoLines = 4.f;
    float barH = 16.f;
    float barGap = 6.f;
    float h = 44.f + infoLines * 22.f + 10.f + (float)coreCount * (barH + barGap) + 30.f;

    this->drawRect(x, y, w, h, BG_CARD, BG_CARD_BORDER, 1.f);
    this->drawRect(x + 1.f, y + 1.f, w - 2.f, 3.f, theme.accent);
    this->drawCardHeader(theme.icon, "CPU", x, y + 10.f, w, theme.accent);

    float cy = y + 40.f;
    float pad = (float)CARD_PAD;

    auto drawInfoLine = [&](const std::string &label, const std::string &key) {
        auto it = d.find(key);
        std::string val = (it != d.end()) ? it->second : "N/A";
        this->drawText(label + ":", x + pad, cy, 11, TEXT_LABEL);
        this->drawText(val, x + 130.f, cy, 11, TEXT_MAIN);
        cy += 22.f;
    };
    drawInfoLine("Model", "Model");
    drawInfoLine("Frequency", "Frequency");
    drawInfoLine("Physical", "PhysicalCores");
    drawInfoLine("Logical", "LogicalCores");

    cy += 6.f;
    auto itTotal = d.find("TotalUsage");
    float totalUsage = 0.f;
    if (itTotal != d.end()) {
        std::stringstream ss(itTotal->second);
        ss >> totalUsage;
    }
    this->drawText("Total:", x + pad, cy, 12, TEXT_MAIN, true);
    this->drawText(std::to_string((int)totalUsage) + "%", x + w - pad - 30.f, cy, 12, theme.accent, true);
    cy += 18.f;
    this->drawProgressBar(x + pad, cy, w - pad * 2.f, barH, totalUsage, theme.barFill, BG_BAR);
    cy += barH + barGap + 4.f;

    this->drawSeparator(x + pad, cy, w - pad * 2.f, BG_CARD_BORDER);
    cy += 8.f;

    for (int i = 0; i < coreCount; i++) {
        std::string key = "Core" + std::to_string(i);
        auto it = d.find(key);
        float usage = 0.f;
        if (it != d.end()) {
            std::stringstream ss(it->second);
            ss >> usage;
        }
        std::string label = "Core " + std::to_string(i);
        this->drawText(label, x + pad, cy, 10, TEXT_DIM);
        this->drawText(std::to_string((int)usage) + "%", x + w - pad - 28.f, cy, 10, TEXT_LABEL);
        cy += 14.f;
        int r = std::min(255, (int)theme.barFill.r + i * 8);
        int g = std::max(0, (int)theme.barFill.g - i * 4);
        sf::Color coreFill((sf::Uint8)r, (sf::Uint8)g, theme.barFill.b);
        this->drawProgressBar(x + pad, cy, w - pad * 2.f, barH - 4.f, usage, coreFill, BG_BAR);
        cy += barH - 4.f + barGap;
    }
    return cy - y + 8.f;
}
