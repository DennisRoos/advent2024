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
char field[140][140];


int check_xmas(string s) {
	if (s.compare("XMAS") == 0 || s.compare("SAMX") == 0) {
		return 1;
	}
	return 0;
}


int find_horizontal(int x, int y) {
	if (x < fieldsize - 3) {
		string s = string() + field[x][y] + field[x + 1][y] + field[x + 2][y] + field[x + 3][y];
		return check_xmas(s);
	}
	return 0;
}


int find_vertical(int x, int y) {
	if (y < fieldsize - 3) {
		string s = string() + field[x][y] + field[x][y + 1] + field[x][y + 2] + field[x][y + 3];
		return check_xmas(s);
	}
	return 0;
}


int find_diagonal_1(int x, int y) {
	if (y < fieldsize - 3 && x < fieldsize - 3) {
		string s = string() + field[x][y] + field[x + 1][y + 1] + field[x + 2][y + 2] + field[x + 3][y + 3];
		return check_xmas(s);
	}
	return 0;
}

int find_diagonal_2(int x, int y) {
	if (y < fieldsize - 3 && x > 2) {
		string s = string() + field[x][y] + field[x - 1][y + 1] + field[x - 2][y + 2] + field[x - 3][y + 3];
		return check_xmas(s);
	}
	return 0;
}

bool find_mas(string s) {
	return s.compare("MAS") == 0 || s.compare("SAM") == 0;
}


int findcross(int x, int y) {
	string s1 = string() + field[x - 1][y - 1] + field[x][y] + field[x + 1][y + 1];
	string s2 = string() + field[x - 1][y + 1] + field[x][y] + field[x + 1][y - 1];
	if (find_mas(s1) && find_mas(s2)) {
		return 1;
	}
	return 0;
}


int main(int argc, char* argv[]){
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
			}
			y++;
		}
		for (int x = 0; x < fieldsize; x++) {
			for (int y = 0; y < fieldsize; y++) {
				answer1 += find_horizontal(x, y) + find_diagonal_1(x, y) + find_diagonal_2(x, y) + find_vertical(x, y);
				if (field[x][y] == 'A' && x > 0 && x < fieldsize - 1 && y > 0 && y < fieldsize - 1) {
					answer2 += findcross(x, y);
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