#ifndef CELL_H
#define CELL_H
class Cell {
private:
    bool m_hasMine = false;
    bool m_isRevealed = false;
    bool m_isFlagged = false;
    int m_neighborMines = 0;

    public:
    Cell() = default;

    bool hasMine() const {return m_hasMine;}
    bool isRevealed() const {return m_isRevealed;}
    bool isFlagged() const {return m_isFlagged;}
    int neighborMines() const {return m_neighborMines;}

    void setMine(){m_hasMine = true;}

    void neighborMines(int count){m_neighborMines = count;}
    void reveal(){m_isRevealed = true;}
    void toggleFlag(){m_isFlagged = !m_isFlagged;}

    

};
#endif // CELL_H