#pragma once

#include <iostream>

class BoardLocation {
public:
    BoardLocation() : m_x(-1), m_y(-1), m_r(-1), m_e(-1){}
    BoardLocation(int x, int y, int r, int e) : m_x(x), m_y(y), m_r(r), m_e(e){}
    BoardLocation(float x, float y, int r, int e) : m_x(abs(x)), m_y(abs(y)), m_r(r), m_e(e) {}

    int getX() const {return m_x;}
    int getY() const {return m_y;}
    int getR() const {return m_r;}
    int getE() const {return m_e;}

    bool exists() const {return m_e;}
    bool rotated() const {return m_r;}

    static int maxWidth;
    static int maxHeight;

    inline bool checkBorders() const { return (m_x < maxWidth) && (m_y < maxHeight); }

    friend std::ostream & operator<< (std::ostream& os, const BoardLocation & b);

private:
    int m_x;
    int m_y;
    int m_r;
    int m_e;
};