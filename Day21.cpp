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


string directional[5][5] = { // 0 = A, 1 = ^, 2 = >, 3 = v, 4 = <
	{{"A"}, {"<A"},{"vA"},{"<vA"},{"v<<A"} },
	{{ ">A" }, { "A" }, { "v>A" }, { "vA" }, { "v<A" } },
	{{ "^A" }, { "<^A" }, { "A" }, { "<A" }, { "<<A" } },
	{{ "^>A" }, { "^A" }, { ">A" }, { "A" }, { "<A" } },
	{{ ">>^A" }, { ">^A" }, { ">>A" }, { ">A" }, { "A" } },
};
string keypad[11][11];
map<string, long long> memo[26];

int keypadX[11] = { 1, 0, 1, 2, 0, 1, 2, 0, 1, 2, 2 };
int keypadY[11] = { 3, 2, 2, 2, 1, 1, 1, 0, 0, 0, 3 };

void find_keypad_string(int i, int j) {
	string s = "";
	if (keypadY[i] == 3 && keypadX[j] == 0) {
		s = s + string(keypadY[i] - keypadY[j], '^');
		s = s + string(keypadX[i] - keypadX[j], '<');
	}
	else if (keypadY[j] == 3 && keypadX[i] == 0) {
		s = s + string(keypadX[j] - keypadX[i], '>');
		s = s + string(keypadY[j] - keypadY[i], 'v');
	}
	else {
		if (keypadX[i] > keypadX[j]) { // move left
			s = s + string(keypadX[i] - keypadX[j], '<');
			if (keypadY[i] > keypadY[j]) {
				s = s + string(keypadY[i] - keypadY[j], '^');
			}
			if (keypadY[j] > keypadY[i]) {
				s = s + string(keypadY[j] - keypadY[i], 'v');
			}
		}
		else {
			if (keypadY[j] > keypadY[i]) {
				s = s + string(keypadY[j] - keypadY[i], 'v');
			}
			if (keypadY[i] > keypadY[j]) {
				s = s + string(keypadY[i] - keypadY[j], '^');
			}
			s = s + string(keypadX[j] - keypadX[i], '>');
			
		}
	}
	s = s + "A";
	keypad[i][j] = s;
}

int convert_char_keypad(char c) {
	if (c == 'A') {
		return 10;
	}
	else return c - '0';
}

int convert_char_dir(char c) {
	if (c == 'A') {
		return 0;
	}
	if (c == '^') {
		return 1;
	}
	if (c == '>') {
		return 2;
	}
	if (c == 'v') {
		return 3;
	}
	return 4;
}

long long expand(string s, int level, int max_level) {
	if (level == max_level) {
		return s.size();
	}
	stringstream ss(s);
	long long total = 0;
	while (getline(ss, s, 'A')) {
		s += "A";
		map<string, long long>::iterator iter = memo[level].find(s);
		if (iter != memo[level].end())  // substring has been previously processed
		{
			total += iter->second;
		}
		else {
			long long subtotal = 0;
			int first = 0;
			for (long long i = 0; i < s.size(); i++) {
				int second = convert_char_dir(s[i]);
				string next_string = directional[first][second];
				subtotal += expand(next_string, level + 1, max_level);
				first = second;
			}
			memo[level][s] = subtotal;
			total += subtotal;
		}
	}
	return total;
}

int main(int argc, char* argv[]) {
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string s;
		long long answer1 = 0;
		long long answer2 = 0;
		for (int i = 0; i < 11; i++) {
			for(int j = 0; j < 11; j++) {
				find_keypad_string(i, j);
				//cout << i << " -> " << j << ": " << keypad[i][j] << endl;
			}
		}
		while (infile >> s){
			string robot = "";
			int first = 10;
			for (int i = 0; i < s.size(); i++) {
				char c = s[i];
				int second = convert_char_keypad(c);
				robot += keypad[first][second];
				first = second;
			}
			long long length = expand(robot, 23, 25);
			s.pop_back();
			long long numeric_part = stoll(s);
			answer1 += length * numeric_part;
			length = expand(robot, 0, 25);
			answer2 += length * numeric_part;
		}

		cout << "Final answer for part 1 is " << answer1 << "\n";
		cout << "Final answer for part 2 is " << answer2 << "\n";
	}

	else {
		cout << "can't find file?\n";
	}
}

// 154115708116294 correct p2 for example
