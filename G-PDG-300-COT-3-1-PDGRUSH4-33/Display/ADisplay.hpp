/*
** EPITECH PROJECT, 2026
** adisplay
** File description:
** adisplay
*/

#include "IDisplay.hpp"

class ADisplay : public Krell::IDisplay {
    private:
        std::string &_name;
        bool _isrun = false;
    public:
    ADisplay(std::string name);
    bool isRun() const override;
    std::string& getName() const override;
    virtual void update_display(const std::vector<Krell::IModule*>&modules) override = 0;
};