#include<iostream>
#include "Game.h"
#include <iostream>
#include "Menu.h"
#include "ScoreList.h"

#define GAME_MENU 0
#define GAME_PLAY 1
#define GAME_OVER 2
#define GAME_Leaderboard 3

int main()
{

    ScoreList score_list("highscore.txt");
    score_list.loadFile();

    RenderWindow window(VideoMode(1280, 960), "Game", Style::Titlebar | Style::Close);
    srand(static_cast<unsigned>(time(NULL)));
    window.setFramerateLimit(60);
    Font font;
    font.loadFromFile("SMpixxo.ttf");
    Game game(&window);
    Menu menu(window.getSize().x, window.getSize().y);

    int game_state = GAME_MENU;
    float time_left = 30.0f;
    float time = time_left;
    sf::Texture texture;
    if (!texture.loadFromFile("menu.jpg")) //ใส่background
    {
        //haddle error
    }


    sf::Sprite background;
    background.setTexture(texture);

    //Game over
    sf::Texture gameoevrtex;
    sf::Sprite bgover;
    std::string name = "";
    int score;
    

    gameoevrtex.loadFromFile("gameover.jpg");
    bgover.setTexture(gameoevrtex);
    //leder
    sf::Texture bgLB;
    sf::Sprite bgL;
    bgLB.loadFromFile("leaderboard.jpg");
    bgL.setTexture(bgLB);

    while (window.isOpen())
    {
        window.clear();
        if (game_state == GAME_MENU) { // State Menu

            // ดึง Event ต่าง ๆ ใน Menu
            Event ev;
            while (window.pollEvent(ev)) {
                if (ev.type == Event::Closed) window.close();
                if (ev.type == Event::TextEntered && ev.text.unicode == 13) {
                    switch (menu.GetPressedItem()) {
                    case 0:
                        std::cout << "PLAY has been pressed" << std::endl;
                        game_state = GAME_PLAY;
                        break;

                    case 1:
                        std::cout << "Leaderboard has been pressed" << std::endl;
                        game_state = GAME_Leaderboard;
                        break;

                    case 2:
                        window.close();
                        break;
                    }
                }
                switch (ev.type) {
                case sf::Event::KeyReleased:
                    switch (ev.key.code) {
                    case sf::Keyboard::Up:
                        menu.MoveUp();
                        break;

                    case sf::Keyboard::Down:
                        menu.MoveDown();
                        break;
                    }
                    break;

                }
            }
            //Menu
            Text text;

            window.draw(background);
            menu.draw(window);
            //window.draw(text);

        }
        if (game_state == GAME_PLAY) { // State Game play
            Event ev;
            while (window.pollEvent(ev)) {
                time -= 0.1f;
                if (time <= 0)
                {
                    //cout<<"hello"<<endl;
                    game_state = GAME_OVER;
                    time = time_left;
                    game.player.setPosition(20.f, 200.f);
                }
                if (ev.type == Event::Closed) window.close();
            }
            // Update Game
            game.update();

            // Render Game
            game.render();
        }
        if (game_state == GAME_OVER)
        {

            Event ev;
            while (window.pollEvent(ev)) {
                if (ev.type) {
                    switch (ev.type)
                    {
                    case Event::Closed:
                        window.close();
                        break;
                    case Event::TextEntered:
                        std::cout << ev.text.unicode << std::endl;


                        if (ev.text.unicode == 8) {
                            if (name.size() > 0) name.erase(name.end() - 1);
                        }
                        if (ev.text.unicode == 13) {

                            score_list.addEntry(name, game.getPoint());
                            game.setPoint(0);
                            game_state = GAME_MENU;
                            game.endGame = false;
                            name = "";
                        }
                        if ((ev.text.unicode >= 'A' && ev.text.unicode <= 'Z') or (ev.text.unicode >= 'a' && ev.text.unicode <= 'z'))
                        {
                            if (name.size() < 10)name.push_back(ev.text.unicode);

                        }

                        std::cout << name << std::endl;
                        break;

                    default:
                        break;
                    }

                }
                if (ev.type == Event::Closed) window.close();

            }
            window.draw(bgover);
            Text text;
            text.setFont(font);
            text.setFillColor(Color::White);
            text.setPosition(550, 700);
            text.setString(name + "Enter your name_");
            window.draw(text);

            text.setFont(font);
            text.setFillColor(Color::White);
            text.setPosition(500, 750);
            text.setCharacterSize(48);
            text.setString("You Point : "+to_string(game.getPoint()));
            window.draw(text);
        }
        if (game_state == GAME_Leaderboard) 
        {
            Event ev;
            while (window.pollEvent(ev)) {
                if (ev.type == Event::Closed) window.close();
                switch (ev.type) {
                case sf::Event::KeyReleased:
                    switch (ev.key.code) {
                    case sf::Keyboard::Escape:
                        game_state = GAME_MENU;
                        break;
                    }
                    break;
                }
            }

            // Draw
            window.draw(bgL);

            Text text;
            text.setFont(font);
            text.setFillColor(Color::White);

            //highscore T.
            int show_max_entry = 10;
            for (int i = 0; i < score_list.get().size(); i++) {
                if (i >= show_max_entry)break;
                text.setPosition(350,300 + (i * 40));
                text.setString(score_list.get().at(i).getName());
                window.draw(text);
            }
            for (int i = 0; i < score_list.get().size(); i++) {
                if (i >= show_max_entry)break;
                text.setPosition(900, 300+ (i * 40));
                text.setString(to_string(score_list.get().at(i).getScore()));
                window.draw(text);
            }
 
        }
        window.display();
    }

    score_list.saveFile();
    return 0;
}