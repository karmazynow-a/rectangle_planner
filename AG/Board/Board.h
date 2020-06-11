#pragma once

/*******************************************************************************
 * Class represtenting single rectangle board that sould be cut out.
 ******************************************************************************/
class Board {
public:
    Board(const int w,const int h) : width(w), height(h) {}
    Board() : width(-1), height(-1) {}

    inline int getWidth() const { return width; }
    inline int getHeight() const { return height; }
    inline int getArea() const { return height*width; }
    inline bool checkBorders() const { return (width < maxWidth) && (height < maxHeight); }

    static int maxWidth;
    static int maxHeight;

private:
    int width;  ///< Width of the board
    int height; ///< Height of the board
};