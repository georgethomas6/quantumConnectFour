//
// Created by George Thomas Alexander on 6/12/24.
//
#pragma once
#include <SFML/Graphics.hpp>

class GameLogic {
private:
    bool redTurn;
    int yellowPosition;
    int redPosition;
    int cols;
    int rows;
    std::vector<std::vector<std::string>> grid;


public:

    GameLogic(int cols, int rows);
    int getRedPos();
    int getYelPos();
    void changeTurn();
    bool getRedTurn();
    bool place(int position);
    bool checkCols();
    bool checkRows();
    bool checkDiagonals();
    void move(sf::Keyboard::Key event);
    std::string winner();
    std::vector<std::vector<std::string>> getGrid();
};



