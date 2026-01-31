/*
** EPITECH PROJECT, 2026
** idisplay
** File description:
** idisplay
*/
#include "../Module/IModule.hpp"
namespace Krell
{ 
    class IModule;
    class IDisplay;
};

class Krell::IDisplay
{
    public:
    virtual ~IDisplay() = default;
    virtual bool isRun() const = 0;
    virtual std::string& getName() const = 0;
    virtual void update_display(const std::vector<Krell::IModule*>&modules) = 0;
};