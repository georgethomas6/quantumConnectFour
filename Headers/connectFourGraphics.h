#pragma once

#include <SFML/Graphics.hpp>

class connectFourGraphics {

    int xCells;
    int yCells;
    int xSpace;
    int ySpace;
    int horizontalSpace;
    int verticalSpace;
    sf::RenderWindow window;
public:
    connectFourGraphics(int xCells, int yCells, int xSpace, int ySpace);
    void drawGrid(sf::RenderWindow *window);
    void drawPieces(sf::RenderWindow *window, std::vector<std::vector<std::string>> grid);
    void drawTurnInProgress(sf::RenderWindow *window, int position, bool redTurn);
    int getXCells();
    int getYCells();
};

