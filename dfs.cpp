#include <iostream>
#include <vector>
#include <sstream>
#include <bits/stdc++.h> 
#include <sstream>

class DfsSolver {
public:
	std::stack<Cord> _next;
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

			Cord c = _next.top(); // recieve cords of next element
			_next.pop(); // remove it from stack as it's useles now
			int x = c._x;
			int y = c._y;

			if (c == maze._end) { // we've reachend the end, print and do something like that
				return;
			}

			std::vector<Cord> neighbors = maze.getNexMoves(c);
			addAndOpenNeighbors(neighbors, c, maze);
			maze._maze[y][x].changeState(CLOSED); // todo I'm really not sure bout that
			_nodesClosed++;

			maze.drawMaze();
    	}
	}



private:
	// places neighbors to stack, set information from where they were found
	void addAndOpenNeighbors(const std::vector<Cord> &neighbors, const Cord &from, Maze &maze) {
		for(int i = 0; i < (int) neighbors.size(); ++i) {
			int x = neighbors[i]._x;
			int y = neighbors[i]._y;
			maze._maze[y][x].changeState(OPENED); // todo should be really opened here?
			_nodesOpened++;
			maze._maze[y][x].setAncesor(from);

			_next.push(neighbors[i]);
		}
	}
};



// int main(int argc, char *argv[]) {
//     std::ifstream ifstream = std::ifstream(argv[1]);

// 	Maze maze;
// 	maze.readInput(ifstream);
	
// 	DfsSolver dfs;
// 	dfs.solve(maze);

// 	int input;
// 	maze.printFinal(dfs._nodesOpened,dfs._nodesClosed);		
//     while((input = getch()) != 'q') {}
// 	return 0;
// }