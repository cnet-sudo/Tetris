#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Button {
public:
    // координаты кнопки          текстура нормальной кнопки   текстура нажатой кнопки       
    Button(sf::Vector2f location, const sf::Texture& normal, const sf::Texture& clicked);
    // метод проверки нажати€ на кнопку в параметрах передаютс€ координаты курсора мышки
    bool checkClick(sf::Vector2i mousePos = sf::Vector2i(-1,-1));
    // метод возвращающий текущее состо€ние отображени€ кнопки 
    sf::Sprite* getSprite();
    
private:
    // объект хранит нормальное отображение кнопки
    sf::Sprite normal;
    // объект хранит отображение нажатой кнопки
    sf::Sprite clicked;
    // указатель на Sprite
    sf::Sprite* currentSpr;
    // свойство состо€ни€ кнопки
    bool current=false; 
    // метод мен€ющий отображение кнопки
    void setState(bool);
    
};



