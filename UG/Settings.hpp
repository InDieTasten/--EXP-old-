#ifndef _Settings_hpp_
#define _Settings_hpp_

struct Settings
{
    int dockWidth;
    sf::Color   guiDockBackground;
    sf::Color   guiDockBackgroundHover;
    sf::Color   guiDockBorder;
    sf::Color   guiDockBorderHover;
    sf::Color   guiDockItemBackground;
    sf::Color   guiDockItemBackgroundHover;
    sf::Color   guiDockItemBorder;
    sf::Color   guiDockItemBorderHover;

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
    std::string guiMenuTitleFont;

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
    sf::Color   guiHorsliderButtonBorderInactive;
    sf::Color   guiHorsliderButtonBorderActive;
    sf::Color   guiHorsliderButtonBorderHover;
    sf::Color   guiHorsliderBarBackgroundInactive;
    sf::Color   guiHorsliderBarBackgroundActive;
    sf::Color   guiHorsliderBarBorderInactive;
    sf::Color   guiHorsliderBarBorderActive;
    sf::Color   guiHorsliderSliderBackgroundInactive;
    sf::Color   guiHorsliderSliderBackgroundActive;
    sf::Color   guiHorsliderSliderBackgroundHover;
    sf::Color   guiHorsliderSliderBackgroundMoving;
    sf::Color   guiHorsliderSliderBorderInactive;
    sf::Color   guiHorsliderSliderBorderActive;
    sf::Color   guiHorsliderSliderBorderHover;
    sf::Color   guiHorsliderSliderBorderMoving;
    int         guiHorsliderTextScale;
    std::string guiHorsliderFontID;

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
