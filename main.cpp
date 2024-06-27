#include <iostream>
#include "Headers/GameLogic.h"
#include "Headers/cFourGraphics.h"


int main(){

    cFourGraphics graphics(7, 6, 720, 640);
    GameLogic logic(7, 6);
    graphics.getLogic().quantumMove(2,3);

    graphics.getLogic().printBoard();
    graphics.drawClassicTurnInProgress();
    graphics.play();






    return 0;
}