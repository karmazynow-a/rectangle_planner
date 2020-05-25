
#include "Board.h"

int getCrossSurface(const Board & b1, const Board & b2){
	// rogi
	int lx = b1.a.x - b2.a.x;
	int ly = b1.a.y - b2.a.y;
	int rx = b1.c.x - b2.c.x;
	int ry = b1.c.y - b2.c.y;

	if ( lx < 0 && ly < 0 && rx > 0 && ry > 0 ){
		// b1 zawarty w b2
		return b1.getSurface();
	}

	if ( lx > 0 && ly > 0 && rx < 0 && ry < 0 ){
		// b2 zawarty w b1
		return b2.getSurface();
	}

	if ( rx < 0 && lx > 0){
		// b2 zachodzi od góry
		return b2.dim_x * ly;
	}
	return 0;
}

std::ostream& operator<<(std::ostream& os, const Board & b){
	os << std::setw(10) << b.dim_x << b.dim_y << b.a.x << b.a.y << b.rotated << std::endl;
	return os;
}

