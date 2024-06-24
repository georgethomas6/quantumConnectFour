#include "Headers/connectFourGraphics.h"
#include <SFML/Graphics.hpp>
#include <iostream>

/**Constructor
 * @param xCells -> number of horizontal cells in grid
 * @param yCells -> number of vertical cells in grid
 * @param xSpace -> total horizontal space of the window
 * @param ySpace -> total vertical space of the window
 **/
connectFourGraphics::connectFourGraphics(int xCells, int yCells, int xSpace, int ySpace) {
    this->xCells = xCells + 2;
    this->yCells = yCells + 3;
    this->xSpace = xSpace;
    this->ySpace = ySpace;
    verticalSpace = ySpace / this->yCells;
    horizontalSpace = xSpace / this->xCells;
}

/**Returns the number of horizontal cells in the grid*/
int connectFourGraphics::getXCells(){
    return xCells;
}

/**Returns the number of vertical cells in the grid*/
int connectFourGraphics::getYCells(){
    return yCells;
}

/**Draws the grid
 * @param window -> a pointer to the window in which the grid is being drawn*/
void connectFourGraphics::drawGrid(sf::RenderWindow *window) {
    window->clear(sf::Color(211, 211, 211));
    //draw columns
    for (int x = 1; x < xCells; x++) {
        //verticalSpace * (yCells - 3) puts the length of the columns at the number of yCells, 5 is the line thickness
        sf::RectangleShape verticalLine(sf::Vector2f(5, verticalSpace * (yCells - 3)));
        verticalLine.setFillColor(sf::Color::Black);

        //verticalSpace * 2 puts the columns at a position two cells down from the top and one from the bottom
        verticalLine.setPosition(horizontalSpace * x, verticalSpace * 2);
        window->draw(verticalLine);
    }
    //draw rows
    for (int y = 2; y < yCells; y++) {
        //horizontalSpace * (xCells - 2) + 5 puts the length of the rows enough to finish the grid, 5 is the line thickness
        sf::RectangleShape horizontalLine(sf::Vector2f(horizontalSpace * (xCells - 2) + 5, 5));
        horizontalLine.setFillColor(sf::Color::Black);
        horizontalLine.setPosition(horizontalSpace, verticalSpace * y);
        window->draw(horizontalLine);
    }
}

/**Draws a circle exactly one vertical cell space above the grid in the column of the given position
 * @param window -> a pointer to the window where the drawing will take place
 * @param position -> the column in which the circle will be drawn above
 * @param redTurn -> a bool based on if it is red's turn or not, determines color of the circle
 **/
void connectFourGraphics::drawTurnInProgress(sf::RenderWindow *window, int position, bool redTurn) {
    int radius;
    if (verticalSpace > horizontalSpace) {
        radius = horizontalSpace / 3;
    } else {
        radius = verticalSpace / 3 ;
    }
    sf::CircleShape circle(radius);

    if (redTurn){
        circle.setFillColor(sf::Color::Red);
    } else {
        circle.setFillColor(sf::Color::Yellow);
    }
    circle.setPosition(horizontalSpace * (position + 1)  + (horizontalSpace - radius) / 3, verticalSpace + (verticalSpace - radius) / 3 );
    window->draw(circle);
}

/**Draws the pieces placed in the grid
 * @param window -> a pointer to the window where the drawing will take place
 * @param grid -> a vector containing a vector of strings that serves as the logical grid
 **/
void connectFourGraphics::drawPieces(sf::RenderWindow *window, std::vector<std::vector<std::string>> grid) {
    int radius;
    if (verticalSpace > horizontalSpace) {
        radius = horizontalSpace / 3;
    } else {
        radius = verticalSpace / 3 ;
    }

    sf::CircleShape circle(radius);

    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[y].size(); x++) {
            if (grid[y][x] == "red") {
                circle.setFillColor(sf::Color::Red);
                circle.setPosition(horizontalSpace * (x + 1)  + (horizontalSpace - radius) / 3, verticalSpace * (y + 2) + (verticalSpace - radius) / 3 );
                window->draw(circle);
            } else if (grid[y][x] == "yel") {
                circle.setFillColor(sf::Color::Yellow);
                circle.setPosition(horizontalSpace * (x + 1)  + (horizontalSpace - radius) / 3 , verticalSpace * (y + 2) + (verticalSpace - radius) / 3 );
                window->draw(circle);
            }
        }
    }
}



