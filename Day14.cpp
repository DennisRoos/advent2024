#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <sstream>
#include <algorithm> 
using namespace std;

struct robot {
	int x;
	int y;
	int dx;
	int dy;
};

vector<robot> v;
int width;
int height;

int find_christmas_tree() {
	int positions[101][103];

	for (int i = 0; i < 101; i++) {
		for (int j = 0; j < 103; j++) {
			positions[i][j] = 2;
		}
	}

	for (int tick = 0; tick < 101 * 103; tick++) {
		bool overlap = false;
		for (int i = 0; i < 101; i++) {
			for (int j = 0; j < 103; j++) {
				if (positions[i][j] > 1) {
					overlap = true;
				}
				
			}
		}
		if (overlap == false) {
			for (int i = 0; i < 103; i++) {
				for (int j = 0; j < 101; j++) {
					cout << positions[j][i];
				}
				cout << endl;
			}
			return tick;
		}

		for (int i = 0; i < 103; i++) {
			for (int j = 0; j < 101; j++) {
				positions[j][i] = 0;
			}
		}
		for (int i = 0; i < v.size(); i++) {
			v[i].x = (((v[i].x + v[i].dx) % width) + width) % width;
			v[i].y = (((v[i].y + v[i].dy) % height) + height) % height;
			positions[v[i].x][v[i].y]++;

		}
	}
	return 0;

}

int main(int argc, char* argv[])
{
	ifstream infile;
	infile.open("data.txt");

	if (infile.is_open())
	{
		string s;
		int answer1 = 0;
		int answer2 = 0;
		width = 101;
		height = 103;
		regex bot("p=(\\d+),(\\d+) v=(-?\\d+),(-?\\d+)");
		smatch match;
		while (getline(infile, s)) {
			if (regex_search(s, match, bot) == true) {
				int x = stoll(match.str(1));
				int y = stoll(match.str(2));
				int dx = stoll(match.str(3));
				int dy = stoll(match.str(4));
				robot r = robot();
				r.x = x;
				r.y = y;
				r.dx = dx;
				r.dy = dy;
				v.push_back(r);
			}
		}

		int topleft = 0;
		int topright = 0;
		int bottomleft = 0;
		int bottomright = 0;
		int midwidth = width / 2;
		int midheight = height / 2;
		for (int i = 0; i < v.size(); i++) {
			int x = (((v[i].x + (v[i].dx * 100)) % width) + width) % width;
			int y = (((v[i].y + (v[i].dy * 100)) % height) + height) % height;
			if (x < midwidth) { // left half
				if (y < midheight) {
					topleft++;
				}
				else if (y > midheight) {
					bottomleft++;
				}
			}
			else if (x > midwidth) { // right half
				if (y < midheight) {
					topright++;
				}
				else if (y > midheight) {
					bottomright++;
				}
			}
		}
		answer1 = topleft * topright * bottomleft * bottomright;
		cout << "Final answer for part 1 is " << answer1 << "\n";
		answer2 = find_christmas_tree();
		cout << "Final answer for part 2 is " << answer2 << "\n";
	}
	else {

		cout << "can't find file?\n";
	}
}


// 1110 too low

// 6871 too high