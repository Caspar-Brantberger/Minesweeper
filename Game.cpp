#include "Game.h"
#include <iostream>
#include <sstream>
#include <cctype>

bool Game::parseAndValidateInput(const std::string& input, int& row, int& col, char& command){

    std::string cleanInput = input;
    command = 'r';

    if(cleanInput.length() >= 2 &&(cleanInput[0]== 'f'|| cleanInput[0] == 'F')){
        command = 'f';

        if(cleanInput.length() >= 3 && cleanInput[1] == ' '){
            cleanInput = cleanInput.substr(2);
        } else {
            cleanInput = cleanInput.substr(1);
        }
    }
    if(cleanInput.length()< 2|| !std::isalpha(cleanInput[0]) || !std::isdigit(cleanInput[1])){
        std::cout << "Ogiltigt format. Använd t.ex. 'a1' eller 'f b2'.\n";
        return false;
    }
    std::string colString = cleanInput.substr(1);
    for(char c: colString){
        if(!std::isdigit(c)){
            std::cout << "Kolumnnummer får endast innehålla siffror.\n";
            return false;
        }
    }
    char rowChar = std::tolower(cleanInput[0]);
    row = rowChar - 'a';

    std::stringstream ss(cleanInput.substr(1));
    int col1Indexed;
    if(!(ss >> col1Indexed)){
        std::cout << "Kunde inte tolka kolumnnummer.\n";
        return false;
    }
    col = col1Indexed - 1; 
    
    int boardHeight = m_gameBoard->getHeight();
    int boardWidth = m_gameBoard->getWidth();   

    if (row < 0 || row >= boardHeight || col < 0 || col >= boardWidth) {
        std::cout << "Koordinaterna (" << rowChar << col1Indexed << ") ligger utanför spelplanen.\n";
        return false;
    }

    return true;

}
void Game::processMove(int row, int col, char command){
    if(!m_gameBoard){
        std::cout <<"Internt fel: Spelbrädet är inte initierat.\n";
        return;
    }
    if(command == 'f'){
        std::cout << "Ruta " << (char)('a' + row) << col + 1 << " flaggades/avflaggades.\n";
    } else if(command == 'r'){
        bool hitMine = m_gameBoard->revealCell(row,col);

        if(hitMine){
            m_isGameOver = true;
            std::cout << "Åh nej! Du avslöjade en mina!\n";
            return;
        }
        checkGameStatus();
    }
}
