#include "Board.h"
#include "Cell.h"
#include <random>
#include <algorithm>
#include <iostream>

void Board::placeMines() {
    std::random_device rd;
    std::mt19937 generator(rd()); 

    std::vector<std::pair<int, int>> allCoordinates;
    for (int r = 0; r < m_height; ++r) {
        for (int c = 0; c < m_width; ++c) {
            allCoordinates.push_back({r, c});
        }
    }

    std::shuffle(allCoordinates.begin(), allCoordinates.end(), generator);

    for (int i = 0; i < m_totalMines; ++i) {
        int r = allCoordinates[i].first;
        int c = allCoordinates[i].second;
        
        m_grid[r][c].setMine(); 
    }
}
void Board::displayBoard() const {
    std::cout << "\n  ";
    for (int c = 0; c < m_width; ++c) {
        std::cout << " " << c + 1;
    }
    std::cout << " \n";

    for (int r = 0; r < m_height; ++r) {
        
        std::cout << "  +";
        for (int c = 0; c < m_width; ++c) {
            std::cout << "---";
        }
        std::cout << "+\n";
        
        std::cout << (char)('a' + r) << " |"; 

        for (int c = 0; c < m_width; ++c) {
            char cellContent = ' '; 
            const Cell& currentCell = m_grid[r][c];
            
            if (currentCell.isFlagged() && !currentCell.isRevealed()) {
                cellContent = 'F'; 
            } else if (currentCell.isRevealed()) {
                if (currentCell.hasMine()) {
                    cellContent = '*'; 
                } else if (currentCell.neighborMines() > 0) {
                    cellContent = (char)('0' + currentCell.neighborMines());
                }
            }
            
            std::cout << " " << cellContent << "|";
        }
        std::cout << "\n";
    }
    
    std::cout << "  +";
    for (int c = 0; c < m_width; ++c) {
        std::cout << "---";
    }
    std::cout << "+\n";
}



void Board::calculateNeighborCounts(){
    for(int r = 0; r < m_height; ++r){
        for(int c = 0; c < m_width; ++c){
            if(m_grid[r][c].hasMine()){
                continue;
            }
            int mineCount = 0;

            for(int i = -1; i <= 1; ++i){
                for(int j = -1; j <= 1; ++j){
                    if(i==0 && j == 0) continue;
                    
                    int neighborR = r + i;
                    int neighborC = c + j;

                    if(neighborR >= 0 && neighborR < m_height &&
                    neighborC >= 0 && neighborC < m_width)
                    {
                        if(m_grid[neighborR][neighborC].hasMine()){ 
                            mineCount++;
                        }
                    } 

                }
            } 
            m_grid[r][c].neighborMines(mineCount);
        }
    }
}
void Board::toggleFlag(int row, int col) {
    m_grid[row][col].toggleFlag(); 
}
bool Board::revealCell(int r,int c){
    if (r < 0|| r >= m_height || c < 0 || c >= m_width) {
        return false;
    }
    Cell& currentCell = m_grid[r][c];

    if(currentCell.isRevealed() || currentCell.isFlagged()){
        return false;
    }
    currentCell.reveal();

    if (currentCell.hasMine()) {
        return true; 
    }

    if (currentCell.neighborMines() > 0) {
        return false; 
    }


    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue; 

            revealCell(r + i, c + j);
        }
    }
    
    return false;

}
