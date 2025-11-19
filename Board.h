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

    void revealCell(int x,int y);

    int getWidth() const {return m_width;}
    int getHeight() const {return m_height;}

};