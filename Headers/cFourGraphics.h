#pragma once

#include <SFML/Graphics.hpp>

class cFourGraphics {

    int xCells;
    int yCells;
    int xSpace;
    int ySpace;
    int horizontalSpace;
    int verticalSpace;
    int radius;
    sf::RenderWindow window;
public:
    cFourGraphics(int xCells, int yCells, int xSpace, int ySpace);
    void drawGrid();
    void drawPieces(std::vector<std::vector<std::string>> grid);
    void drawClassicTurnInProgress(int position, bool redTurn);
    void drawQuantumTurnInProgress(int positionOne, bool redTurn);
    void wait();
};

