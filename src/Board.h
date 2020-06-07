#pragma once

class Board {
public:
    Board(const int w,const int h) : width(w), height(h) {}
    Board() : width(-1), height(-1) {}

    inline int getWidth() const { return width; }
    inline int getHeight() const { return height; }
    inline int getArea() const { return height*width; }

private:
    int width;
    int height;
};