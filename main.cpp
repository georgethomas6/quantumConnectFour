#include <iostream>
#include "Headers/Logic.h"
#include "Headers/cFourGraphics.h"


int main(){

    cFourGraphics graphics(7, 6, 720, 640);
    Logic logic(7, 6);

    graphics.play();


    return 0;
}