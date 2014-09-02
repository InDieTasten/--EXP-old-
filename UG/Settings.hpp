#ifndef _Settings_hpp_
#define _Settings_hpp_

struct Settings
{
    int guiOpacity1;
    int guiOpacity2;
    int guiOpacity3;
    sf::Color guiActiveMenuBorder;
    sf::Color guiInactiveMenuBorder;
    sf::Color guiActiveMenuBackground;
    sf::Color guiInactiveMenuBackground;
    sf::Color guiActiveMenuTitleBackground;
    sf::Color guiInactiveMenuTitleBackground;
    sf::Color guiActiveMenuTitleText;
    sf::Color guiInactiveMenuTitleText;

    std::string guiTitleFont;

    int dockWidth;
};

#endif
