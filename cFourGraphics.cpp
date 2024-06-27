#include "Headers/cFourGraphics.h"
#include <SFML/Graphics.hpp>
#include <iostream>

/**Constructor
 * @param xCells -> number of horizontal cells in grid
 * @param yCells -> number of vertical cells in grid
 * @param xSpace -> total horizontal space of the window
 * @param ySpace -> total vertical space of the window
 **/
cFourGraphics::cFourGraphics(int xCells, int yCells, int xSpace, int ySpace)
    : window(sf::VideoMode(xSpace, ySpace), "C4"),
    logic(xCells, yCells)
    {
    this->xCells = xCells + 2;
    this->yCells = yCells + 3;
    this->xSpace = xSpace;
    this->ySpace = ySpace;

    verticalSpace = ySpace / this->yCells;
    horizontalSpace = xSpace / this->xCells;
    if (verticalSpace > horizontalSpace) {
        radius = horizontalSpace / 3;
    } else {
        radius = verticalSpace / 3 ;
    }
}

/**Draws the grid
 */
void cFourGraphics::drawGrid() {
    window.clear(sf::Color(211, 211, 211));
    //draw columns
    for (int x = 1; x < xCells; x++) {
        //verticalSpace * (yCells - 3) puts the length of the columns at the number of yCells, 5 is the line thickness
        sf::RectangleShape verticalLine(sf::Vector2f(5, verticalSpace * (yCells - 3)));
        verticalLine.setFillColor(sf::Color::Black);

        //verticalSpace * 2 puts the columns at a position two cells down from the top and one from the bottom
        verticalLine.setPosition(horizontalSpace * x, verticalSpace * 2);
        window.draw(verticalLine);
    }
    //draw rows
    for (int y = 2; y < yCells; y++) {
        //horizontalSpace * (xCells - 2) + 5 puts the length of the rows enough to finish the grid, 5 is the line thickness
        sf::RectangleShape horizontalLine(sf::Vector2f(horizontalSpace * (xCells - 2) + 5, 5));
        horizontalLine.setFillColor(sf::Color::Black);
        horizontalLine.setPosition(horizontalSpace, verticalSpace * y);
        window.draw(horizontalLine);
    }
}

/**Draws a circle exactly one vertical cell space above the grid in the column of the given position
 * @param position -> the column in which the circle will be drawn above
 * @param redTurn -> a bool based on if it is red's turn or not, determines color of the circle
 **/
void cFourGraphics::drawClassicTurnInProgress() {

    sf::CircleShape circle(radius);

    if (logic.getRedTurn()){
        circle.setFillColor(sf::Color::Red);
        circle.setPosition(horizontalSpace * (logic.getRedPos() + 1)  + (horizontalSpace - radius) / 3, verticalSpace + (verticalSpace - radius) / 3 );
    } else {
        circle.setFillColor(sf::Color::Yellow);
        circle.setPosition(horizontalSpace * (logic.getYelPos() + 1)  + (horizontalSpace - radius) / 3, verticalSpace + (verticalSpace - radius) / 3 );
    }

    window.draw(circle);
    window.display();
}

void cFourGraphics::drawQuantumTurnInProgress() {
    sf::RectangleShape cover;
    cover.setSize(sf::Vector2f (  1.2 * radius, 2 * radius));
    cover.setFillColor(sf::Color (211, 211, 211));
    drawClassicTurnInProgress();
    if (logic.getRedTurn()) {
        cover.setPosition(horizontalSpace * (logic.getRedPos() + 1) + 2 * (horizontalSpace - radius) / 3,
                          verticalSpace + (verticalSpace - radius) / 3);
    } else {
        cover.setPosition(horizontalSpace * (logic.getYelPos() + 1) + 2 * (horizontalSpace - radius) / 3,
                          verticalSpace + (verticalSpace - radius) / 3);
    }
    window.draw(cover);
    window.display();
}

/**Draws the pieces placed in the grid
 * @param grid -> a vector containing a vector of strings that serves as the logical grid
 **/
void cFourGraphics::drawPieces() {
    std::vector<std::vector<std::string>> grid = logic.getGrid();
    sf::CircleShape circle(radius);
    sf::RectangleShape cover;
    cover.setSize(sf::Vector2f (  1.2 * radius, 2 * radius));
    cover.setFillColor(sf::Color (211, 211, 211));

    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[y].size(); x++) {
            cover.setPosition( horizontalSpace * (x + 1)  + 2 * (horizontalSpace - radius) / 3, verticalSpace * (y + 2) + (verticalSpace - radius) / 3 );
            if (grid[y][x] == "RRR") {
                circle.setFillColor(sf::Color::Red);
                circle.setPosition(horizontalSpace * (x + 1)  + (horizontalSpace - radius) / 3, verticalSpace * (y + 2) + (verticalSpace - radius) / 3 );
                window.draw(circle);
            } else if (grid[y][x] == "YYY") {
                circle.setFillColor(sf::Color::Yellow);
                circle.setPosition(horizontalSpace * (x + 1)  + (horizontalSpace - radius) / 3, verticalSpace * (y + 2) + (verticalSpace - radius) / 3 );
                window.draw(circle);
            } else if (grid[y][x] == "RXX"){
                circle.setFillColor(sf::Color::Red);
                circle.setPosition(horizontalSpace * (x + 1)  + (horizontalSpace - radius) / 3 , verticalSpace * (y + 2) + (verticalSpace - radius) / 3 );
                window.draw(circle);
                window.draw(cover);
            } else if (grid[y][x] == "YXX") {
                circle.setFillColor(sf::Color::Yellow);
                circle.setPosition(horizontalSpace * (x + 1)  + (horizontalSpace - radius) / 3 , verticalSpace * (y + 2) + (verticalSpace - radius) / 3 );
                window.draw(circle);
                window.draw(cover);
            }
        }
    }
}

void cFourGraphics::handleKeyPress(sf::Event event) {
    if (event.type == sf::Event::EventType::KeyPressed) {
        if (logic.getRedTurn()) {
            if (event.key.code == sf::Keyboard::Key::Right) {
                logic.moveRed(1);
            } else if (event.key.code == sf::Keyboard::Key::Left) {
                logic.moveRed(-1);
            } else if (event.key.code == sf::Keyboard::Key::Space) {
                logic.classicalMove(logic.getRedPos());
            }
        } else {
            if (event.key.code == sf::Keyboard::Key::Right) {
                logic.moveYellow(1);
            } else if (event.key.code == sf::Keyboard::Key::Left) {
                logic.moveYellow(-1);
            } else if (event.key.code == sf::Keyboard::Key::Space) {
                logic.classicalMove(logic.getYelPos());
            }
        }
    }
}
void cFourGraphics::play(){
    sf::Event event;
    drawGrid();
    drawPieces();
    drawClassicTurnInProgress();
    while (window.isOpen()){


    while (window.pollEvent(event)){

       if (event.key.code == sf::Keyboard::Key::Escape){
           window.close();
       }
       handleKeyPress(event);
       drawGrid();
       drawPieces();
       drawClassicTurnInProgress();
       logic.printBoard();
       std::cout<< "\n";

    }
    }
}

GameLogic cFourGraphics::getLogic() {
    return logic;
}



