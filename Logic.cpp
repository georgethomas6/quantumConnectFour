#include "Headers/Logic.h"

Logic::Logic(int columns, int rows) {
    this->columns = columns;
    this->rows = rows;
    turnsPlayed = 0;
    yellowPosition = columns / 2;
    redPosition = columns / 2;
    redTurn = true;
    cMoveInProgress = true;
    quantumMovesPlayed = 0;
    this->grid = std::vector<std::vector<std::string>>(rows + 2, std::vector<std::string>(columns, "XXX"));
    std::vector<std::vector<std::string>> turns;
    std::vector<std::string> moves;
}

/**@return redPosition*/
int Logic::getRedPosition() {
    return redPosition;
}

/**@return yellowPosition*/
int Logic::getYellowPosition() {
    return yellowPosition;
}

/**Moves red's position by dx
 * @param dx -> value to increment/decrement red's position*/
void Logic::moveRed(int dx) {
    redPosition = redPosition + dx;
    //makes the piece warp around the grid
    if (redPosition > columns - 1) {
        redPosition = 0;
    } else if (redPosition < 0) {
        redPosition = columns - 1;
    }
}

/**Moves yellow's position by dx
 * @param dx -> value to increment/decrement yellow's position*/
void Logic::moveYellow(int dx) {
    yellowPosition = yellowPosition + dx;
    //makes the piece warp around the grid
    if (yellowPosition > columns - 1) {
        yellowPosition = 0;
    } else if (yellowPosition < 0) {
        yellowPosition = columns - 1;
    }
}

/**@return redTurn*/
bool Logic::getRedTurn() {
    return redTurn;
}

/**@return quantumMovesPlayed*/
int Logic::getQuantumMovesPlayed() {
    return quantumMovesPlayed;
}

/**@return turnsPlayed*/
int Logic::getTurnsPlayed() {
    return turnsPlayed;
}

/**Switches the value of the redTurn boolean*/
void Logic::changeTurn() {
    redTurn = !redTurn;
}

/**@return grid*/
std::vector<std::vector<std::string>> Logic::getGrid() {
    return grid;
}

/**@return cMoveInProgress*/
bool Logic::getCMoveInProgress() {
    return cMoveInProgress;
}

/**@return return true if the game is over, false otherwise*/
bool Logic::winner() {
    int cnt = 0;
    for (std::vector<std::string> row: grid) {
        for (std::string entry: row) {
            if (entry == "XXX") {
                cnt++;
            }
        }
    }
    return cnt == 0 || checkCols() || checkRows() || checkDiagonals();
}

/**@return true if there is a group in one of the rows, false otherwise*/
bool Logic::checkRows() {
    for (std::vector<std::string> &row: grid) {
        //check every four positions in the row for four of a kind
        for (int i = 0; i < row.size() - 3; i++) {
            bool fourInARow =
                    row[i] == row[i + 1]
                    && row[i] == row[i + 2]
                    && row[i] == row[i + 3]
                    && (row[i] == "RRR" || row[i] == "YYY");
            if (fourInARow) {
                return true;
            }
        }
    }
    return false;
}

/**@return true if there is a group in one of the columns, false otherwise*/
bool Logic::checkCols() {
    for (int y = 0; y < grid.size() - 3; y++) {
        for (int x = 0; x < grid[y].size(); x++) {
            bool fourInARow =
                    grid[y][x] == grid[y + 1][x]
                    && grid[y][x] == grid[y + 1][x]
                    && grid[y][x] == grid[y + 2][x]
                    && grid[y][x] == grid[y + 3][x]
                    && (grid[y][x] == "RRR" || grid[y][x] == "YYY");
            if (fourInARow) {
                return true;
            }
        }
    }
    return false;
}

/**@return true if there is a group in one of the diagonals, false otherwise*/
bool Logic::checkDiagonals() {

    //check ascending diagonals
    for (int y = grid.size() - 1; y > 4; y--) {
        for (int x = 0; x < grid[y].size(); x++) {
            bool fourInARow =
                    grid[y][x] == grid[y - 1][x + 1] &&
                    grid[y][x] == grid[y - 2][x + 2] &&
                    grid[y][x] == grid[y - 3][x + 3] && (
                            grid[y][x] == "YYY" || grid[y][x] == "RRR");
            if (fourInARow) {
                return true;
            }
        }
    }

    //check descending diagonals
    for (int y = grid.size() - 1; y > 3; y--) {
        for (int x = grid[y].size() - 1; x > 2; x--) {
            bool fourInARow =
                    grid[y][x] == grid[y - 1][x - 1] &&
                    grid[y][x] == grid[y - 2][x - 2] &&
                    grid[y][x] == grid[y - 3][x - 3] && (
                            grid[y][x] == "RRR" || grid[y][x] == "YYY");
            if (fourInARow) {
                return true;
            }
        }
    }
    return false;
}

/**Resets the positions of both pieces to columns / 2 i.e. the center*/
void Logic::resetPositions() {
    redPosition = columns / 2;
    yellowPosition = columns / 2;
}

/**Attempts to place the input string in the input col on the grid
 * @param pos -> column at which player is trying to place piece
 * @return -1 if column is full, a positive integer of there is a depth availible
 * */
