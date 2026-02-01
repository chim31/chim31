/*
** EPITECH PROJECT, 2026
** SfmlDisplay
** File description:
** Card renderer: RAM (string-based)
**   getData() format:
**     "Total: 7949 MB\nUsed: 4200 MB\nFree: 2100 MB\n
**      Available: 3749 MB\nUsage: 52\nSwapTotal: 2048 MB\n
**      SwapUsed: 100 MB\nSwapUsage: 4"
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

float SfmlDisplay::drawCardRam(const std::string &data, float x, float y, float w)
{
    const CardTheme &theme = this->getTheme("RAM");

    this->drawRect(x, y, w, 220.f, BG_CARD, BG_CARD_BORDER, 1.f);
    this->drawRect(x + 1.f, y + 1.f, w - 2.f, 3.f, theme.accent);
    this->drawCardHeader(theme.icon, "Memory", x, y + 10.f, w, theme.accent);

    float cy = y + 40.f;
    float pad = (float)CARD_PAD;

    std::string totalStr = this->extractValue(data, "Total:");
    std::string usedStr = this->extractValue(data, "Used:");
    std::string availStr = this->extractValue(data, "Available:");
    std::string usageStr = this->extractValue(data, "Usage:");
    std::string swapTotalStr = this->extractValue(data, "SwapTotal:");
    std::string swapUsageStr = this->extractValue(data, "SwapUsage:");

    float ramPercent = 0.f;
    if (!usageStr.empty()) {
        std::stringstream ss(usageStr);
        ss >> ramPercent;
    }

    this->drawText("RAM Usage", x + pad, cy, 12, TEXT_MAIN, true);
    this->drawText(std::to_string((int)ramPercent) + "%", x + w - pad - 30.f, cy, 12, theme.accent, true);
    cy += 20.f;
    this->drawProgressBar(x + pad, cy, w - pad * 2.f, 18.f, ramPercent, theme.barFill, BG_BAR);
    cy += 26.f;

    auto drawDetail = [&](const std::string &label, const std::string &val) {
        this->drawText(label, x + pad, cy, 11, TEXT_DIM);
        this->drawText(val.empty() ? "N/A" : val, x + 140.f, cy, 11, TEXT_MAIN);
        cy += 18.f;
    };
    drawDetail("Total:", totalStr);
    drawDetail("Used:", usedStr);
    drawDetail("Available:", availStr);

    cy += 6.f;
    this->drawSeparator(x + pad, cy, w - pad * 2.f, BG_CARD_BORDER);
    cy += 10.f;


    float swapPercent = 0.f;
    if (!swapUsageStr.empty()) {
        std::stringstream ss(swapUsageStr);
        ss >> swapPercent;
    }
    this->drawText("Swap", x + pad, cy, 12, TEXT_MAIN, true);
    this->drawText(std::to_string((int)swapPercent) + "%", x + w - pad - 30.f, cy, 12, TEXT_LABEL);
    cy += 20.f;
    sf::Color swapColor(130, 70, 220);
    this->drawProgressBar(x + pad, cy, w - pad * 2.f, 12.f, swapPercent, swapColor, BG_BAR);
    cy += 18.f;
    drawDetail("Swap Total:", swapTotalStr);

    float h = cy - y + 10.f;
    return h;
}
