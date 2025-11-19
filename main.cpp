#include "Game.h"
#include <iostream>

int main(){
    const int BOARD_WIDTH = 6;
    const int BOARD_HEIGHT = 6;
    const int TOTAL_MINES = 5;

    std::cout << "Välkommen till Minröj! \n";
    std::cout << "Spelet startar med" + BOARD_WIDTH << "x" 
    << BOARD_HEIGHT << "rutor och" << TOTAL_MINES <<" minor.\n";

    try{
    Game minesweeper(BOARD_HEIGHT,BOARD_WIDTH,TOTAL_MINES);

    minesweeper.run();
    }catch(const std::exception & e){
    std::cerr << "Ett fel uppstod vid spelets initiering: " << e.what() << '\n';
        return 1;

    }
    return 0;
}