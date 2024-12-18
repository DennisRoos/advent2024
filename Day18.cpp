#include <iostream>
#include <algorithm>    
#include <cmath>    
#include <fstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

int A[71][71];
int dist[71][71];
bool blocked[71][71];
int X[5000];
int Y[5000];
int fieldsize;

void navigate(int x, int y, int distance) {
	if (x < 0 || x > fieldsize || y < 0 || y > fieldsize) {
		return;
	}
	if (blocked[x][y]) {
		return;
	}
	if (dist[x][y] <= distance) {
		return;
	}
	dist[x][y] = distance;
	navigate(x - 1, y, distance + 1);
	navigate(x + 1, y, distance + 1);
	navigate(x, y - 1, distance + 1);
	navigate(x, y + 1, distance + 1);
}

bool navigate2(int x, int y, int distance) {
	if (x < 0 || x > fieldsize || y < 0 || y > fieldsize) {
		return false;
	}
	if (blocked[x][y]) {
		return false;
	}
	if (x == fieldsize && y == fieldsize) {
		return true;
	}
	if (dist[x][y] <= distance) {
		return false;
	}
	dist[x][y] = distance;
	return navigate2(x - 1, y, distance + 1) ||
	navigate2(x + 1, y, distance + 1) ||
	navigate2(x, y - 1, distance + 1) ||
	navigate2(x, y + 1, distance + 1);
}

string find_blocker() {
	int tick = 1024;
	while (true) {
		blocked[X[tick]][Y[tick]] = true;
		for (int i = 0; i < 71; i++) {
			for (int j = 0; j < 71; j++) {
				dist[i][j] = 999999;
			}
		}
		if (!navigate2(0, 0, 0)) {
			return to_string(X[tick]) + "," + to_string(Y[tick]);
		}
		tick++;
	}
}


int main(int argc, char* argv[]) {
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{	
		string s;
		int x; 
		int y;
		int i = 0;
		int answer1;
		string answer2;
		for (int i = 0; i < 71; i++) {
			for (int j = 0; j < 71; j++) {
				blocked[i][j] = false;
				dist[i][j] = 999999;
			}
		}
		fieldsize = 0;
		while (infile >> s) {
			stringstream ss(s);
			getline(ss, s, ',');
			x = stoi(s);
			getline(ss, s, ',');
			y = stoi(s);
			fieldsize = max(fieldsize, x);
			X[i] = x;
			Y[i] = y;
			if (i < 1024) {
				blocked[x][y] = true;
			}
			i++;
		}
		navigate(0, 0, 0);
		answer1 = dist[fieldsize][fieldsize];
		answer2 = find_blocker();
		cout << "Final answer for part 1 is " << answer1 << "\n";
		cout << "Final answer for part 2 is " << answer2 << "\n";
		
	}

	else {
		cout << "can't find file?\n";
	}
}


// 321369175486 too low
// 20567627247063 too low