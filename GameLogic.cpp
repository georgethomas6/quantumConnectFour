#include "Headers/GameLogic.h"
#include <iostream>
#include <random>
#include <functional>


GameLogic::GameLogic(int cols, int rows) {
    redTurn = true;
    yellowPosition = cols / 2;
    redPosition = cols / 2;
    this->cols = cols;
    this->rows = rows;
    std::vector<std::vector<int>> moves;
    grid = std::vector<std::vector<std::string>>(rows, std::vector<std::string>(cols, "XXX"));
}

/**Returns red's position*/
int GameLogic::getRedPos() {
    return redPosition;
}

/**Returns yellow's position*/
int GameLogic::getYelPos() {
    return yellowPosition;
}

bool GameLogic::getRedTurn() {
    return redTurn;
}

void GameLogic::changeTurn() {
    redTurn = !redTurn;
}

/**Returns the grid which is a vector containing vectors consisting of strings*/
std::vector<std::vector<std::string>> GameLogic::getGrid() {
    return grid;
}


/**Returns Red if red won the game, Yel if yellow won the game, stalemate if neither won, and XXX if game is still in progress*/
std::string GameLogic::winner() {
    int cnt = 0;
    for (std::vector<std::string> row: grid) {
        for (std::string entry: row) {
            if (entry == "XXX") {
                cnt++;
            }
        }
    }

    if (cnt == 0) {
        return "stalemate";
    } else if (redTurn && (checkCols() || checkRows() || checkDiagonals())) {
        return "Yel";
    } else if (!redTurn && (checkCols() || checkRows() || checkDiagonals())) {
        return "Red";
    }

    return "XXX";
}

/**Returns true if there is a connect4 in the rows, false otherwise*/
bool GameLogic::checkRows() {
    for (std::vector<std::string> row: grid) {
        //check every four positions in the row for four of a kind
        for (int i = 0; i < row.size() - 3; i++) {
            bool fourInARow =
                    row[i] == row[i + 1] && row[i + 1] == row[i + 2] && row[i + 2] == row[i + 3] && row[i] != "XXX";
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


/**Attempts to place the input string in the input col on the grid
 * --if it can be placed it returns the depth
 * --if not it returns -1
 * @param pos -> column at which player is trying to place piece
 * */
int GameLogic::tryPlace(int pos) {
    int depth = 0;
    for (int i = 0; i < rows; i++) {
        bool empty = grid[i][pos] == "XXX";
        if (empty) {
            depth++;
        } else {
            break;
        }
    }
    depth--;

    return depth;
}

/**Returns true and switches turn if move succeeded; false and does not switch turn otherwise
 * @param positionOne -> column of first possibility
 * @param positionTwo -> column of second possibility*/
bool GameLogic::quantumMove(int positionOne, int positionTwo) {
    //Check for valid placements
    bool firstPlacementGood = tryPlace(positionOne) != -1;
    bool secondPlacementGood = tryPlace(positionTwo) != -1;

    //if good placements add move
    if (firstPlacementGood && secondPlacementGood) {
        std::vector<int> move;
        move.push_back(positionOne);
        move.push_back(positionTwo);
        moves.push_back(move);
        updateBoard();
        changeTurn();
        return true;
    }

    return false;
}

/**This function chooses a state for the quantum moves made*/
void GameLogic::measure() {
    //have to specify pass by value or the changes won't hold
    for (std::vector<int> &move : moves){
        std::random_device r;

        // Choose a random mean between 1 and 6
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> uniform_dist(1, 6);
        int choice = uniform_dist(e1) % 2;
        if (move.size() != 1){
            if (choice == 1){
                //if chose the first number delete the second number
            move.pop_back();
            } else {
                //change first element to the value of the second element before deleting the second element
                move[0] = move[1];
                move.pop_back();
            }
        }
    }
    updateBoard();
}

/**Updates the board with current moves list, handles turn switching*/
void GameLogic::updateBoard() {
    grid = std::vector<std::vector<std::string>>(rows, std::vector<std::string>(cols, "XXX"));
    //turn will be modded by 2 to determine if red or yellow turn
    int turn = 0;
    for (std::vector<int> move: moves) {
        //if move.size is less than three then it is a classical move so put RRR or YYY
        if (move.size() == 1) {
            if (turn % 2 == 0) {
                grid[tryPlace(move[0])][move[0]] = "RRR";
                turn++;
            } else {
                grid[tryPlace(move[0])][move[0]] = "YYY";
                turn++;
            }
        } else {
            //NOTE THIS IS HARDCODED IF WANT MORE POSSIBILITIES FOR QUANTUM MOVES WILL HAVE TO GET MORE COMPLICATED
            if (turn % 2 == 0) {
                grid[tryPlace(move[0])][move[0]] = "RXX";
                grid[tryPlace(move[1])][move[1]] = "RXX";
                turn++;
            } else if (turn % 2 == 1) {
                grid[tryPlace(move[0])][move[0]] = "YXX";
                grid[tryPlace(move[1])][move[1]] = "YXX";
                turn++;
            }
        }
    }
}

/**Prints the board on the terminal*/
void GameLogic::printBoard() {
    for (const std::vector<std::string> &row: grid) {
        for (const std::string &entry: row) {
            if (entry.size() < 2) {
                std::cout << entry << " ";
            } else {
                std::cout << entry << " ";
            }
        }
        std::cout << "\n";
    }
}

/**Returns true if the move succeed and switches turn, false otherwise and does not switch turn
 * @param position -> column for the classical move to occur in*/
bool GameLogic::classicalMove(int position) {
    bool goodPlacement = tryPlace(position);
    if (goodPlacement) {
        //create move to add to moves list
        std::vector<int> move;
        //update moves
        move.push_back(position);
        moves.push_back(move);
        //update board
        updateBoard();
        changeTurn();
        return true;
    }
    return false;
}




