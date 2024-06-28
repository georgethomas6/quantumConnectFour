#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <functional>

class Logic {
private:
    int rows;
    int columns;
    int redPosition;
    int yellowPosition;
    bool cMoveInProgress;
    bool redTurn;
    int quantumMovesPlayed;
    std::vector<int> quantumMoves;
    std::vector<std::vector<std::string>> grid;
    std::vector<std::vector<int>> turns;

public:
    Logic(int columns, int rows);
    int getRedPosition();
    int getYellowPosition();
    bool getCMoveInProgress();
    bool getRedTurn();
    bool checkCols();
    bool checkRows();
    bool checkDiagonals();
    std::string winner();
    std::vector<std::vector<std::string>> getGrid();
    int tryPlace(int column);
    void changeTurn();
    void moveRed(int dx);
    void moveYellow(int dx);
    void changeCMoveInProgress();
    void classicalMove(int column);
    void halfQuantumMove(int column);
    void quantumMoveToTurns();
    void updateBoard();
    void measure();
    void printBoard();

};


