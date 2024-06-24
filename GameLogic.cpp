#include "Headers/GameLogic.h"
#include <SFML/Graphics.hpp>
#include <iostream>


GameLogic::GameLogic(int cols, int rows) {
    redTurn = true;
    yellowPosition = cols / 2;
    redPosition = cols / 2;
    this->cols = cols;
    this->rows = rows;
    grid = std::vector<std::vector<std::string>>(rows, std::vector<std::string>(cols, "XXX"));
}

/**Returns red's position*/
int GameLogic::getRedPos(){
    return redPosition;
}

/**Returns yellow's position*/
int GameLogic::getYelPos(){
    return yellowPosition;
}

/**Returns true if it is red's turn, false if it is yellow's turn*/
bool GameLogic::getRedTurn() {
    return redTurn;
}

/**Returns the grid which is a vector containing vectors consisting of strings*/
std::vector<std::vector<std::string>> GameLogic::getGrid() {
    return grid;
}

/**Sets the bool of redTurn to the opposite of its current value*/
void GameLogic::changeTurn() {
    redPosition = cols /2;
    yellowPosition = cols/2;
    redTurn = !redTurn;
}

/**Returns true on success of placement, false otherwise
 * @param position -> the column number at which the player is attempting to place their piece
 **/
bool GameLogic::place(int position) {
    //finds the row at which the first piece is stored in the column
    int depth = 0;
    for (int i = 0; i < rows; i++) {
        if (grid[i][position] == "XXX") {
            depth++;
        } else {
            break;
        }
    }

    //could not place
    if (depth == 0) {
        return false;
    } else {
        //Decrement depth because it is 1 ahead of i at break statement
        depth--;
        //place piece
        if (redTurn) {
            grid[depth][position] = "red";
        } else {
            grid[depth][position] = "yel";
        }
        return true;
    }
}

/**Returns Red if red won the game, Yel if yellow won the game, stalemate if neither won, and XXX if game is still in progress*/
std::string GameLogic::winner() {
    int cnt = 0;
    for (std::vector<std::string> row : grid){
        for (std::string entry : row){
            if (entry == "XXX"){
                cnt++;
            }
        }
    }

    if (cnt == 0){
        return "stalemate";
    } else if (redTurn && (checkCols() || checkRows() || checkDiagonals())){
        return "Yel";
    } else if (!redTurn && (checkCols()  || checkRows() || checkDiagonals())){
        return "Red";
    }

    return "XXX";
}

/**Returns true if there is a connect4 in the rows, false otherwise*/
bool GameLogic::checkRows() {
    for (std::vector<std::string> row: grid) {
        //check every four positions in the row for four of a kind
        for (int i = 0; i < row.size() - 3; i++) {
            bool fourInARow = row[i] == row[i + 1] && row[i + 1] == row[i + 2] && row[i + 2] == row[i + 3] && row[i] != "XXX";
            if (fourInARow) {
                return true;
            }
        }
    }
    return false;
}

/**Returns true if there is a connect4 in the cols, false otherwise*/
bool GameLogic::checkCols() {
    for (int x = 0; x < cols; x++) {
        for (int y = 0; y < rows - 3; y++) {
            bool fourInARow = grid[y][x] == grid[y + 1][x] && grid[y + 1][x] == grid[y + 2][x] &&
                              grid[y + 2][x] == grid[y + 3][x] && grid[y][x] != "XXX";
            if (fourInARow) {
                return true;
            }
        }
    }
    return false;
}


/**Returns true if there is a connect4 in the diagonals, false otherwise*/
bool GameLogic::checkDiagonals() {
    //check ascending diagonals
    for (int x = 0; x < cols - 3; x++) {
        for (int y = 0; y < rows - 3; y++) {
            bool fourInARow = grid[y][x] == grid[y + 1][x + 1] && grid[y + 1][x + 1] == grid[y + 2][x + 2] &&
                              grid[y + 2][x + 2] == grid[y + 3][x + 3] && grid[y][x] != "XXX";
            if (fourInARow) {
                return true;
            }
        }
    }

    //check descending diagonals
    for (int y = 0; y < rows - 3; y++) {
        for (int x = cols - 1; x >= 3; x--) {
            bool fourInARowD = grid[y][x] == grid[y + 1][x - 1] && grid[y + 1][x - 1] == grid[y + 2][x - 2] &&
                               grid[y + 2][x - 2] == grid[y + 3][x - 3] && grid[y + 3][x - 3] != "XXX";
            if (fourInARowD) {
                return true;
            }
        }
    }
    return false;
}

/**Moves the piece left or right during the selection phase of a player's turn
 * @param event -> the keyStroke the player input
 **/
void GameLogic::move(sf::Keyboard::Key event) {
    if (redTurn) {
        if (event == sf::Keyboard::Left) {
            redPosition--;
            if (redPosition < 0) {
                redPosition = cols - 1;
            }
        } else if (event == sf::Keyboard::Right) {
            redPosition++;
            if (redPosition > cols - 1) {
                redPosition = 0;
            }
        }
    } else {
        if (event == sf::Keyboard::Left) {
            yellowPosition--;
            if (yellowPosition < 0) {
                yellowPosition = cols - 1;
            }
        } else if (event == sf::Keyboard::Right) {
            yellowPosition++;
            if (yellowPosition > cols - 1) {
                yellowPosition = 0;
            }
        }
    }
}

