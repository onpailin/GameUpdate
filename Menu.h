#pragma once
#include<SFML\Graphics.hpp>
#define MAX_ITEMS 3

class Menu
{
public:
    Menu(float width, float height);
    ~Menu();

    void draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown();
    void update();
    int GetPressedItem()
    {
        return selectedItem;
    }
    int getSelectedItem();
private:

    int selectedItem = 0;
    sf::Font font;
    sf::Text menu[MAX_ITEMS]; //play score howtoplay exit
};
