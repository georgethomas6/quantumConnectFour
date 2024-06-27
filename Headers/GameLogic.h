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
    std::vector<std::vector<int>> moves;
    std::vector<std::vector<std::string>> grid;


public:

    GameLogic(int cols, int rows);
    int getRedPos();
    int getYelPos();
    void changeTurn();
    void updateBoard();
    bool getRedTurn();
    bool checkCols();
    bool checkRows();
    bool checkDiagonals();
    int tryPlace(int pos);
    bool classicalMove(int position);
    bool quantumMove(int positionOne, int positionTwo);
    std::string winner();
    void measure();
    std::vector<std::vector<std::string>> getGrid();
    void printBoard();
};



