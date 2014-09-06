#ifndef _Settings_hpp_
#define _Settings_hpp_

struct Settings
{
    int dockWidth;

    sf::Color   guiMenuBorderInactive;
    sf::Color   guiMenuBorderActive;
    sf::Color   guiMenuBackgroundInactive;
    sf::Color   guiMenuBackgroundActive;
    sf::Color   guiMenuTitleBackgroundInactive;
    sf::Color   guiMenuTitleBackgroundActive;
    sf::Color   guiMenuTitleTextInactive;
    sf::Color   guiMenuTitleTextActive;
    int         guiMenuTitleHeight;
    int         guiMenuTitleTextScale;
    std::string guiTitleFont;

    sf::Color   guiButtonBackgroundInactive;
    sf::Color   guiButtonBackgroundActive;
    sf::Color   guiButtonBackgroundHover;
    sf::Color   guiButtonBorderInactive;
    sf::Color   guiButtonBorderActive;
    sf::Color   guiButtonBorderHover;
    sf::Color   guiButtonTextInactive;
    sf::Color   guiButtonTextActive;
    sf::Color   guiButtonTextHover;
    int         guiButtonTextScale;
    std::string guiButtonFontID;

    sf::Color   guiHorsliderButtonBackgroundInactive;
    sf::Color   guiHorsliderButtonBackgroundActive;
    sf::Color   guiHorsliderButtonBackgroundHover;
    sf::Color   guiHorsliderguiHorsliderButtonBorderInactive;
    sf::Color   guiHorsliderButtonBorderActive;
    sf::Color   guiHorsliderButtonBorderHover;
    sf::Color   guiHorsliderSliderBackgroundInactive;
    sf::Color   guiHorsliderSliderBackgroundActive;
    sf::color   guiHorsliderSliderBackgroundHover;
    sf::Color   guiHorsliderSliderBackgroundMoving;
    int         guiHorsliderTextScale;
    std::string guiHorsliderFontID

    sf::Color   guiLabelTextInactive;
    sf::Color   guiLabelTextActive;
    sf::Color   guiLabelTextHover;
    int         guiLabelTextScale;
    std::string guiLabelFontID;

    sf::Color   guiTextboxBackgroundInactive;
    sf::Color   guiTextboxBackgroundActive;
    sf::Color   guiTextboxBackgroundHover;
    sf::Color   guiTextboxBorderInactive;
    sf::Color   guiTextboxguiTextboxBorderActive;
    sf::Color   guiTextboxBorderHover;
    int         guiTextboxTextScale;
    std::string guiTextboxFontID;
};

#endif
