# A* visaulizer

Visualizer for [A* search algorithm](https://en.wikipedia.org/wiki/A*_search_algorithm) in C using\n
[raylib](https://www.raylib.com/).
<br />
<br />
A* is a pathfinding algorithm that finds the shortest path between source and destination using
a goal-directed heuristic.

## Demo

[![Watch the video]()](https://vimeo.com/1043903783?ts=0&share=copy)

## Building

## About A*

A* is an informed search algorithm that finds the shortest path between a source vertex and a destination
vertex in a weighted graph. It does this by maintaining a tree of paths originating at the start node
and extending those paths one edge at a time until the goal node is reached.
<br />
<br />
At each iteration of the search, A* holds a cost map of all visited nodes that is calculated by the
formula
```math
f(n) = g(n) + h(n)
```
where

- $g(n)$ is the cost of the path from the start node to node n
- $h(n)$ is the heuristic function that approximates how close node n is to the destination node
- $f(n)$ is the total cost of node n that is used to determine if a node is worthwhile to visit.

This implementation of A* uses a priority queue to store the neighbors of the current cell with the
priority of their cost. Since cost must be minimized, the cells with low cost are prioritized over cells
with higher cost.
<br />
<br />
The heuristic function h(n) estimates how close the current cell is to the destination cell, and can
be changed for different graph conditions. In this implementation, where the neighbors of a
the cell is defined as the 4 adjacent cells, the Manhattan distance between the current cell and the destination
cell is taken as a heuristic which is given by
```math
d = |x_2 - x_1| + |y_2 - y_1|
```
For a graph where diagonal traversal is allowed, Euclidean distance is used as a heuristic which is given
by
```math
d = \sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2}
```
where x1,y1, and x2,y2 define the coordinates of the current cell and the destination cell.
<br />
<br />
The time complexity of A* is given by $`O(b^d)`$ where b is the branching factor and d is the number
of nodes in the solution
