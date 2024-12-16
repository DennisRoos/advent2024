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
char A[142][142];
int dist[142][142][4];
bool bestPath[142][142];
int Sx;
int Sy;
int Ex;
int Ey;

struct step {
	int x;
	int y;
	int d;
	int s;
};
vector<step> v;

void add_step(int x, int y, int score, int d) {
	step s;
	s.x = x;
	s.y = y;
	s.d = d;
	s.s = score;
	v.push_back(s);
}


bool moveSouth2(int x, int y, int score);
bool moveEast2(int x, int y, int score);
bool moveWest2(int x, int y, int score);
bool moveNorth2(int x, int y, int score);

void moveEast(int x, int y, int score) {
	if (A[x][y] == '#') {
		return;
	}
	if (dist[x][y][0] <= score) {
		return;
	}
	dist[x][y][0] = score;
	if (A[x][y] == 'E') {
		return;
	}
	add_step(x + 1, y, score + 1, 0);
	add_step(x, y - 1, score + 1001, 3);
	add_step(x, y + 1, score + 1001, 1);
}


void moveSouth(int x, int y, int score) {
	if (A[x][y] == '#') {
		return;
	}
	if (dist[x][y][1] <= score) {
		return;
	}
	dist[x][y][1] = score;
	if (A[x][y] == 'E') {
		return;
	}
	add_step(x, y + 1, score + 1, 1);
	add_step(x + 1, y, score + 1001, 0);
	add_step(x - 1, y, score + 1001, 2);
}


void moveWest(int x, int y, int score) {
	if (A[x][y] == '#') {
		return;
	}
	if (dist[x][y][2] <= score) {
		return;
	}
	dist[x][y][2] = score;
	if (A[x][y] == 'E') {
		return;
	}
	add_step(x - 1, y, score + 1, 2);
	add_step(x, y - 1, score + 1001, 3);
	add_step(x, y + 1, score + 1001, 1);
}

void moveNorth(int x, int y, int score) {
	if (A[x][y] == '#') {
		return;
	}
	if (dist[x][y][3] <= score) {
		return;
	}
	dist[x][y][3] = score;
	if (A[x][y] == 'E') {
		return;
	}
	add_step(x, y - 1, score + 1, 3);
	add_step(x + 1, y, score + 1001, 0);
	add_step(x - 1, y, score + 1001, 2);
}



bool moveEast2(int x, int y, int score) {
	if (A[x][y] == '#') {
		return false;
	}
	if (dist[x][y][0] != score) { // Not on optimal path
		return false;
	}
	if (A[x][y] == 'E') {
		bestPath[x][y] = true;
		return true;
	}
	bool result1 = moveEast2(x + 1, y, score + 1);
	bool result2 = moveSouth2(x, y + 1, score + 1001);
	bool result3 = moveNorth2(x, y - 1, score + 1001);
	bool result = result1 || result2 || result3;
	if (result) {
		bestPath[x][y] = true;
	}
	return result;
}

bool moveSouth2(int x, int y, int score) {
	if (A[x][y] == '#') {
		return false;
	}
	if (dist[x][y][1] != score) { // Not on optimal path
		return false;
	}
	if (A[x][y] == 'E') {
		bestPath[x][y] = true;
		return true;
	}
	bool result1 = moveSouth2(x, y + 1, score + 1);
	bool result2 = moveWest2(x - 1, y, score + 1001);
	bool result3 = moveEast2(x + 1, y, score + 1001);
	bool result = result1 || result2 || result3;
	if (result) {
		bestPath[x][y] = true;
	}
	return result;
}


bool moveWest2(int x, int y, int score) {
	if (A[x][y] == '#') {
		return false;
	}
	if (dist[x][y][2] != score) { // Not on optimal path
		return false;
	}
	if (A[x][y] == 'E') {
		bestPath[x][y] = true;
		return true;
	}
	bool result1 = moveWest2(x - 1, y, score + 1);
	bool result2 = moveSouth2(x, y + 1, score + 1001);
	bool result3 = moveNorth2(x, y - 1, score + 1001);
	bool result = result1 || result2 || result3;
	if (result) {
		bestPath[x][y] = true;
	}
	return result;
}

bool moveNorth2(int x, int y, int score) {
	if (A[x][y] == '#') {
		return false;
	}
	if (dist[x][y][3] != score) { // Not on optimal path
		return false;
	}
	if (A[x][y] == 'E') {
		bestPath[x][y] = true;
		return true;
	}
	bool result1 = moveNorth2(x, y - 1, score + 1);
	bool result2 = moveWest2(x - 1, y, score + 1001);
	bool result3 = moveEast2(x + 1, y, score + 1001);
	bool result = result1 || result2 || result3;
	if (result) {
		bestPath[x][y] = true;
	}
	return result;
}


int main(int argc, char* argv[]) {
	ifstream infile;
	infile.open("data.txt");
	int start_x;
	int start_y;
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
				A[x][y] = s[x];
				bestPath[x][y] = false;
				for (int i = 0; i < 4; i++) {
					dist[x][y][i] = 200000000;
				}
				if (s[x] == 'S') {
					Sx = x;
					Sy = y;
				}
				else if (s[x] == 'E') {
					Ex = x;
					Ey = y;
				}
			}
			y++;
		}

		bool b = true;
		while (b) {
			b = false;
			for (int j = 1; j < fieldsize; j++) {//close all dead ends
				for (int i = 1; i < fieldsize; i++) {
					if (A[i][j] == '.') {
						int k = 0;
						if (A[i + 1][j] == '#') {
							k++;
						}
						if (A[i - 1][j] == '#') {
							k++;
						}
						if (A[i][j + 1] == '#') {
							k++;
						}
						if (A[i][j - 1] == '#') {
							k++;
						}

						if (k >= 3) {
							A[i][j] = '#';
							b = true;
						}
					}
				}
			}
		}
		add_step(Sx, Sy, 0, 0);
		for (int i = 0; i < v.size(); i++) {
			if (v[i].d == 0) {
				moveEast(v[i].x, v[i].y, v[i].s);
			}
			else if (v[i].d == 1 ) {
				moveSouth(v[i].x, v[i].y, v[i].s);
			}
			else if (v[i].d == 2) {
				moveWest(v[i].x, v[i].y, v[i].s);
			}
			else {
				moveNorth(v[i].x, v[i].y, v[i].s);
			}
		}
		answer1 = min(dist[Ex][Ey][0], dist[Ex][Ey][3]);
		dist[Ex][Ey][0] = answer1;
		dist[Ex][Ey][3] = answer1;
		moveEast2(Sx, Sy, 0);

		for (int j = 1; j < fieldsize; j++) {
			for (int i = 1; i < fieldsize; i++) {
				if (bestPath[i][j]) {
					answer2++;
				}
			}
		}

		for (int y = 0; y < fieldsize; y++) {
			for (int x = 0; x < fieldsize; x++) {
				if (bestPath[x][y]) {
					cout << 'O';
				}
				else {
					cout << A[x][y];
				}
			}
			cout << endl;
		}
		cout << "Final answer for part 1 is " << answer1 << "\n";
		cout << "Final answer for part 2 is " << answer2 << "\n";
	}
}