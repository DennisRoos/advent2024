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
int region[142][142];
int r_size[1000];
int corners[1000];

int region_size;
int perimeter;


void explore_region(int x, int y, char label, int region_id) {
	if (field[x][y] != label) {
		perimeter++;
		return;
	}
	else if (region[x][y] != -1) {
		return;
	}
	else {
		region[x][y] = region_id;
		region_size++;
		explore_region(x - 1, y, label, region_id);
		explore_region(x, y - 1, label, region_id);
		explore_region(x + 1, y, label, region_id);
		explore_region(x, y + 1, label, region_id);
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
		int answer1 = 0;
		int answer2 = 0;
		int y = 1;
		while (infile >> s)
		{
			fieldsize = s.size();
			for (int x = 0; x < s.size(); x++) {
				field[x+1][y] = s[x];
				region[x + 1][y] = -1;
			}
			y++;
		}
		for (int i = 0; i < 142; i++) {
			region[i][0] = 0;
			region[0][i] = 0;
			region[i][fieldsize+1] = 0;
			region[fieldsize+1][i] = 0;
		}
		int region_id = 1;
		for (int x = 1; x <= fieldsize; x++) {
			for (int y = 1; y <= fieldsize; y++) {
				if (region[x][y] == -1) { // new region
					region_size = 0;
					perimeter = 0;
					explore_region(x, y, field[x][y], region_id);
					answer1 += region_size * perimeter;
					r_size[region_id] = region_size;
					corners[region_id] = 0;
					region_id++;

				}
			}
		}
		cout << "Final answer for part 1 is " << answer1 << "\n";

		for (int x = 0; x <= fieldsize; x++) {// For each intersection of tiles, check for corners
			for (int y = 0; y <= fieldsize; y++) {
				int A[4];
				A[0] = region[x][y];
				A[1] = region[x + 1][y];
				A[2] = region[x][y + 1];
				A[3] = region[x + 1][y + 1];
				map<int, int> m;
				for (int i = 0; i < 4; i++) {
					if (m.count(A[i]) == 0) { //count how many times the region occurs in this 2x2 area.
						m[A[i]] = 1;
					}
					else {
						m[A[i]]++;
					}
				}
				for (auto const& x : m)
				{
					int key = x.first;
					int count = x.second;
					if(count == 1 || count == 3){ // a single corner exists for this region
						corners[key]++;
					}
					else if (count == 2 && ((key == A[0] && key == A[3]) || (key == A[1] && key == A[2]))) { //diagonal touching
						corners[key] += 2;
					}
				}
			}
		}
		for (int i = 1; i < region_id; i++) {
			answer2 += r_size[i] * corners[i]; // Note that number of sides == number of corners
		}

		cout << "Final answer for part 2 is " << answer2 << "\n";
	}

	else {
		cout << "can't find file?\n";
	}
}