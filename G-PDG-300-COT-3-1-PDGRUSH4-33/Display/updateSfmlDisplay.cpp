/*
** EPITECH PROJECT, 2026
** SfmlDisplay
** File description:
** Main update loop, event handling, scrolling
*/

#include "SfmlDisplay.hpp"
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>

static const sf::Color BG_MAIN(26, 27, 46);
static const sf::Color BG_CARD_BORDER(45, 47, 84);
static const sf::Color BG_SIDEBAR(22, 23, 42);
static const sf::Color BG_HEADER(30, 31, 54);
static const sf::Color TEXT_MAIN(224, 224, 236);

void SfmlDisplay::update_display(std::vector<Krell::IModule *> &modules)
{
    if (!this->_window || !this->_window->isOpen()) {
        this->_isrun = false;
        return;
    }
    sf::Event event;
    while (this->_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->_window->close();
            this->_isrun = false;
            return;
        }
        if (event.type == sf::Event::MouseWheelScrolled) {
            this->_scrollOffset -= event.mouseWheelScroll.delta * 25.f;
            if (this->_scrollOffset < 0.f)
                this->_scrollOffset = 0.f;
            if (this->_scrollOffset > this->_maxScroll)
                this->_scrollOffset = this->_maxScroll;
        }
    }
    this->_window->clear(BG_MAIN);
    this->drawBackground();
    this->drawSidebar(modules);
    this->drawHeader();

    float contentX = (float)SIDEBAR_W + (float)CARD_MARGIN;
    float contentW = (float)WIN_W - (float)SIDEBAR_W
                     - (float)CARD_MARGIN * 2.f;
    float curY = (float)HEADER_H + (float)CARD_MARGIN
                 - this->_scrollOffset;

    for (std::size_t i = 0; i < modules.size(); i++) {
        float cardH = this->drawCard(modules[i], contentX, curY, contentW);
        curY += cardH + (float)CARD_MARGIN;
    }

    float totalH = curY + this->_scrollOffset - (float)HEADER_H;
    float visibleH = (float)WIN_H - (float)HEADER_H;
    this->_maxScroll = totalH > visibleH
                       ? totalH - visibleH + 20.f : 0.f;
    if (this->_scrollOffset > this->_maxScroll)
        this->_scrollOffset = this->_maxScroll;

    this->drawRect(0, 0, (float)WIN_W, (float)HEADER_H, BG_HEADER);
    this->drawHeader();
    this->drawRect(0, 0, (float)SIDEBAR_W, (float)WIN_H, BG_SIDEBAR);
    this->drawSidebar(modules);

    if (this->_maxScroll > 0.f) {
        float sbH = visibleH
                    * (visibleH / (totalH > 0 ? totalH : 1));
        if (sbH < 30.f) sbH = 30.f;
        float sbY = (float)HEADER_H + (this->_scrollOffset
                    / this->_maxScroll) * (visibleH - sbH);
        this->drawRect((float)WIN_W - 4.f, sbY, 4.f, sbH,
                       sf::Color(80, 82, 120));
    }

    this->_window->display();
}
