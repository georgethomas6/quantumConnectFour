#include "Headers/GameLogic.h"
#include "Headers/connectFourGraphics.h"
#include "Headers/Game.h"

int main(){
    //Create all the objects needed to play the game
    sf::RenderWindow window(sf::VideoMode(720, 640), "Connect Four");
    connectFourGraphics graphics(7, 6, 720, 640);
    GameLogic logic(7, 6);
    Game game(7, 6);

    //Pass those objects into the play function provided by game class
    game.play(&window, &graphics, &logic);

    return 0;
}