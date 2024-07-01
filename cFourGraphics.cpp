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
          logic(xCells, yCells) {
    this->xCells = xCells + 2;
    this->yCells = yCells + 3;
    this->xSpace = xSpace;
    this->ySpace = ySpace;

    verticalSpace = ySpace / (this->yCells + 2);
    horizontalSpace = xSpace / this->xCells;
    if (verticalSpace > horizontalSpace) {
        radius = horizontalSpace / 3;
    } else {
        radius = verticalSpace / 3;
    }
}

/**Draws the grid*/
void cFourGraphics::drawGrid() {
    window.clear(sf::Color(211, 211, 211));
    //draw columns
    for (int x = 1; x < xCells; x++) {
        //verticalSpace * (yCells - 3) puts the length of the columns at the number of yCells, 5 is the line thickness
        sf::RectangleShape verticalLine(sf::Vector2f(5, verticalSpace * (yCells - 3)));
        verticalLine.setFillColor(sf::Color::Black);

        //verticalSpace * 4 puts the columns at a position four cells down from the top and one from the bottom, this number needs to match the vertical transformation below
        verticalLine.setPosition(horizontalSpace * x, verticalSpace * 4);
        window.draw(verticalLine);
    }
    //draw rows
    //the number four is a vertical transformation
    for (int y = 4; y < yCells + 4; y++) {
        //horizontalSpace * (xCells - 2) + 5 puts the length of the rows enough to finish the grid, 5 is the line thickness
        sf::RectangleShape horizontalLine(sf::Vector2f(horizontalSpace * (xCells - 2) + 5, 5));
        horizontalLine.setFillColor(sf::Color::Black);
        horizontalLine.setPosition(horizontalSpace, verticalSpace * y);
        window.draw(horizontalLine);
    }
    //window.display();
}

/**Draws a circle exactly one vertical cell space above the grid in the column of the given position
 * @param position -> the column in which the circle will be drawn above
 * @param redTurn -> a bool based on if it is red's turn or not, determines color of the circle
 **/
void cFourGraphics::drawClassicTurnInProgress() {

    sf::CircleShape circle(radius);

    if (logic.getRedTurn()) {
        circle.setFillColor(sf::Color::Red);
        circle.setPosition(horizontalSpace * (logic.getRedPosition() + 1) + (horizontalSpace - radius) / 3,
                           verticalSpace + (verticalSpace - radius) / 3);
    } else {
        circle.setFillColor(sf::Color::Yellow);
        circle.setPosition(horizontalSpace * (logic.getYellowPosition() + 1) + (horizontalSpace - radius) / 3,
                           verticalSpace + (verticalSpace - radius) / 3);
    }

    window.draw(circle);
    //only want to display in this function if classical move, otherwise it displays twice SFML doesn't like that
    if (logic.getCMoveInProgress()) {
        //window.display();
    }
}

void cFourGraphics::drawQuantumTurnInProgress() {
    sf::RectangleShape cover;
    cover.setSize(sf::Vector2f(1.2 * radius, 2 * radius));
    cover.setFillColor(sf::Color(211, 211, 211));
    drawClassicTurnInProgress();
    if (logic.getRedTurn()) {
        cover.setPosition(horizontalSpace * (logic.getRedPosition() + 1) + 2 * (horizontalSpace - radius) / 3,
                          verticalSpace + (verticalSpace - radius) / 3);
    } else {
        cover.setPosition(horizontalSpace * (logic.getYellowPosition() + 1) + 2 * (horizontalSpace - radius) / 3,
                          verticalSpace + (verticalSpace - radius) / 3);
    }
    window.draw(cover);
    if (!logic.getCMoveInProgress()) {
        //window.display();
    }
}

/**Draws the pieces placed in the grid
 * @param grid -> a vector containing a vector of strings that serves as the logical grid
 **/
