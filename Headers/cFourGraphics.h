#pragma once

#include <SFML/Graphics.hpp>
#include "GameLogic.h"

class cFourGraphics {

    int xCells;
    int yCells;
    int xSpace;
    int ySpace;
    GameLogic logic;
    int horizontalSpace;
    int verticalSpace;
    int radius;
    sf::RenderWindow window;
public:
    cFourGraphics(int xCells, int yCells, int xSpace, int ySpace);
    void drawGrid();
    void drawPieces();
    void drawClassicTurnInProgress();
    void drawQuantumTurnInProgress();
    void handleKeyPress(sf::Event event);
    GameLogic getLogic();
    void play();
};

