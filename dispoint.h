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
class dispoint
{
private:

    Texture* texture;
    IntRect currentFrame;
    void initdispoint();
    float width;
    float height;
    float preWidth;
    float preHeight;

    int delay;
    int frame;
public:
    int decayss;
    float x;
    float y;
    CircleShape dispoints;
    dispoint(float x, float y, Texture* texture);
    virtual ~dispoint();
    void renderdispoint(RenderTarget* target);
    void updatedispoint();
    inline FloatRect getGlobalBounds()
    {
        return dispoints.getGlobalBounds();
    }
};


