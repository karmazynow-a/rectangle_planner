/** 
*   Test for objective penalties from AGtools
*   @author Aleksandra Poreba 
*/

#include <iostream>
#include <cmath>
#include <cassert>

#include "../AG/Board/Board.h"
#include "../AG/Board/BoardLocation.h"
#include "../AG/AGtools/ObjectivePenalty.h"

// messages for failed asserts
// https://en.cppreference.com/w/cpp/error/assert
#define assertm(exp, msg) assert(((void)msg, exp))

void test(){

    ObjectivePenalty o;

    Board b1 = Board(400, 200);
    Board b2 = Board(50, 100);

    // test outside penalty
    std::cout << "Test penalty for being outside the board..." << std::endl;
    BoardLocation b1Loc = BoardLocation(2750, 10, 0, 1);

    assertm( o.outsidePenalty(b1, b1Loc) != 0, "test 1" );

    b1Loc = BoardLocation(10, 2000, 0, 1);
    assertm( o.outsidePenalty(b1, b1Loc) != 0, "test 2" );

    b1Loc = BoardLocation(10, 2000, 1, 1);
    assertm( o.outsidePenalty(b1, b1Loc) != 0, "test 3" );

    b1Loc = BoardLocation(10, 2000, 1, 0);
    assertm( o.outsidePenalty(b1, b1Loc) == 0, "test 4" );

    std::cout << "passed." << std::endl;
    std::cout  << std::endl << "Test penalty for intersection..." << std::endl;

    b1Loc = BoardLocation(100, 100, 0, 1);
    BoardLocation b2Loc = BoardLocation(1000, 1000, 0, 1);

    std::cout  << " not intersected..." << std::endl;
    assertm(o.calculateIntersection(b1, b1Loc, b2, b2Loc) == 0, "test 5a");
    assertm(o.calculateIntersection(b2, b2Loc, b1, b1Loc) == 0, "test 5b");

    std::cout  << " one is inside other one..." << std::endl;
    b2Loc = BoardLocation(110, 110, 0, 1);
    assertm( o.calculateIntersection(b1, b1Loc, b2, b2Loc) == b2.getArea(), "test 6a");
    assertm( o.calculateIntersection(b2, b2Loc, b1, b1Loc) == b2.getArea(), "test 6b");

    std::cout  << " side intersection..." << std::endl;
    b2Loc = BoardLocation(90, 110, 0, 1); 
    assertm( o.calculateIntersection(b1, b1Loc, b2, b2Loc) == 4000, "test 7a");
    assertm( o.calculateIntersection(b2, b2Loc, b1, b1Loc) == 4000, "test 7b");

    b2Loc = BoardLocation(480, 110, 0, 1); 
    assertm( o.calculateIntersection(b1, b1Loc, b2, b2Loc) == 2000, "test 8a");
    assertm( o.calculateIntersection(b2, b2Loc, b1, b1Loc) == 2000, "test 8b");

    b2Loc = BoardLocation(110, 80, 0, 1); 
    assertm( o.calculateIntersection(b1, b1Loc, b2, b2Loc) == 4000, "test 9a");
    assertm( o.calculateIntersection(b2, b2Loc, b1, b1Loc)  == 4000, "test 9b");

    b2Loc = BoardLocation(110, 280, 0, 1); 
    assertm( o.calculateIntersection(b1, b1Loc, b2, b2Loc) == 1000, "test 10a");
    assertm( o.calculateIntersection(b2, b2Loc, b1, b1Loc) == 1000, "test 10b");

    std::cout << " corner intersection..." << std::endl;

    b2Loc = BoardLocation(90, 90, 0, 1); 
    assertm( o.calculateIntersection(b1, b1Loc, b2, b2Loc) == 3600, "test 11a");
    assertm( o.calculateIntersection(b2, b2Loc, b1, b1Loc) == 3600, "test 11b");

    b2Loc = BoardLocation(480, 280, 0, 1); 
    assertm( o.calculateIntersection(b1, b1Loc, b2, b2Loc) == 400, "test 12a");
    assertm( o.calculateIntersection(b2, b2Loc, b1, b1Loc) == 400, "test 12b");

    b2Loc = BoardLocation(490, 90, 0, 1); 
    assertm( o.calculateIntersection(b1, b1Loc, b2, b2Loc) == 900, "test 13a");
    assertm( o.calculateIntersection(b2, b2Loc, b1, b1Loc) == 900, "test 13b");

    b2Loc = BoardLocation(90, 280, 0, 1); 
    assertm( o.calculateIntersection(b1, b1Loc, b2, b2Loc) == 800, "test 14a");
    assertm( o.calculateIntersection(b2, b2Loc, b1, b1Loc) == 800, "test 14b");

    std::cout << "passed." << std::endl;

    std::cout  << std::endl << "Other tests..." << std::endl;

    b2Loc = BoardLocation(100, 100, 0, 1); 
    assertm( o.calculateIntersection(b1, b1Loc, b2, b2Loc) == b2.getArea()*2, "test 15a");
    assertm( o.calculateIntersection(b2, b2Loc, b1, b1Loc) == b2.getArea()*2, "test 15b");

    b2Loc = BoardLocation(100, 100, 0, 1); 
    b2 = Board(200, 500);
    assertm( o.calculateIntersection(b1, b1Loc, b2, b2Loc) == 40000, "test 16a");
    assertm( o.calculateIntersection(b2, b2Loc, b1, b1Loc) == 40000, "test 16b");

    b2 = Board(123, 678);
    b2Loc = BoardLocation(2757, 1576, 0, 1); 
    assertm( o.outsidePenalty(b2, b2Loc) > 0, "test 17");

    b1 = Board(1400, 500);
    b1Loc = BoardLocation(1920, 1238, 1, 1); 
    b2 = Board(900, 900);
    b2Loc = BoardLocation(1221, 723, 1, 1); 
    assertm( o.calculateIntersection(b1, b1Loc, b2, b2Loc) == 77385, "test 18a");
    assertm( o.calculateIntersection(b2, b2Loc, b1, b1Loc) == 77385, "test 18b");


    b1 = Board(900, 900);
    b1Loc = BoardLocation(2402, 1070, 0, 1);

    assertm( o.outsidePenalty(b1, b1Loc) > 0, "test 19");

    std::cout << "passed." << std::endl;
}

int main(void){
    test();
    return 0;
}