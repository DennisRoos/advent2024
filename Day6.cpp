#include <iostream>
#include <algorithm>    
#include <cmath>    
#include <fstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


using namespace std;
int fieldsize;
char field[130][130];
bool visited[130][130][4];


int traverse(int x, int y) {
	int direction = 0; //North
	int visited_tiles = 1;
	while (x >= 0 && x < fieldsize && y >= 0 && y < fieldsize) {
		if (direction == 0) { // North
			if (y > 0 && field[x][y - 1] == '#') {
				direction = 1;
			}
			else {
				y--;
			}
		}
		else if (direction == 1) { // East
			if (x < fieldsize - 1 && field[x + 1][y] == '#') {
				direction = 2;
			}
			else {
				x++;
			}
		}
		else if (direction == 2) { // South
			if (y - fieldsize - 1 && field[x][y + 1] == '#') {
				direction = 3;
			}
			else {
				y++;
			}
		}
		else if (direction == 3) { // West
			if (x > 0 && field[x - 1][y] == '#') {
				direction = 0;
			}
			else {
				x--;
			}
		}
		if (field[x][y] == '.') {
			field[x][y] = 'O';
			visited_tiles++;
		}
	}
	return visited_tiles;
}


int traverse_2(int x, int y) {
	int direction = 0;
	while (x >= 0 && x < fieldsize && y >= 0 && y < fieldsize) {
		if (visited[x][y][direction]) {// loop
			return 1;
		}
		visited[x][y][direction] = true;
		if (direction == 0) { // North
			if (y > 0 && field[x][y - 1] == '#') {
				direction = 1;
			}
			else {
				y--;
			}
		}
		else if (direction == 1) { // East
			if (x < fieldsize - 1 && field[x + 1][y] == '#') {
				direction = 2;
			}
			else {
				x++;
			}
		}
		else if (direction == 2) { // South
			if (y - fieldsize - 1 && field[x][y + 1] == '#') {
				direction = 3;
			}
			else {
				y++;
			}
		}
		else if (direction == 3) { // West
			if (x > 0 && field[x - 1][y] == '#') {
				direction = 0;
			}
			else {
				x--;
			}
		}
	}
	return 0;
}


int main(int argc, char* argv[]) {
	ifstream infile;
	infile.open("data.txt");
	int start_x;
	int start_y;
	if (infile.is_open())
	{
		string s;
		int answer1;
		int answer2 = 0;
		int y = 0;
		while (infile >> s)
		{
			fieldsize = s.size();
			for (int x = 0; x < s.size(); x++) {
				field[x][y] = s[x];
				if (s[x] == '^') {
					start_x = x;
					start_y = y;
					field[x][y] = 'O';
				}
			}
			y++;
		}

		answer1 = traverse(start_x, start_y);
		cout << "Final answer for part 1 is " << answer1 << "\n";

		for (int x = 0; x < fieldsize; x++) {
			for (int y = 0; y < fieldsize; y++) {
				if (!(x == start_x && y == start_y) && field[x][y] != '#') { // only try on empty places

					for (int i = 0; i < fieldsize; i++) { // clear visited array
						for (int j = 0; j < fieldsize; j++){
							for (int k = 0; k < 4; k++) {
								visited[i][j][k] = false;
							}
						}
					}
					field[x][y] = '#';  // place obstacle
					answer2 += traverse_2(start_x, start_y);
					field[x][y] = '.';  // remove obstacle
				}

			}
		}
		cout << "Final answer for part 2 is " << answer2 << "\n";
	}

	else {
		cout << "can't find file?\n";
	}
}
