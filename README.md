# Rectangle planner
Genetic algorithm solving the issue of planning location of small rectangles on one big board.
Small boards should not intersect with each other and be fully inside the restricted area.
The algorithm is looking for a solution with a maximum area of small boards.

## Data
* input - file with dimentions of small boards
* output - surface of small boards, dimensions and their locations

## Compilation and execution
GALib library is required, available [here](http://lancet.mit.edu/ga/).

To compile do:

    mkdir build
    cd build
    cmake ../AG/
    make


To execute do:

    ./AG_proj

Input file `maleplyty.txt` should be in the same directory as executable. As a result, the file `output.txt` will be produced.

To draw the boards do:

    cd draw
    ./draw_result.py

The turtle screen will show up, and the boards will be drawn. The final drawing will be saved to file `board.eps`. Example drawing is available in the documentation.

## Tests
Test for penalties calculation were prepared. To compile and execute them do:

    mkdir build_test
    cd build_test
    cmake ../test/
    make
    ./AG_proj_test


## Technologies
* C++
* GAlib
* python + turtle for drawings