int Logic::tryPlace(int pos) {
    int depth = 0;
    for (int i = 0; i < rows + 2; i++) {
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

/**Switches the value of cMoveInProgress*/
void Logic::changeCMoveInProgress() {
    cMoveInProgress = !cMoveInProgress;
}

/**Makes a classical move in the column corresponding to the parameter
 * @param position -> column piece is to be placed in
 * @return true if move succeeded, false otherwise*/
bool Logic::classicalMove(int column) {
    int depth = tryPlace(column);
    //depth greater than 1 because there are two phantom rows for quantum pieces to appear above board prior to measurement
    bool columnNotFull = depth > 1;
    if (columnNotFull) {
        //add move to turns if it was allowed
        std::vector<int> move;
        move.push_back(column);
        turns.push_back(move);
        turnsPlayed++;
        return true;
    }
    return false;
}

/**Makes half of a quantum move in the column corresponding to the parameter
 * @param position -> column piece is to be placed in
 * @return true if move succeeded, false otherwise*/
bool Logic::halfQuantumMove(int column) {
    int depth = tryPlace(column);
    //depth > -1 limits the number of quantum moves above the board to 2
    //grid[2][column] occupied makes sure that if there is a full piece in the top column a player cannot play a quantum move above it
    bool columnNotFull = depth > -1 && grid[2][column] != "RRR" && grid[2][column] != "YYY";
    if (columnNotFull) {
        quantumMoves.push_back(column);
        quantumMovesPlayed++;
        //if two quantum moves have been played call quantumMove organizer function
        if (quantumMovesPlayed % 2 == 0 && quantumMovesPlayed != 0) {
            quantumMoveToTurns();
            turnsPlayed++;
        }
        return true;
    }
    return false;
}

/**Takes the vector of quantum moves made and pairs each quantum move together to be added to Turn queue,
 * after it prepares them to be added it clears the quantumMoves vector*/
void Logic::quantumMoveToTurns() {
    for (int i = 0; i < quantumMoves.size() - 1; i += 2) {
        std::vector<int> turn;
        turn.push_back(quantumMoves[i]);
        turn.push_back(quantumMoves[i + 1]);
        turns.push_back(turn);
    }
    quantumMoves.clear();
}

/**Calls quantumMoveToTurns, then loops through Turns making the corresponding changes to grid for each turn played
 * one turn is when one color plays a move*/
void Logic::updateBoard() {
    //clear the board
    grid = std::vector<std::vector<std::string>>(rows + 2, std::vector<std::string>(columns, "XXX"));
    //turn will be modded by 2 to determine if red or yellow turn
    int turnCounter = 0;
    for (std::vector<int> &turn: turns) {
        //if turn.size = 1 then it is a classical move, so only one placement on the board
        if (turn.size() == 1) {
            if (tryPlace(turn[0]) > 1) {
                if (turnCounter % 2 == 0) {
                    grid[tryPlace(turn[0])][turn[0]] = "RRR";
                    turnCounter++;
                } else {
                    grid[tryPlace(turn[0])][turn[0]] = "YYY";
                    turnCounter++;
                }
            }
        } else {
            //we need to play two moves because a quantum move consists of two placements on the board
            //check for valid placement
            bool columnNotFull1 = tryPlace(turn[0]) > -1;
            bool columnNotFull2 = tryPlace(turn[0] > -1);
            bool notFull = columnNotFull1 && columnNotFull2;
            if (turnCounter % 2 == 0 && notFull) {
                grid[tryPlace(turn[0])][turn[0]] = "RXX";
                grid[tryPlace(turn[1])][turn[1]] = "RXX";
                turnCounter++;
            } else if (turnCounter % 2 == 1 && notFull) {
                grid[tryPlace(turn[0])][turn[0]] = "YXX";
                grid[tryPlace(turn[1])][turn[1]] = "YXX";
                turnCounter++;
            }
        }
    }

    //handles a quantum turn that is half completed
    for (int quantumMove: quantumMoves) {
        bool notOutOfBounds = tryPlace(quantumMove) != -1;
        if (notOutOfBounds) {
            //we need to play two moves because a quantum move consists of two placements on the board
            if (turnCounter % 2 == 0) {
                grid[tryPlace(quantumMove)][quantumMove] = "RXX";
                turnCounter++;
            } else if (turnCounter % 2 == 1) {
                grid[tryPlace(quantumMove)][quantumMove] = "YXX";
                turnCounter++;
            }
        }
    }
}


/**This function chooses a state for the quantum quantumMoves made*/
void Logic::measure() {
    for (std::vector<int> &turn: turns) {
        //have to specify pass by value or the changes won't hold
        if (turn.size() != 1) {
            // Choose a random mean between 1 and 6
            std::random_device r;
            std::default_random_engine e1(r());
            std::uniform_int_distribution<int> uniform_dist(1, 6);
            int choice = uniform_dist(e1) % 2;
            if (choice == 1) {
                //if chose the first number delete the second number
                turn.pop_back();
            } else {
                //change first element to the value of the second element before deleting the second element
                turn[0] = turn[1];
                turn.pop_back();
            }
        }
    }
    updateBoard();
}

/**Prints the board, used in debugging*/
void Logic::printBoard() {

    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[y].size(); x++) {

            std::cout << grid[y][x] << " ";
        }
        std::cout << "\n";
    }
}