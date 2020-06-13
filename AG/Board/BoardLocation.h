#pragma once

#include <iostream>

/*******************************************************************************
 * Class representing location of board.
 ******************************************************************************/
class BoardLocation {
public:
    BoardLocation() : m_x(-1), m_y(-1), m_r(-1), m_e(-1){}
    BoardLocation(int x, int y, int r, int e) : m_x(x), m_y(y), m_r(r), m_e(e){}

    /*******************************************************************************
     * Get x coord for board's upper left corner
     ******************************************************************************/
    int getX() const {return m_x;}

    /*******************************************************************************
     * Get y coord for board's upper left corner
     ******************************************************************************/
    int getY() const {return m_y;}

    /*******************************************************************************
     * Get value if board is rotated
     ******************************************************************************/
    int getR() const {return m_r;}

    /*******************************************************************************
     * Get value if board will be cut out on big board
     ******************************************************************************/
    int getE() const {return m_e;}

    /*******************************************************************************
     * Check if board exist
     ******************************************************************************/
    bool exists() const {return m_e;}

    /*******************************************************************************
     * Check if board is rotated
     ******************************************************************************/
    bool rotated() const {return m_r;}

    /*******************************************************************************
     * Check if upper left corner of board is within restricted area
     ******************************************************************************/
    inline bool checkBorders() const { return (m_x < maxWidth) && (m_y < maxHeight); }

    /*******************************************************************************
     * Pretty printout of board parameters
     ******************************************************************************/
    friend std::ostream & operator<< (std::ostream& os, const BoardLocation & b);

    static int maxWidth;    ///< max width of board - tha same as width of restricted area
    static int maxHeight;   ///< max height of board - tha same as height of restricted area

private:
    int m_x;
    int m_y;
    int m_r;
    int m_e;
};