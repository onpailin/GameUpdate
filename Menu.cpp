#include "Menu.h"
Menu::Menu(float width, float height)
{
    if (!font.loadFromFile("SMpixxo.ttf"))
    {
        //haddle error
    }
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Magenta);
    menu[0].setString("PLAY");
    menu[0].setCharacterSize(65);
    menu[0].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2);
    menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 2.5));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setCharacterSize(65);
    menu[1].setString("LEADERBOARD");
    menu[1].setOrigin(menu[1].getLocalBounds().width / 2, menu[1].getLocalBounds().height / 2);
    menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 3));

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setCharacterSize(65);
    menu[2].setString("EXIT");
    menu[2].setOrigin(menu[2].getLocalBounds().width / 2, menu[2].getLocalBounds().height / 2);
    menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 3.5));
}

Menu::~Menu()
{

}

void Menu::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < MAX_ITEMS; i++)
    {
        window.draw(menu[i]);
    }
}

void Menu::MoveUp()
{
    if (selectedItem - 1 >= 0)
    {
        menu[selectedItem].setFillColor(sf::Color::White);
        selectedItem--;
        menu[selectedItem].setFillColor(sf::Color::Magenta);
    }
}

void Menu::MoveDown()
{
    if (selectedItem + 1 < MAX_ITEMS)
    {
        menu[selectedItem].setFillColor(sf::Color::White);
        selectedItem++;
        menu[selectedItem].setFillColor(sf::Color::Magenta);
    }
}

/*void Menu::update()
{
    this->time = clock.getElapsedTime();
    this->seconds = this->time.asSeconds();
}
*/
int Menu::getSelectedItem()
{
    return this->selectedItem;
}