#include "Game.h"
#include <iostream>
#include <sstream>
#include <cctype>

Game::Game(int width, int height, int mines) 
    : m_gameBoard(std::make_unique<Board>(width, height, mines)) 
{
    std::cout << "Nytt Minröj-spel skapat.\n";
    
    if (m_gameBoard) {
        m_gameBoard->placeMines();
        m_gameBoard->calculateNeighborCounts();
    }
}

void Game::run(){
    std::string input;
    
    while (!m_isGameOver && !m_isGameWon) {
        
        m_gameBoard->displayBoard(); 
        
        int row, col;
        char command;
        
        std::cout << "\nAnge drag (t.ex. 'a1' eller 'f b2'): ";
        std::getline(std::cin, input);
    
        if (parseAndValidateInput(input, row, col, command)) {

            processMove(row, col, command);
        } else {
    
        }
    }
    
    if (m_isGameOver || m_isGameWon) {
        m_gameBoard->displayBoard();
        if (m_isGameWon) {
            std::cout << "Grattis, Kingen! Du vann! Jävligt smutt!\n";
        } else if (m_isGameOver) {
            std::cout << "BOOM! Du avslöjade en mina. Game Over, Gud.\n";
        }
    }
}


bool Game::parseAndValidateInput(const std::string& input, int& row, int& col, char& command){

    std::string cleanInput = input;
    command = 'r';

    if (input.length() >= 3 && (input[0] == 'f' || input[0] == 'F') && input[1] == ' ') {
        command = 'f';

        cleanInput = input.substr(2); 
    }

    if(cleanInput.length() < 2 || !std::isalpha(cleanInput[0]) || !std::isdigit(cleanInput[1])){
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
        m_gameBoard->toggleFlag(row,col);
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
void Game:: checkGameStatus(){
    if (m_isGameOver) return;

    if(m_gameBoard -> checkWinCondition()){
        m_isGameWon = true;
    }

}
