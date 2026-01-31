/*
** EPITECH PROJECT, 2026
** SfmlDisplay
** File description:
** SFML graphical display mode - Modern card-based dashboard
*/

#ifndef SFMLDISPLAY_HPP_
#define SFMLDISPLAY_HPP_

#include "ADisplay.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>

struct CardTheme {
    sf::Color accent;
    sf::Color barFill;
    std::string icon;
};

class SfmlDisplay : public ADisplay
{
    private:
        sf::RenderWindow *_window;
        sf::Font _fontBold;
        sf::Font _fontRegular;
        float _scrollOffset;
        float _maxScroll;

        static const int WIN_W = 960;
        static const int WIN_H = 720;
        static const int SIDEBAR_W = 220;
        static const int HEADER_H = 56;
        static const int CARD_MARGIN = 10;
        static const int CARD_PAD = 14;

        std::map<std::string, CardTheme> _themes;
        CardTheme _defaultTheme;

        void initThemes();

        void drawBackground();
        void drawSidebar(const std::vector<Krell::IModule *> &modules);
        void drawHeader();
        float drawCard(Krell::IModule *mod, float x, float y, float w);

        float drawCardDateTime(const std::map<std::string, std::string> &d, float x, float y, float w);
        float drawCardSystem(const std::string &name, const std::map<std::string, std::string> &d, float x, float y, float w);
        float drawCardCpu(const std::map<std::string, std::string> &d, float x, float y, float w);
        float drawCardRam(const std::map<std::string, std::string> &d, float x, float y, float w);
        float drawCardNetwork(const std::map<std::string, std::string> &d, float x, float y, float w);
        float drawCardBattery(const std::map<std::string, std::string> &d, float x, float y, float w);
        float drawCardGeneric(const std::string &name, const std::map<std::string, std::string> &d, float x, float y, float w);

        void drawRect(float x, float y, float w, float h, sf::Color fill, sf::Color outline = sf::Color::Transparent, float outlineThick = 0.f);
        void drawProgressBar(float x, float y, float w, float h, float percent, sf::Color fill, sf::Color bg);
        void drawText(const std::string &str, float x, float y, unsigned int size, sf::Color color, bool bold = false);
        void drawCardHeader(const std::string &icon, const std::string &title, float x, float y, float w, sf::Color accent);
        void drawSeparator(float x, float y, float w, sf::Color color);

        const CardTheme &getTheme(const std::string &moduleName) const;
        float getTextWidth(const std::string &str, unsigned int size, bool bold = false);

    public:
        SfmlDisplay(const std::string &name);
        ~SfmlDisplay();
        void init(const std::vector<Krell::IModule *> &modules) override;
        void update_display(std::vector<Krell::IModule *> &modules) override;
        void stop() override;
};

#endif /* !SFMLDISPLAY_HPP_ */
