#include <iostream>
#include <algorithm>    
#include <cmath>    
#include <fstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


struct node {
	int x;
	int y;
	char freq;
};


using namespace std;
int fieldsize;
bool field[130][130];
vector<node> v;
int answer1;
int answer2;

bool add_antinode(int new_x, int new_y) {
	if (new_x >= 0 && new_x < fieldsize && new_y >= 0 && new_y < fieldsize) { // within field
		if (!field[new_x][new_y]) { //not already an antinode
			//cout << new_x << "," << new_y << " from " << a.x << "," << a.y << " and " << b.x << "," << b.y << endl;
			field[new_x][new_y] = true;
			return true;
		}
	}
	return false;
}

void simple_antinode(node a, node b) {
	int delta_x = b.x - a.x;
	int delta_y = b.y - a.y;
	int new_x = b.x + delta_x;
	int new_y = b.y + delta_y;
	if (add_antinode(new_x, new_y)) {
		answer1++;
	}
}

void complex_antinode(node a, node b) {
	if (add_antinode(a.x, a.y)) {
		answer2++;
	}
	int delta_x = b.x - a.x;
	int delta_y = b.y - a.y;
	int new_x = b.x + delta_x;
	int new_y = b.y + delta_y;
	while (new_x >= 0 && new_x < fieldsize && new_y >= 0 && new_y < fieldsize) {
		if (add_antinode(new_x, new_y)) {
			answer2++;
		}
		new_x += delta_x;
		new_y += delta_y;
	}
}

int main(int argc, char* argv[]) {
	ifstream infile;
	infile.open("data.txt");
	int start_x;
	int start_y;
	if (infile.is_open())
	{
		string s;
		answer1 = 0;
		int y = 0;
		while (infile >> s)
		{
			fieldsize = s.size();
			for (int x = 0; x < s.size(); x++) {
				field[x][y] = false;
				if (s[x] != '.') {
					node n;
					n.x = x;
					n.y = y;
					n.freq = s[x];
					v.push_back(n);
				}
			}
			y++;
		}
		for (int i = 0; i < v.size(); i++) {
			for (int j = i + 1; j < v.size(); j++) {
				if (v[i].freq == v[j].freq) {
					simple_antinode(v[i], v[j]);
					simple_antinode(v[j], v[i]);
				}
			}
		}
		answer2 = answer1;
		for (int i = 0; i < v.size(); i++) {
			for (int j = i + 1; j < v.size(); j++) {
				if (v[i].freq == v[j].freq) {
					complex_antinode(v[i], v[j]);
					complex_antinode(v[j], v[i]);
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