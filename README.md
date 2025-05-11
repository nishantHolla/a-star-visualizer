# A* visualizer

Visualizer for [A* search algorithm](https://en.wikipedia.org/wiki/A*_search_algorithm) in C using
[raylib](https://www.raylib.com/).
<br />
<br />
A* is a pathfinding algorithm that finds the shortest path between source and destination using a goal-directed heuristic.

## Demo

https://github.com/user-attachments/assets/4a38f041-a8de-40b0-8c4d-3df8970cda81

## Building using docker

- If you are using linux make sure to run these to use docker buildkit and allow x11 forwarding

```bash
export DOCKER_BUILDKIT=1
xhost +local:root > /dev/null
```

- If you are using MacOS make sure to run these to use docker buildkit and allow x11 forwarding
```bash
export DOCKER_BUILDKIT=1
```
Setting up Docker for gui in mac: [https://gist.github.com/roaldnefs/fe9f36b0e8cf2890af14572c083b516c](https://gist.github.com/roaldnefs/fe9f36b0e8cf2890af14572c083b516c)

- If you are using windows setup WSL and follow the steps for linux machine.

- Clone the repository

```bash
git clone https://github.com/nishantHolla/a-star-visualizer
cd a-star-visualizer
```

- Run build script to build in debug mode

```bash
./build.sh debug
```

or in release mode

```bash
./build.sh release
```

- Execute the program

```bash
./run debug
```

or if you built in release mode

```bash
./run release
```

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
The heuristic function $h(n)$ estimates how close the current cell is to the destination cell, and can
be changed for different graph conditions. In this implementation, where the neighbors of a
the cell is defined as the 4 adjacent cells connected by a common edge, the Manhattan distance between the current cell and the destination
cell is taken as a heuristic which is given by
```math
d = |x_2 - x_1| + |y_2 - y_1|

```

For a graph where diagonal traversal is allowed, Euclidean distance is used as a heuristic which is given
by
```math
d = \sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2}

```

where $`x1`$, $`y1`$, and $`x2`$, $`y2`$ define the coordinates of the current cell and the destination cell.
<br />
<br />
The time complexity of A* is given by $`O(b^d)`$ where b is the branching factor and d is the number
of nodes in the solution
