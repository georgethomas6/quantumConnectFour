#include <iostream>
#include "Headers/Game.h"
#include "Headers/GameLogic.h"

/**Constructor
 * @param cols -> number of columns in grid
 * @param rows -> number of rows in grid
 **/
Game::Game(int cols, int rows) {
    this->cols = cols;
    this->rows = rows;
    std::vector<std::vector<std::string>> grid(rows, std::vector<std::string>(cols, "XXX"));
}

/**Plays the game
 * @param window -> a pointer to where all the graphics will occur
 * @param graphics -> a pointer to the graphics handler
 * @param game -> a pointer to the logic handler
 **/
void Game::play(sf::RenderWindow *window, connectFourGraphics *graphics, GameLogic *game) {
    std::string result = round(window, graphics, game);
    if (result == "stalemate") {
        graphics->drawGrid(window);
        graphics->drawPieces(window, game->getGrid());
        window->display();
        std::cout << "It was a stalemate!\n";
    } else {
        graphics->drawGrid(window);
        graphics->drawPieces(window, game->getGrid());
        window->display();
        std::cout << result << " won!\n";
    }
    while (window->isOpen()){
        sf::Event event;
        while(window->pollEvent(event)){
            bool hitEscape = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
            if (hitEscape){
                window->close();
            } else if (event.type == sf::Event::Closed){
                window->close();
            }
        }
    }

}

std::string Game::round(sf::RenderWindow *window, connectFourGraphics *graphics, GameLogic *game) {
    graphics->drawGrid(window);
    graphics->drawPieces(window, game->getGrid());
    graphics->drawTurnInProgress(window, game->getRedPos(), game->getRedTurn());
    window->display();
    while (game->winner() == "XXX") {

        while (window->isOpen()) {

            sf::Event event;
            while (window->pollEvent(event)) {

                bool hitLeftRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
                bool hitDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
                bool hitEscape = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
                if (hitLeftRight) {
                    game->move(event.key.code);
                    if (game->getRedTurn()) {
                        graphics->drawGrid(window);
                        graphics->drawPieces(window, game->getGrid());
                        graphics->drawTurnInProgress(window, game->getRedPos(), game->getRedTurn());
                        window->display();
                        break;
                    } else {
                        graphics->drawGrid(window);
                        graphics->drawPieces(window, game->getGrid());
                        graphics->drawTurnInProgress(window, game->getYelPos(), false);
                        window->display();
                        break;
                    }
                } else if (hitDown) {
                    if (game->getRedTurn()) {
                        //If placement was successful update the picture and change turns, otherwise break and do nothing
                        if (game->place(game->getRedPos())) {
                            game->changeTurn();
                            graphics->drawGrid(window);
                            graphics->drawPieces(window, game->getGrid());
                            graphics->drawTurnInProgress(window, game->getYelPos(),game->getRedTurn());
                            window->display();
                            if (game->winner() == "Red") {
                                return "Red";
                            } else if (game->winner() == "stalemate") {
                                return "stalemate";
                            }
                        } else {
                            graphics->drawGrid(window);
                            graphics->drawPieces(window, game->getGrid());
                            graphics->drawTurnInProgress(window, game->getYelPos(),game->getRedTurn());
                            window->display();
                            break;
                        }
                    } else {
                        if (game->place(game->getYelPos())) {
                            game->changeTurn();
                            graphics->drawGrid(window);
                            graphics->drawPieces(window, game->getGrid());
                            graphics->drawTurnInProgress(window, game->getRedPos(), game->getRedTurn());
                            window->display();
                            if (game->winner() == "Yel") {
                                return "Yellow";
                            } else if (game->winner() == "stalemate") {
                                return "stalemate";
                            }
                        } else {
                            graphics->drawGrid(window);
                            graphics->drawPieces(window, game->getGrid());
                            graphics->drawTurnInProgress(window, game->getRedPos(), game->getRedTurn());
                            window->display();
                            break;
                        }
                    }
                } else if (hitEscape){
                    window->close();
                } else if (event.type == sf::Event::Closed){
                    window->close();
                }
            }
        }
    }
    return "won't reach";
}





