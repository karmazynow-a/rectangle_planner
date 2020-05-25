#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>

struct Point {
	int x;
	int y;
};

struct Board {
	Point a, b, c, d;
	int dim_x, dim_y;
	bool rotated;

	int getSurface() const {return dim_x * dim_y;}
	bool isInside(Point & p) {
		return (a.x < p.x) && (c.x > p.x) && (a.y < p.y) && (c.y > p.y);
	}
	friend std::ostream& operator<<(std::ostream& o, const Board & board);
};

// print board's data
std::ostream& operator<<(std::ostream&, const Board&);

int getCrossSurface(const Board & b1, const Board & b2);
