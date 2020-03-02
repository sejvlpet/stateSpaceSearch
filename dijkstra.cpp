
class DijkstraSolver {
public:
	std::priority_queue<Cell, std::vector<Cell>, CompareCells> _next;
	int _nodesOpened = 0;
	int _nodesClosed = 0;

	void solve(Maze &maze) {
		if (maze._start == maze._end) {
			return;
		}

		std::vector<Cord> neighbors = maze.getNexMoves(maze._start);
		addAndOpenNeighbors(neighbors, maze._start, maze);

		while(!_next.empty()) {

			Cell c = _next.top();
			_next.pop();
			int x = c._position._x;
			int y = c._position._y;

			if (c._position == maze._end) {
				return;
			}
			
			std::vector<Cord> neighbors = maze.getNexMoves(c._position);
			addAndOpenNeighbors(neighbors, c._position, maze);
			maze._maze[y][x].changeState(CLOSED);
			_nodesClosed++;
			_nodesOpened--;

			maze.drawMaze();
		}
	}


private:
	void addAndOpenNeighbors(const std::vector<Cord> &neighbors, const Cord &from, Maze &maze) {
		int dist = maze._maze[from._y][from._x]._distanceFromStart + 1;
		for(int i = 0; i < (int) neighbors.size(); ++i) {
			
			int x = neighbors[i]._x;
			int y = neighbors[i]._y;

			maze._maze[y][x].changeState(OPENED);
			maze._maze[y][x]._distanceFromStart = dist;
			maze._maze[y][x].setAncesor(from);

			_nodesOpened++;

			_next.push(maze._maze[y][x]);
		}
	}
};
