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
class Coins
{
    private:
        
        Texture* texture;
        IntRect currentFrame;
        void initcoins();
        float width;
        float height;
        float preWidth;
        float preHeight;

        int delay;
        int frame;
    public:
        int decay;
        float x;
        float y;
        CircleShape coin;
        Coins(float x, float y, Texture* texture);
        virtual ~Coins();
        void rendercoins(RenderTarget * target);
        void updatecoins();
        inline FloatRect getGlobalBounds()
        {
            return coin.getGlobalBounds();
        }
};

