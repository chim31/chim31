/*
** EPITECH PROJECT, 2026
** SfmlDisplay
** File description:
** Init, themes, constructor, stop, and string parsing helper
*/

#include "SfmlDisplay.hpp"
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>

SfmlDisplay::SfmlDisplay(const std::string &name)
    : ADisplay(name), _window(nullptr), _scrollOffset(0.f), _maxScroll(0.f)
{
    this->initThemes();
}

SfmlDisplay::~SfmlDisplay()
{
    this->stop();
}

void SfmlDisplay::initThemes()
{
    this->_defaultTheme = {sf::Color(100, 160, 255), sf::Color(100, 160, 255), ">"};

    this->_themes["Hostname"] = {sf::Color(0, 212, 170), sf::Color(0, 212, 170), "@"};
    this->_themes["User"] = {sf::Color(0, 212, 170), sf::Color(0, 212, 170), "$"};
    this->_themes["Operating System"] = {sf::Color(77, 142, 255), sf::Color(77, 142, 255), "#"};
    this->_themes["Kernel"] = {sf::Color(77, 142, 255), sf::Color(77, 142, 255), "~"};
    this->_themes["Date & Time"] = {sf::Color(244, 114, 182), sf::Color(244, 114, 182), "*"};
    this->_themes["CPU"] = {sf::Color(255, 140, 66), sf::Color(255, 140, 66), "%"};
    this->_themes["RAM"] = {sf::Color(168, 85, 247), sf::Color(168, 85, 247), "="};
    this->_themes["Network"] = {sf::Color(52, 211, 153), sf::Color(52, 211, 153), "^"};
    this->_themes["Battery"] = {sf::Color(251, 191, 36), sf::Color(251, 191, 36), "+"};
}

const CardTheme &SfmlDisplay::getTheme(const std::string &moduleName) const
{
    auto it = this->_themes.find(moduleName);
    if (it != this->_themes.end())
        return it->second;
    return this->_defaultTheme;
}

void SfmlDisplay::init(const std::vector<Krell::IModule *> &modules)
{
    (void)modules;
    this->_window = new sf::RenderWindow(
        sf::VideoMode(WIN_W, WIN_H), "MyGKrellm",
        sf::Style::Titlebar | sf::Style::Close
    );
    this->_window->setFramerateLimit(30);
    this->_isrun = true;

    std::vector<std::string> fontPaths = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Bold.ttf",
        "/usr/share/fonts/truetype/ubuntu/Ubuntu-Bold.ttf",
        "/usr/share/fonts/TTF/DejaVuSans-Bold.ttf"
    };
    bool loaded = false;
    for (auto &p : fontPaths) {
        if (this->_fontBold.loadFromFile(p)) {
            loaded = true;
            break;
        }
    }
    if (!loaded)
        std::cerr << "Warning: Could not load bold font" << std::endl;

    std::vector<std::string> fontPathsReg = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        "/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf"
    };
    loaded = false;
    for (auto &p : fontPathsReg) {
        if (this->_fontRegular.loadFromFile(p)) {
            loaded = true;
            break;
        }
    }
    if (!loaded)
        this->_fontRegular = this->_fontBold;
}

void SfmlDisplay::stop()
{
    if (this->_window) {
        if (this->_window->isOpen())
            this->_window->close();
        delete this->_window;
        this->_window = nullptr;
    }
    this->_isrun = false;
}

std::string SfmlDisplay::extractValue(const std::string &data, const std::string &key) const
{
    std::istringstream stream(data);
    std::string line;

    while (std::getline(stream, line)) {
        std::size_t pos = line.find(key);
        if (pos == 0 || (pos != std::string::npos && pos < 2)) {
            std::string val = line.substr(pos + key.length());
            std::size_t start = val.find_first_not_of(' ');
            if (start != std::string::npos)
                return val.substr(start);
            return val;
        }
    }
    return "";
}
