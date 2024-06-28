#pragma once

#include <SFML/Graphics.hpp>
#include "Logic.h"

class cFourGraphics {

    int xCells;
    int yCells;
    int xSpace;
    int ySpace;
    Logic logic;
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
    void drawHalfQuantumMove();
    sf::Keyboard::Key handleKeyPress(sf::Event event);
    void handleQuantumMove(sf::Event event);
    Logic getLogic();
    void play();
};

