#pragma once

/*******************************************************************************
 * Class represtenting single rectangle board that sould be cut out.
 ******************************************************************************/
class Board {
public:
    Board(const int w,const int h) : width(w), height(h) {}
    Board() : width(-1), height(-1) {}

    /*******************************************************************************
     * Get width of board
     ******************************************************************************/
    inline int getWidth() const { return width; }

    /*******************************************************************************
     * Get height of board
     ******************************************************************************/
    inline int getHeight() const { return height; }

    /*******************************************************************************
     * Get area of board
     ******************************************************************************/
    inline int getArea() const { return height*width; }

private:
    int width;  ///< Width of the board
    int height; ///< Height of the board
};