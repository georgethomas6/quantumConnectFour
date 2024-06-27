#include <iostream>
#include "Headers/GameLogic.h"
#include "Headers/cFourGraphics.h"


int main(){

    cFourGraphics graphics(7, 6, 720, 640);
    GameLogic logic(7, 6);
    std::vector<std::vector<std::string>> grid (6, std::vector<std::string> (7, "XXX"));
    logic.quantumMove(2, 3);
    logic.quantumMove(2, 3);
    logic.classicalMove(5);
    logic.measure();
    graphics.drawGrid();
    graphics.drawPieces(logic.getGrid());
    logic.printBoard();

    graphics.drawClassicTurnInProgress(0, logic.getRedTurn());
    graphics.wait();






    return 0;
}