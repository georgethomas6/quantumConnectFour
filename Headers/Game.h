#pragma once
#include <SFML/Graphics.hpp>
#include "connectFourGraphics.h"
#include "GameLogic.h"

class Game {

    int cols;
    int rows;
    std::vector<std::vector<std::string>> grid;

public:
    Game(int cols, int rows);
    void play(sf::RenderWindow *window, connectFourGraphics *graphics, GameLogic *game);
    std::string round(sf::RenderWindow *window, connectFourGraphics *graphics, GameLogic *game);


};


