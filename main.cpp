#include <iostream>
#include "Headers/Logic.h"
#include "Headers/cFourGraphics.h"


int main(){

    cFourGraphics graphics(7, 6, 720, 640);
    Logic logic(7, 6);
    for (int i = 0; i < 4; i++){
        logic.classicalMove(3);
        logic.classicalMove(4);
    }

    logic.updateBoard();
    logic.printBoard();
    logic.measure();


    logic.updateBoard();

    std::cout << logic.winner() << " \n";
    logic.printBoard();







    return 0;
}