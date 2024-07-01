#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <functional>

class Logic {

private:
    int turnsPlayed;
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

    int getQuantumMovesPlayed();

    int getTurnsPlayed();

    bool getCMoveInProgress();

    bool getRedTurn();

    bool checkCols();

    bool checkRows();

    bool checkDiagonals();

    bool winner();

    std::vector<std::vector<std::string>> getGrid();

    int tryPlace(int column);

    void changeTurn();

    void resetPositions();

    void moveRed(int dx);

    void moveYellow(int dx);

    void changeCMoveInProgress();

    bool classicalMove(int column);

    bool halfQuantumMove(int column);

    void quantumMoveToTurns();

    void updateBoard();

    void measure();

    void printBoard();

    void printMoves();
};


