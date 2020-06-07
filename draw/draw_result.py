#!/usr/bin/env python
# script for drawing algorithm result

import argparse
import numpy as np
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
        self.width = width*scale
        self.height = height*scale
        self.x = x*scale
        self.y = y*scale
        self.rotated = rotated

    def draw(self, turtle, color):
        if self.x == -1 or self.y == -1:
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

        print("Position (%d, %d) width %d height %d" % (self.x, self.y, edges[0], edges[1]))

        for edge in edges:
            turtle.forward(edge)
            turtle.left(90)

        turtle.end_fill()

def main():
    fileName = args.file[0]
    with open(fileName, 'r') as file:
        total_surface = file.readline()
        print("Total surface of boards is %s" % total_surface)

        WIDTH, HEIGHT = 2800*scale, 2070*scale
        print("Screen has size %d %d" % (WIDTH, HEIGHT))

        turtle = t.Turtle()
        turtle.hideturtle()
        turtle.speed(0)
        turtle.penup()

        turtle_screen = t.Screen()
        turtle_screen.setup(WIDTH + 50, HEIGHT + 50)
        turtle_screen.setworldcoordinates(0, WIDTH + 50, HEIGHT + 50, 0)



        color_list = [
            '#c77373',
	        '#b1e369',
	        '#329f7b',
	        '#d6b474',
	        '#926a6a'
        ]

        idx = 1;
        for line in file.readlines():
            line_split = line.split()
            if len(line_split) == 5:
                [w, h, x, y, r] = map(int, line_split)
                b = Board(idx, w, h, x, y, r)
                color_idx = random.randint(0, len(color_list)-1)
                b.draw(turtle, color_list[color_idx])
                turtle_screen.update()
                idx = idx + 1

        #turtle_screen.tracer(True)
        turtle_screen.getcanvas().postscript(file="board.eps", colormode='color')
        turtle_screen.exitonclick()
        #turtle.done()


if __name__ == '__main__':
    main()
