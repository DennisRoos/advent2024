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
int field[100][100];
bool visited[100][100];
int answer2;

void clean() {
	for (int x = 0; x < fieldsize; x++) {
		for (int y = 0; y < fieldsize; y++) {
			visited[x][y] = false;
		}
	}
}

int traverse(int x, int y, int value) {
	if (!(x >= 0 && x < fieldsize && y >= 0 && y < fieldsize)) {
		return 0;
	}
	if (field[x][y] != value) {
		return 0;
	}
	if (value == 9) {
		answer2++;
		if (visited[x][y]) {
			return 0;
		}
		visited[x][y] = true;
		return 1;
	}
	int total = 
		traverse(x - 1, y, value + 1) + 
		traverse(x + 1, y, value + 1) + 
		traverse(x, y + 1, value + 1) + 
		traverse(x, y - 1, value + 1);
	return total;

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
		answer2 = 0;
		int y = 0;
		while (infile >> s)
		{
			fieldsize = s.size();
			for (int x = 0; x < s.size(); x++) {
				field[x][y] = s[x] - '0';
			}
			y++;
		}
		for (int x = 0; x < fieldsize; x++) {
			for (int y = 0; y < fieldsize; y++) {
				if (field[x][y] == 0) {
					clean();
					answer1 += traverse(x, y, 0);
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