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
	std::cout << "Choose your algorithm - 1 for bfs, 2 for dfs, 3 for Dijkstra, 4 for A*, 5 for Greedy or 6 for random search.\n";
	std::cin >> alg;

	if(alg > RANDOM || alg < BFS) {
		std::cout << "You've entered wrong number" << std::endl;
		return 1;		
	}

    std::ifstream ifstream = std::ifstream(argv[1]);

	Maze maze;
	maze.readInput(ifstream);

	int opened = 0;
	bool res = false;

	BfsSolver bfs;
	DfsSolver dfs;
	DijkstraSolver d;
	AstarSolver aStar;
	GreedySolver g;
	RandomSolver r;

	if (alg == BFS) {
		res = bfs.solve(maze);
		opened = bfs._nodesOpened;
	} else if (alg == DFS) {
		res = dfs.solve(maze);
		opened = dfs._nodesOpened;
	} else if (alg == DIJKSTRA) {
		res = d.solve(maze);
		opened = d._nodesOpened;
	} else if (alg == A_STAR) {
		res = aStar.solve(maze);
		opened = aStar._nodesOpened;
	} else if (alg == GREEDY) {
		res = g.solve(maze);
		opened = g._nodesOpened;
	} else if (alg == RANDOM) {
		res = r.solve(maze);
		opened = r._nodesOpened;
	}

	int input;
	if(res) {
		maze.printFinal(opened);		
	    while((input = getch()) != 'q') {}
	} else {
		printw("Algoritm hasn't reached the end, press q to quit");
		while((input = getch()) != 'q') {}
	}
	return 0;
}