#ifndef STATE_H
#define STATE_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>

extern int CurrentState;

using namespace sf;
using namespace std;

class State
{
private:
    int state;

public:
    int currentState();
    void NextState(int s);

};
#endif // !STATE_H
