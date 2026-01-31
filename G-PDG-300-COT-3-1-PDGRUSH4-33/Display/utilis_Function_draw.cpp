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

void SfmlDisplay::drawRect(float x, float y, float w, float h, sf::Color fill, sf::Color outline, float outlineThick)
{
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(w, h));
    rect.setPosition(x, y);
    rect.setFillColor(fill);
    if (outlineThick > 0.f) {
        rect.setOutlineColor(outline);
        rect.setOutlineThickness(outlineThick);
    }
    this->_window->draw(rect);
}

void SfmlDisplay::drawProgressBar(float x, float y, float w, float h, float percent, sf::Color fill, sf::Color bg)
{
    if (percent < 0.f) percent = 0.f;
    if (percent > 100.f) percent = 100.f;

    this->drawRect(x, y, w, h, bg);

    float fillW = (w * percent) / 100.f;
    if (fillW > 0.5f)
        this->drawRect(x, y, fillW, h, fill);

    if (fillW > 2.f) {
        sf::Color highlight(
            std::min(255, (int)fill.r + 40),
            std::min(255, (int)fill.g + 40),
            std::min(255, (int)fill.b + 40),
            100
        );
        this->drawRect(x, y, fillW, h * 0.35f, highlight);
    }
}

void SfmlDisplay::drawText(const std::string &str, float x, float y, unsigned int size, sf::Color color, bool bold)
{
    sf::Text text;
    text.setFont(bold ? this->_fontBold : this->_fontRegular);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(x, y);
    this->_window->draw(text);
}

void SfmlDisplay::drawCardHeader(const std::string &icon, const std::string &title, float x, float y, float w, sf::Color accent)
{
    (void)w;
    this->drawText(icon, x + (float)CARD_PAD, y, 14, accent, true);
    this->drawText(title, x + (float)CARD_PAD + 20.f, y, 14, TEXT_MAIN, true);
}

void SfmlDisplay::drawSeparator(float x, float y, float w, sf::Color color)
{
    this->drawRect(x, y, w, 1.f, color);
}

float SfmlDisplay::getTextWidth(const std::string &str, unsigned int size, bool bold)
{
    sf::Text text;
    text.setFont(bold ? this->_fontBold : this->_fontRegular);
    text.setString(str);
    text.setCharacterSize(size);
    return text.getLocalBounds().width;
}
