#include <memory>
#include <string>
#include "Board.h"

#ifndef GAME_H
#define GAME_H


class Game{
    private:

    std::unique_ptr<Board> m_gameBoard;

    bool m_isGameOver = false;
    bool m_isGameWon = false;

    bool parseAndValidateInput(const std::string& input, int& row, int& col, char& command);
    void processMove(int row, int col, char command);
    void checkGameStatus();

public:
    Game(int width,int height,int mines);
    
    void run();

};

#endif // GAME_H