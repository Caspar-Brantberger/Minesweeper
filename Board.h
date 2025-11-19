#include <vector>
#include "Cell.h"

class Board {
private:
    std::vector<std::vector<Cell>> m_grid;

    const int m_width;
    const int m_height;
    const int m_totalMines;

    public:

    Board(int width,int height,int mines);

    void placeMines();
    void calculateNeighborCounts();
    void displayBoard() const;

    bool revealCell(int x,int y);
    void toggleFlag(int x,int y);

    bool checkWinConditions() const;

    int getWidth() const {return m_width;}
    int getHeight() const {return m_height;}

};