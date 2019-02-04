# Fireworks Project Report

Alexander Ahlbrandt

010726372

## Problem Statement
Written in C++, this simple program uses openGL to draw a static image of what a firework may look like after explosion. There is no input, no error handeling, and no output (other than the window displaying the fireworks).

## Design
This C++ program has three classes that define the structure of the program: Coordinate, LineSegment, Color, and Firework. There is a global vector of fireworks, and an array of coordinates for them to be placed at. The firework class is responsible for generating the destination coordinates, the line segments, and finally drawing them. The other classes serve as basic data structures. This allows me to make computations in an organized and consistent manner.

## Implementation
At the main method, the window is initialized for drwaing. I define some coordinates to serve as the origin, then three fireworks are instantiated, centered with an origin. In the display method, the fireworks are drawn.
## Testing

## Conclusion
