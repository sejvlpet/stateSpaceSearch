
class GreedySolver {
public:
	std::priority_queue<Cell, std::vector<Cell>, CompareCells> _next;
	int _nodesOpened = 0;

	bool solve(Maze &maze) {
		if (maze._start == maze._end) {
			 return true;
		}

		_nodesOpened += 1; // for opening of of the start
		std::vector<Cord> neighbors = maze.getNexMoves(maze._start);
		addAndOpenNeighbors(neighbors, maze._start, maze);

		while(!_next.empty()) {

			Cell c = _next.top();
			_next.pop();
			int x = c._position._x;
			int y = c._position._y;

			if (c._position == maze._end) return true;
			if (maze._maze[y][x]._state == CLOSED) continue; // node can be in pq, but already closed, this happens if first found path wasn't the shortest

			std::vector<Cord> neighbors = maze.getNexMoves(c._position);
			addAndOpenNeighbors(neighbors, c._position, maze);
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

			if(maze._maze[y][x]._state == IN_PRORITY_QUEUE && maze._maze[y][x].getMinimunToEnd(maze._end) >= maze._maze[y][x]._minPossibleToEnd) continue; 
			if(maze._maze[y][x]._state != IN_PRORITY_QUEUE && maze._maze[y][x]._state != END) _nodesOpened++;

			maze._maze[y][x].changeState(IN_PRORITY_QUEUE);
			maze._maze[y][x].setMinimunToEnd(maze._end);
			maze._maze[y][x].setAncesor(from);

			_next.push(maze._maze[y][x]);
		}
	}
};
