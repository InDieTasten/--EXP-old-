#include "LocalControl.hpp"

LocalControl::LocalControl()
{
    targetRotation   = 0.0;

    rotateTarget     = 0.0;
    translateForward = 0.0;
    translateBack    = 0.0;
    translateLeft    = 0.0;
    translateRight   = 0.0;
}
void LocalControl::analyzeAction(std::list<std::string> _action)
{

}
