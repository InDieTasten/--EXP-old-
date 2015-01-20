#include <MemoryBank/LocalControl.hpp>

LocalControl::LocalControl()
{
    translateForward = 0.0;
    translateBack    = 0.0;
    translateLeft    = 0.0;
    translateRight   = 0.0;

    targetPoint = Vector(0.0,-20.0);
}
void LocalControl::analyzeAction(std::list<std::string> _action)
{
    //assume "action" already cut away
    if(*_action.begin() == "startTranslateForward")
    {
        translateForward = 100.0;
    }
    else if(*_action.begin() == "endTranslateForward")
    {
        translateForward = 0.0;
    }
    else if(*_action.begin() == "startTranslateBack")
    {
        translateBack = 100.0;
    }
    else if(*_action.begin() == "endTranslateBack")
    {
        translateBack = 0.0;
    }
    else if(*_action.begin() == "startTranslateLeft")
    {
        translateLeft = 100.0;
    }
    else if(*_action.begin() == "endTranslateLeft")
    {
        translateLeft = 0.0;
    }
    else if(*_action.begin() == "startTranslateRight")
    {
        translateRight = 100.0;
    }
    else if(*_action.begin() == "endTranslateRight")
    {
        translateRight = 0.0;
    }
}
