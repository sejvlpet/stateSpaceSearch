
#include <iostream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <curses.h>

enum STATES {
	WALL, UNATTENDED, OPENED, CLOSED, START, END, ERROR, UNITILISED, FINAL
};

enum COLOR_PAIR {
    RED_PAIR = 1, BLUE_PAIR, YELLOW_PAIR, GREEN_PAIR
};


const char WALL_CHAR = 'X';
const char UNATTENDED_CHAR = ' ';
const char OPENED_CHAR = 'O';
const char CLOSED_CHAR = '-';
const char START_CHAR = 'S';
const char END_CHAR = 'E';
const char ERROR_CHAR = 'e';
const char FINAL_CHAR = '+';


class Cord {
public:
	int _x;
	int _y;

    Cord() = default;
    Cord(int x, int y) : _x(x), _y(y) {}

	bool operator == (const Cord& other) const { // todo test
        return _x == other._x && _y == other._y;
    }
};


class Cell {

public:
	STATES _state = UNITILISED;
	Cord _position;
	Cord _accessedFrom;
	int _distanceFromStart;


	void print() { // todo refactor using << overload
		if (_state == WALL) addch(WALL_CHAR | COLOR_PAIR(BLUE_PAIR));
		if (_state == UNATTENDED) addch(UNATTENDED_CHAR | COLOR_PAIR(BLUE_PAIR));
		if (_state == OPENED) addch(OPENED_CHAR | COLOR_PAIR(GREEN_PAIR));
		if (_state == CLOSED) addch(CLOSED_CHAR | COLOR_PAIR(YELLOW_PAIR));
		if (_state == START) addch(START_CHAR | COLOR_PAIR(RED_PAIR));
		if (_state == END) addch(END_CHAR | COLOR_PAIR(RED_PAIR));
		if (_state == FINAL)  addch(FINAL_CHAR | COLOR_PAIR(RED_PAIR));
	}

	bool isToVisit() const {
		return _state == UNATTENDED || _state == END;
	}

	void changeState(STATES state) {
		if(_state != END) _state = state;
	}
	void setAncesor(Cord c) {
		_accessedFrom = c;
	}

};


class Maze {
public:
	std::vector<std::vector<Cell>> _maze;
	Cord _start;
	Cord _end;

	Maze() {
		initNcurses();
	}

	~Maze() {
	   	endwin();

	}

	// reads maze into vector of strings given as parameter
	// fills 2D vector of structs which'll be handy later
	void readInput(std::istream &istream) { // TODO implement as >> overload
		std::string line;
		bool start = true;
		int y = 0;
		while (std::getline(istream, line)) {
			if(line.empty()) {
            	continue;
        	}
	    	if(line[0] != 'X') { // indicates end of maze, information abot the start and the end'll be read
	    		setTarget(line, start);
	    		start = false;
	    		continue;
	    	} 

	    	std::vector<Cell> tmp;

	    	for(int x = 0; x < (int) line.length(); ++x) {
	    		Cell cell;
	    		cell._state = line[x] == 'X' ? WALL : UNATTENDED;
	    		cell._position = Cord(x, y);
	    		tmp.push_back(cell);
			}

			_maze.push_back(tmp);
			y++;
		}

		_maze[_start._y][_start._x]._state = START; 
		_maze[_start._y][_start._x]._distanceFromStart = 0;

		_maze[_end._y][_end._x]._state = END;

	}

	void drawMaze() {
		move(0,0);
   	 	refresh();
		for(int i = 0; i <  (int) _maze.size(); ++i) {
			for(int j = 0; j <  (int) _maze[i].size(); ++j) {
				_maze[i][j].print();
			}
			addch('\n');
		}
     	getch();
	}

	void printFinal(int opened, int closed) {
		Cord end = _end;
		int length = 0;
		while(!(_start == end)) {
			int x = end._x;
			int y = end._y;
			_maze[y][x].changeState(FINAL);
			end = _maze[y][x]._accessedFrom;
			length++;
		}
		drawMaze();
		printw("Nodes expanded: %d, Nodes closed %d, path length: %d\n", opened, closed, length);
		printw("Press q to quit");
	}

	std::vector<Cord> getNexMoves(const Cord &c) const {
		int x = c._x;
		int y = c._y;

		std::vector<Cord> toVisit;

		if(x < 0 || y < 0) return toVisit;

		if(_maze[y][x + 1].isToVisit()) toVisit.emplace_back(x + 1, y);
		if(_maze[y][x - 1].isToVisit()) toVisit.emplace_back(x - 1, y);
		if(_maze[y - 1][x].isToVisit()) toVisit.emplace_back(x, y - 1);
		if(_maze[y + 1][x].isToVisit()) toVisit.emplace_back(x, y + 1);

		return toVisit;
	}

private:
	void initNcurses() {
		initscr();
		cbreak();
	    noecho();
	    keypad(stdscr, true);
	    start_color();
	    use_default_colors();
	    init_pair(BLUE_PAIR, COLOR_BLUE, -1);
	    init_pair(RED_PAIR, COLOR_RED, -1);
	    init_pair(YELLOW_PAIR, COLOR_YELLOW, -1);
	    init_pair(GREEN_PAIR, COLOR_GREEN, -1);
	}

	void setTarget(const std::string phrase, bool start) {
		Cord newCord;

		int count = 0;
		std::stringstream ss;
		ss << phrase;
		int num;
	    std::string temp; 
	   
	    while (!ss.eof() && count < 2) { 
	          ss >> temp; 
	  
	          if (std::stringstream(temp) >> num) {
	              if(count == 1) newCord._y = num;
	              if(count == 0) newCord._x = num;
	              count++;
	          }                
	          temp = ""; 
	    }

	    if (start) _start = newCord;
	    else _end = newCord;
	}

};
