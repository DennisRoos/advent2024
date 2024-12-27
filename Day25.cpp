#include <iostream>
#include <algorithm>    
#include <cmath>    
#include <fstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>

using namespace std;

vector<vector<int>> locks;
vector<vector<int>> keys;

int main(int argc, char* argv[]) {
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string s;
		int answer1 = 0;
		while (infile >> s) {
			if (s[0] == '#') { //lock
				vector<int> lock;
				for (int i = 0; i < 5; i++) {
					lock.push_back(0);
				}
				for (int j = 0; j < 6; j++) {
					infile >> s;
					for (int i = 0; i < 5; i++) {
						if (s[i] == '#') {
							lock[i]++;
						}
					}
				}
				locks.push_back(lock);
			}
			else { // key
				vector<int> key;
				for (int i = 0; i < 5; i++) {
					key.push_back(5);
				}
				for (int j = 0; j < 6; j++) {
					infile >> s;
					for (int i = 0; i < 5; i++) {
						if (s[i] == '.') {
							key[i]--;
						}
					}
				}
				keys.push_back(key);
			}
		}
		for (int l = 0; l < locks.size(); l++) {
			vector<int> lock = locks[l];
			for (int k = 0; k < keys.size(); k++) {
				bool fit = true;
				vector<int> key = keys[k];
				for (int i = 0; i < 5; i++) {
					if (key[i] + lock[i] >= 6) {
						fit = false;
					}
				}
				if (fit) {
					answer1++;
				}
			}
		}


		cout << "Final answer for part 1 is " << answer1 << "\n";
	}

	else {
		cout << "can't find file?\n";
	}
}