void cFourGraphics::drawPieces() {
    std::vector<std::vector<std::string>> grid = logic.getGrid();
    sf::CircleShape circle(radius);
    sf::RectangleShape cover;
    cover.setSize(sf::Vector2f(1.2 * radius, 2 * radius));
    cover.setFillColor(sf::Color(211, 211, 211));

    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[y].size(); x++) {
            cover.setPosition(horizontalSpace * (x + 1) + 2 * (horizontalSpace - radius) / 3,
                              verticalSpace * (y + 2) + (verticalSpace - radius) / 3);
            if (grid[y][x] == "RRR") {
                circle.setFillColor(sf::Color::Red);
                circle.setPosition(horizontalSpace * (x + 1) + (horizontalSpace - radius) / 3,
                                   verticalSpace * (y + 2) + (verticalSpace - radius) / 3);
                window.draw(circle);
            } else if (grid[y][x] == "YYY") {
                circle.setFillColor(sf::Color::Yellow);
                circle.setPosition(horizontalSpace * (x + 1) + (horizontalSpace - radius) / 3,
                                   verticalSpace * (y + 2) + (verticalSpace - radius) / 3);
                window.draw(circle);
            } else if (grid[y][x] == "RXX") {
                circle.setFillColor(sf::Color::Red);
                circle.setPosition(horizontalSpace * (x + 1) + (horizontalSpace - radius) / 3,
                                   verticalSpace * (y + 2) + (verticalSpace - radius) / 3);
                window.draw(circle);
                window.draw(cover);
            } else if (grid[y][x] == "YXX") {
                circle.setFillColor(sf::Color::Yellow);
                circle.setPosition(horizontalSpace * (x + 1) + (horizontalSpace - radius) / 3,
                                   verticalSpace * (y + 2) + (verticalSpace - radius) / 3);
                window.draw(circle);
                window.draw(cover);
            }
        }
    }
    //window.display();
}


void cFourGraphics::handleKeyPress(sf::Event event) {
    if (event.type == sf::Event::EventType::KeyPressed) {
        if (logic.getRedTurn()) {
            if (event.key.code == sf::Keyboard::Key::Right) {
                logic.moveRed(1);
            } else if (event.key.code == sf::Keyboard::Key::Left) {
                logic.moveRed(-1);
            } else if (event.key.code == sf::Keyboard::Key::Space && logic.getCMoveInProgress()) {
                if (logic.classicalMove(logic.getRedPosition())) {
                    logic.updateBoard();
                    logic.printBoard();
                    std::cout << "\n";
                    logic.changeTurn();
                    logic.resetPositions();
                }
            } else if (event.key.code == sf::Keyboard::Key::Q && logic.getQuantumMovesPlayed() % 2 == 0) {
                logic.changeCMoveInProgress();
            } else if (event.key.code == sf::Keyboard::Key::Space && !logic.getCMoveInProgress()) {
                if (logic.halfQuantumMove(logic.getRedPosition())) {
                    logic.updateBoard();
                    logic.printBoard();
                    std::cout << "\n";
                    logic.resetPositions();
                    if (logic.getQuantumMovesPlayed() % 2 == 0) {
                        logic.changeTurn();
                        logic.changeCMoveInProgress();
                    }
                }
            }
        } else {
            if (event.key.code == sf::Keyboard::Key::Right) {
                logic.moveYellow(1);
            } else if (event.key.code == sf::Keyboard::Key::Left) {
                logic.moveYellow(-1);
            } else if (event.key.code == sf::Keyboard::Key::Space && logic.getCMoveInProgress()) {
                if (logic.classicalMove(logic.getYellowPosition())) {
                    logic.updateBoard();
                    logic.printBoard();
                    std::cout << "\n";
                    logic.changeTurn();
                    logic.resetPositions();
                }
            } else if (event.key.code == sf::Keyboard::Key::Q && logic.getQuantumMovesPlayed() % 2 == 0) {
                logic.changeCMoveInProgress();
            } else if (event.key.code == sf::Keyboard::Key::Space && !logic.getCMoveInProgress()) {
                if (logic.halfQuantumMove(logic.getYellowPosition())) {
                    logic.updateBoard();
                    logic.printBoard();
                    std::cout << "\n";
                    logic.resetPositions();
                    if (logic.getQuantumMovesPlayed() % 2 == 0) {
                        logic.changeTurn();
                        logic.changeCMoveInProgress();
                    }
                }
            }
        }
    }
}

void cFourGraphics::play() {
    sf::Event event;
    drawGrid();
    drawPieces();
    drawClassicTurnInProgress();
    while (window.isOpen()) {


        while (window.pollEvent(event)) {


            if (event.key.code == sf::Keyboard::Key::Escape) {
                window.close();
            }


            if (logic.getTurnsPlayed() % 5 == 0) {
                logic.measure();
            }
            drawGrid();
            drawPieces();

            if (!logic.winner()) {
                handleKeyPress(event);
                if (logic.getCMoveInProgress()) {
                    drawClassicTurnInProgress();
                } else {
                    drawQuantumTurnInProgress();
                }
            }
            window.display();


        }
    }
}





