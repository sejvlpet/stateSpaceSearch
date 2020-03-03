
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

			// get coordination
			Cell c = _next.top();
			_next.pop();
			int x = c._position._x;
			int y = c._position._y;

			// test
			if (c._position == maze._end) return;
			if (maze._maze[y][x]._state == CLOSED) continue; // node can be in pq, but already closed, this happens if first found path wasn't the shortest

			// find neighbors
			std::vector<Cord> neighbors = maze.getNexMoves(c._position);
			addAndOpenNeighbors(neighbors, c._position, maze);

			// close node
			maze._maze[y][x].changeState(CLOSED);

			// draw maze
			maze.drawMaze();
		}
	}


private:
	void addAndOpenNeighbors(const std::vector<Cord> &neighbors, const Cord &from, Maze &maze) {
		int dist = maze._maze[from._y][from._x]._distanceFromStart + 1;
		for(int i = 0; i < (int) neighbors.size(); ++i) {
			
			int x = neighbors[i]._x;
			int y = neighbors[i]._y;

			if(maze._maze[y][x]._state == IN_PRORITY_QUEUE && dist >= maze._maze[y][x]._distanceFromStart) continue;
 
			if(maze._maze[y][x]._state != IN_PRORITY_QUEUE) _nodesOpened++;

			maze._maze[y][x].changeState(IN_PRORITY_QUEUE);
			maze._maze[y][x]._distanceFromStart = dist;
			maze._maze[y][x].setAncesor(from);

			_next.push(maze._maze[y][x]);
		}
	}
};
