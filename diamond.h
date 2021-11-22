#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<tmxlite/Map.hpp>
#include<tmxlite/Layer.hpp>
#include<tmxlite/TileLayer.hpp>
#include<tmxlite/ObjectGroup.hpp>

#include <vector>
#include<iostream>

using namespace std;
using namespace sf;
class diamond
{
private:

    Texture* texture;
    IntRect currentFrame;
    void initdiamond();
    float width;
    float height;
    float preWidth;
    float preHeight;

    int delay;
    int frame;
public:
    int decays;
    float x;
    float y;
    CircleShape diamonds;
    diamond(float x, float y, Texture* texture);
    virtual ~diamond();
    void renderdiamond(RenderTarget* target);
    void updatediamond();
    inline FloatRect getGlobalBounds()
    {
        return diamonds.getGlobalBounds();
    }
};

