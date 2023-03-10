#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Button {
public:
    Button(sf::Vector2f location, const sf::Texture& normal, const sf::Texture& clicked);

    bool checkClick(sf::Vector2i mousePos, bool position) ;
    
    sf::Sprite* getSprite();
    
private:
    sf::Sprite normal;
    sf::Sprite clicked;
    sf::Sprite* currentSpr;
    bool current=false;
    void setState(bool);
    
};



