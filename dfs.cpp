
class DfsSolver {
public:
	std::stack<Cord> _next;
	int _nodesOpened = 0;

	bool solve(Maze &maze) {
		if (maze._start == maze._end) {
			 return true;
		}

		_nodesOpened += 1; // for opening of of the start
		std::vector<Cord> neighbors = maze.getNexMoves(maze._start);
		addAndOpenNeighbors(neighbors, maze._start, maze);

		while(!_next.empty()) {

			Cord c = _next.top();
			_next.pop();
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
			if(maze._maze[y][x]._state != END) _nodesOpened++;
			maze._maze[y][x].setAncesor(from);

			_next.push(neighbors[i]);
		}
	}
};