/*
** EPITECH PROJECT, 2026
** SfmlDisplay
** File description:
** Primitive drawing helpers
*/

#include "SfmlDisplay.hpp"
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>

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
    this->drawText(title, x + (float)CARD_PAD + 20.f, y, 14, sf::Color(224, 224, 236), true);
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
