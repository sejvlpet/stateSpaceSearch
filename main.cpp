#include <iostream>
#include <vector>
#include <sstream>
#include <bits/stdc++.h> 
#include <sstream>
#include <curses.h>

#include "schema.cpp"

#include "bfs.cpp"
#include "dfs.cpp"
#include "dijkstra.cpp"
#include "a_star.cpp"
#include "greedy.cpp"
#include "random.cpp"

const int BFS = 1;
const int DFS = 2;
const int DIJKSTRA = 3;
const int A_STAR = 4;
const int GREEDY = 5;
const int RANDOM = 6;

int main(int argc, char *argv[]) {
	int alg;
	std::cout << "Choose your algoritm - 1 for bfs, 2 for dfs, 3 for Dijkstra, 4 for A*, 5 for Greedy or 6 for random search.\n";
	std::cin >> alg;

	if(alg > RANDOM || alg < BFS) {
		std::cout << "You've entered wrong number" << std::endl;
		return 1;		
	}

    std::ifstream ifstream = std::ifstream(argv[1]);

	Maze maze;
	maze.readInput(ifstream);

	int opened = 0;
	int closed = 0;

	BfsSolver bfs;
	DfsSolver dfs;
	DijkstraSolver d;
	AstarSolver aStar;
	GreedySolver g;
	RandomSolver r;

	if (alg == BFS) {
		bfs.solve(maze);
		opened = bfs._nodesOpened;
		closed = bfs._nodesClosed;
	} else if (alg == DFS) {
		dfs.solve(maze);
		opened = dfs._nodesOpened;
		closed = dfs._nodesClosed;
	} else if (alg == DIJKSTRA) {
		d.solve(maze);
		opened = d._nodesOpened;
		closed = d._nodesClosed;
	} else if (alg == A_STAR) {
		aStar.solve(maze);
		opened = aStar._nodesOpened;
		closed = aStar._nodesClosed;
	} else if (alg == GREEDY) {
		g.solve(maze);
		opened = g._nodesOpened;
		closed = g._nodesClosed;
	} else if (alg == RANDOM) {
		r.solve(maze);
		opened = r._nodesOpened;
		closed = r._nodesClosed;
	}

	int input;
	maze.printFinal(opened, closed);		
    while((input = getch()) != 'q') {}

	return 0;
}