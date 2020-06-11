#!/usr/bin/env python
# script for drawing algorithm result

import argparse
from math import ceil, floor
import random
import warnings

# drawing shapes
import turtle as t

# save turtle to file
import Tkinter as tk

parser = argparse.ArgumentParser(description = 
	'Draw layout of small boards on big board.')
parser.add_argument('-f', '--file', metavar='FILE', type=str, nargs=1, 
	default=['../build/output.txt'], help='name of input file')
parser.add_argument('-s', '--scale', metavar='SC', type=float, nargs=1, 
	default=[0.25], help='scale of printout')

args = parser.parse_args()

# scale of printout
scale = args.scale[0]

class Board:
    def __init__(self, idx, width, height, x, y, rotated):
        self.idx = idx
        self.width = floor(width*scale)
        self.height = floor(height*scale)
        self.x = floor(x*scale)
        self.y = floor(y*scale)
        self.rotated = rotated

    def draw(self, turtle, color):
        if self.x < 0 or self.y < 0:
            print("Board %d will not be cut" % self.idx)
            return

        print("Cutting board %d" % self.idx)

        turtle.penup()
        turtle.setpos(self.x, self.y)
        turtle.color('black', color)
        turtle.pendown()
        turtle.begin_fill()

        edges = [self.height, self.width, self.height, self.width] \
            if self.rotated \
            else [self.width, self.height, self.width, self.height]

        print("Position (%d, %d) width %d height %d" % (self.x/scale, self.y/scale, edges[0]/scale, edges[1]/scale))

        for edge in edges:
            turtle.forward(edge)
            turtle.left(90)

        turtle.end_fill()

def main():
    fileName = args.file[0]
    with open(fileName, 'r') as file:
        total_surface = file.readline()
        print("Total surface of boards is %s" % total_surface)

        WIDTH, HEIGHT = ceil((2800)*scale), ceil((2070)*scale)

        turtle = t.Turtle()
        turtle.hideturtle()
        turtle.speed(0)
        turtle.penup()

        turtle_screen = turtle.getscreen()
        turtle_screen.setup(width = WIDTH + 50, height = HEIGHT + 50, startx = None, starty = None)
        turtle_screen.setworldcoordinates(llx = 0, lly = HEIGHT + 10, urx = WIDTH + 10, ury = 0)
        
        color_list = [
            '#c77373',
	        '#b1e369',
	        '#329f7b',
	        '#d6b474',
	        '#926a6a'
        ]

        # draw board
        turtle.penup()
        turtle.setpos(0, 0)
        turtle.color('black', '#dbb4a0')
        turtle.pendown()
        turtle.begin_fill()
        edges = [ WIDTH, HEIGHT, WIDTH, HEIGHT]
        for edge in edges:
            turtle.forward(edge)
            turtle.left(90)

        turtle.end_fill()

        idx = 1;
        for line in file.readlines():
            line_split = line.split()
            if len(line_split) == 5:
                [w, h, x, y, r] = map(int, line_split)
                b = Board(idx, w, h, x, y, r)
                color = random.choice(color_list)
                b.draw(turtle, color)
                turtle_screen.update()
                idx = idx + 1

        #turtle_screen.tracer(True)
        turtle_screen.getcanvas().postscript(file="board.eps", colormode='color')
        turtle_screen.exitonclick()
        #turtle.done()


if __name__ == '__main__':
    main()
