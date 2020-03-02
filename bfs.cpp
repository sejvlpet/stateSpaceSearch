
class BfsSolver {
public:
	std::queue<Cord> _next;
	int _nodesOpened = 0;
	int _nodesClosed = 0;

	void solve(Maze &maze) {
		if (maze._start == maze._end) {
			return;
		}

		std::vector<Cord> neighbors = maze.getNexMoves(maze._start);
		addAndOpenNeighbors(neighbors, maze._start, maze);

		while(!_next.empty()) {

			Cord c = _next.front();
			_next.pop(); 
			int x = c._x;
			int y = c._y;

			if (c == maze._end) { 
				return;
			}
			
			std::vector<Cord> neighbors = maze.getNexMoves(c);
			addAndOpenNeighbors(neighbors, c, maze);
			maze._maze[y][x].changeState(CLOSED); 
			_nodesClosed++;
			_nodesOpened--;

			maze.drawMaze();
		}
	}


private:
	void addAndOpenNeighbors(const std::vector<Cord> &neighbors, const Cord &from, Maze &maze) {
		for(int i = 0; i < (int) neighbors.size(); ++i) {
			int x = neighbors[i]._x;
			int y = neighbors[i]._y;
			maze._maze[y][x].changeState(OPENED);
			_nodesOpened++;
			maze._maze[y][x].setAncesor(from);

			_next.push(neighbors[i]);
		}
	}
};
