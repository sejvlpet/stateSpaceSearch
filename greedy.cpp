#include <iostream>
#include <vector>
#include <sstream>
#include <bits/stdc++.h> 
#include <sstream>

class GreedySolver {
public:
	std::priority_queue<Cell, std::vector<Cell>, CompareCells> _next;
	int _nodesOpened = 0;
	int _nodesClosed = 0;


	// todo maze reference could be memeber of dfs
	void solve(Maze &maze) {
		if (maze._start == maze._end) { // we've reachend the end, print and do something like that
			return;
		}

		std::vector<Cord> neighbors = maze.getNexMoves(maze._start);
		addAndOpenNeighbors(neighbors, maze._start, maze);

		while(!_next.empty()) {

			Cell c = _next.top(); // recieve cords of next element
			_next.pop(); // remove it from stack as it's useles now
			int x = c._position._x;
			int y = c._position._y;

			if (c._position == maze._end) { // we've reachend the end, print and do something like that
				return;
			}
			
			std::vector<Cord> neighbors = maze.getNexMoves(c._position);
			addAndOpenNeighbors(neighbors, c._position, maze);
			maze._maze[y][x].changeState(CLOSED); // todo I'm really not sure bout that
			_nodesClosed++;
			_nodesOpened--;

			maze.drawMaze();
		}
	}



private:
	// places neighbors to queue, set information from where they were found
	void addAndOpenNeighbors(const std::vector<Cord> &neighbors, const Cord &from, Maze &maze) {
		for(int i = 0; i < (int) neighbors.size(); ++i) {
			
			int x = neighbors[i]._x;
			int y = neighbors[i]._y;

			maze._maze[y][x].changeState(OPENED); // todo should be really opened here?
			maze._maze[y][x].setMinimunToEnd(maze._end);
			maze._maze[y][x].setAncesor(from);

			_nodesOpened++;

			_next.push(maze._maze[y][x]);
		}
	}
};
