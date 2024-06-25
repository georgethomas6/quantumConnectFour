#include <iostream>
#include "Headers/GameLogic.h"


int main(){

    GameLogic logic(7, 6);
    logic.quantumMove(3, 6);
    logic.quantumMove(4, 6);
    logic.quantumMove(4, 6);
    logic.classicalMove(4);
    logic.classicalMove(4);
    logic.printBoard();
    std::cout << "\n";
    logic.measure();
    logic.printBoard();







    return 0;
}