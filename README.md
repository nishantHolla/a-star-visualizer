# A* visaulizer

Visualizer for [A* search algorithm](https://en.wikipedia.org/wiki/A*_search_algorithm) in C using\n
[raylib](https://www.raylib.com/).
<br />
<br />
A* is a pathfinding algorithm that finds the shortest path between source and destination using
a goal directed heuristic.

## Building

## About A*

A* is an informed search algorithm that finds the shortest path between a source vertex and a destination
vertex in a weighted graph. It does this by maintaining a tree of paths originating at the start node
and extending those paths one edge at a time until the goal node is reached.
<br />
<br />
At each itteration of the search, A* holds a cost map of all visited nodes that is calculates by the
formula
$$
f(n) = g(n) + h(n)
$$
where

- $g(n)$ is the cost of the path from start node to node n
- $h(n)$ is the heuristic function that approximates how close node n is to the destination node
- $f(n)$ is the total cost of node n that is used to determine if a node is worthwhile to visit.

This implementation of A* uses a priority queue to store the neighbors of the current cell with the
priority of their cost. Since cost must be minimized, the cells with low cost is prioritized over cells
with higher cost.
<br />
<br />
The heuristic function h(n) that estimates how close current cell is to the destination cell, can
be changed for different conditions of the graph. In this implementation, where the neighbors of a
cell is defined as the 4 adjacent cells, Manhattan distance between the current cell and the destination
cell is taken as heuristic which is given by
$$
d = |x_2 - x_1| + |y_2 - y_1|
$$
For a graph whre diagonal traversal is allowed, Euclidean distance is used as heuristic which is given
by
$$
d = \sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2}
$$
whre x1,y1 and x2,y2 define the coordinates of the current cell and the destination cell.
<br />
<br />
The time complexity of A* is given by $O(b^d)$ where b is the branching factor and d is the number
of nodes in the solution
