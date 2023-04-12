#include "Button.h"

Button::Button(sf::Vector2f location, const sf::Texture& normal, const sf::Texture& clicked)
{
    // устанавливаем текстуры для спрайтов 
    this->normal.setTexture(normal);   // нормальная кнопка
    this->clicked.setTexture(clicked); // кнопка нажата
    // устанавливаем координаты расположения кнопок
    this->normal.setPosition(location);
    this->clicked.setPosition(location);
    // присваиваем указателю нормальное состояние кнопки
    currentSpr = &this->normal;
}

bool Button::checkClick(sf::Vector2i mousePos) 
{
    // если передаются координаты курсора мышки делаем проверку, 
    // что курсор находится в пределах границ кнопки
    if (mousePos.x>=0)
    {
    if ((static_cast<float>(mousePos.x) > currentSpr->getPosition().x && 
        static_cast<float>(mousePos.x) < (currentSpr->getPosition().x + 
        currentSpr->getGlobalBounds().width))
        && (static_cast<float>(mousePos.y) > currentSpr->getPosition().y && 
            static_cast<float>(mousePos.y) < (currentSpr->getPosition().y + 
        currentSpr->getGlobalBounds().height)) )
        {
        // меняем состояние кнопки на противоположное
        setState(!current); return true;
        }
      }
    else
        // если кнопка нажата меняем её вид в нормальное положение
        if (current) 
        { 
            setState(!current); return true; 
        } 
    return false;
}

void Button::setState(bool which) 
{
    current = which;
    
    if (current) 
    {
        currentSpr = &clicked;
        
        return;
    }
    currentSpr = &normal;  
}

sf::Sprite* Button::getSprite() 
{
    return currentSpr;
}








