#include <iostream>
#include <vector>
#include <sstream>
#include <bits/stdc++.h> 
#include <sstream>


class RandomCordContainer {
public:
	std::vector<Cord> _cords;
	int _open = 0;
	int _start = 0;

	void push(Cord c) {
		_cords.push_back(c);
		_open++;
	}

	Cord getRandomCord() {
		srand(time(0)); 
	    int random = rand() %  (_cords.size() - _start) + _start;

	    swap(random);

	    _start++;
	    _open--; 

	    if( (int) _cords.size() / 4 > _open ) {
	    	resize();
	    }

	    return _cords[_start - 1];
	}

	bool empty() {
		return _cords.size() <= 0; // could/should work with open I guess
	}

private:
	void swap(int i) {
		Cord c = _cords[_start];
		_cords[_start] = _cords[i];
		_cords[i] = c;
	}

	void resize() {
		std::vector<Cord> newCords;
		for(int i = _start - 1; i < (int) _cords.size(); ++i) {
			newCords.push_back(_cords[i]);
		}
		_cords = newCords;
		_start = 1; // element on index 0 will be returned
	}
};



class RandomSolver {
public:
	RandomCordContainer _next;
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

			Cord c = _next.getRandomCord(); // recieve cords of next element


			int x = c._x;
			int y = c._y;

			if (c == maze._end) { // we've reachend the end, print and do something like that
				return;
			}
			
			std::vector<Cord> neighbors = maze.getNexMoves(c);
			addAndOpenNeighbors(neighbors, c, maze);
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
	
// 	BfsSolver bfs;
// 	bfs.solve(maze);
	
// 	int input;
// 	maze.printFinal(bfs._nodesOpened,bfs._nodesClosed);		
//     while((input = getch()) != 'q') {}

// 	return 0;
// }