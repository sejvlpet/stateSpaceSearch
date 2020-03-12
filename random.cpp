
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
	    int random = rand() % (_cords.size() - _start) + _start;

	    swap(random);

	    _start++;
	    _open--; 

	    if( (int) _cords.size() / 4 > _open ) {
	    	resize();
	    }

	    return _cords[_start - 1];
	}

	bool empty() {
		return _open <= 0;
	}

private:
	void swap(int i) {
		Cord c = _cords[_start];
		_cords[_start] = _cords[i];
		_cords[i] = c;
	}

	void resize() {
		std::vector<Cord> newCords;
		newCords.reserve( (int) _cords.size() / 2);

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

	bool solve(Maze &maze) {
		if (maze._start == maze._end) {
			return true;
		}

		_nodesOpened += 1; // for opening of of the start
		std::vector<Cord> neighbors = maze.getNexMoves(maze._start);
		addAndOpenNeighbors(neighbors, maze._start, maze);

		while(!_next.empty()) {

			Cord c = _next.getRandomCord(); // recieve cords of next element


			int x = c._x;
			int y = c._y;

			if (c == maze._end) {
				return true;
			}
			
			std::vector<Cord> neighbors = maze.getNexMoves(c);
			addAndOpenNeighbors(neighbors, c, maze);
			maze._maze[y][x].changeState(CLOSED);

			maze.drawMaze();
		}
		
		return false;
	}



private:
	void addAndOpenNeighbors(const std::vector<Cord> &neighbors, const Cord &from, Maze &maze) {
		for(int i = 0; i < (int) neighbors.size(); ++i) {
			int x = neighbors[i]._x;
			int y = neighbors[i]._y;
			maze._maze[y][x].changeState(OPENED); 
			if (maze._maze[y][x]._state != END) _nodesOpened++;
			maze._maze[y][x].setAncesor(from);

			_next.push(neighbors[i]);
		}
	}
};
