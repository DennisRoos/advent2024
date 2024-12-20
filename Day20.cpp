#include <iostream>
#include <algorithm>    
#include <cmath>    
#include <fstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>

using namespace std;


int fieldsize;
char field[142][142];
int dist[142][142];
int Sx;
int Sy;
int Ex;
int Ey;

bool next(int x, int y) {
	return field[x][y] != '#' && dist[x][y] == -1;
}

void traverse_path() {
	int x = Sx;
	int y = Sy;
	int distance = 0;
	dist[x][y] = 0;
	while (field[x][y] != 'E') {
		distance++;
		if (next(x + 1, y)) {
			x++;
		}
		else if (next(x - 1, y)) {
			x--;
		}
		else if (next(x, y + 1)) {
			y++;
		}
		else if (next(x, y - 1)) {
			y--;
		}
		dist[x][y] = distance;
	}
}

int cheat(int x, int y, int x2, int y2, int cheat_duration) {
	if (x2 < 0 || x2 >= fieldsize || y2 < 0 || y2 >= fieldsize) {  // outside the maze
		return 0;
	}
	if (field[x2][y2] == '#') {
		return 0;
	}
	if (dist[x2][y2] - dist[x][y] >= 100 + cheat_duration) {
		return 1;
	}
	return 0;
}

int cheats(int x, int y, int max_cheat_duration) {
	int num_cheats = 0;
	for (int cheat_duration = 2; cheat_duration <= max_cheat_duration; cheat_duration++) {
		num_cheats += cheat(x, y, x, y - cheat_duration, cheat_duration);
		num_cheats += cheat(x, y, x, y + cheat_duration, cheat_duration);
		num_cheats += cheat(x, y, x - cheat_duration, y, cheat_duration);
		num_cheats += cheat(x, y, x + cheat_duration, y, cheat_duration);
		for (int deltaX = 1; deltaX < cheat_duration; deltaX++) {
			int deltaY = cheat_duration - deltaX;
			num_cheats += cheat(x, y, x - deltaX, y - deltaY, cheat_duration);
			num_cheats += cheat(x, y, x + deltaX, y - deltaY, cheat_duration);
			num_cheats += cheat(x, y, x - deltaX, y + deltaY, cheat_duration);
			num_cheats += cheat(x, y, x + deltaX, y + deltaY, cheat_duration);
		}
	}
	return num_cheats;
}

int main(int argc, char* argv[]) {
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string s;
		int answer1 = 0;
		int answer2 = 0;
		int y = 0;
		while (infile >> s)
		{
			fieldsize = s.size();
			for (int x = 0; x < s.size(); x++) {
				field[x][y] = s[x];
				dist[x][y] = -1;
				if (s[x] == 'S') {
					Sx = x;
					Sy = y;
				}
				if (s[x] == 'E') {
					Ex = x;
					Ey = y;
				}
			}
			y++;
		}
		traverse_path();
		for (int y = 1; y < fieldsize - 1; y++) {
			for (int x = 1; x < fieldsize - 1; x++) {
				if (field[x][y] != '#') {
					answer1 += cheats(x, y, 2);
					answer2 += cheats(x, y, 20);
				}
			}
		}
		cout << "Final answer for part 1 is " << answer1 << "\n";
		cout << "Final answer for part 2 is " << answer2 << "\n";
	}

	else {
		cout << "can't find file?\n";
	}
}
