#include <iostream>
#include <algorithm>    
#include <cmath>    
#include <fstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>


using namespace std;


bool order[100][100];

int check_line(vector<int> v) {
	for (int i = 1; i < v.size(); i++) {
		for (int j = 0; j < i; j++) {
			if (order[v[i]][v[j]]) { // wrong order
				//cout << "Failure for " << v[j] << "," << v[i] << "\n";
				return 0;
			}
		}
	}
	//cout << "Add " << v[(v.size() - 1) / 2] << "\n";
	return v[(v.size() - 1) / 2];
}


bool sort_function(int i, int j) {
	return (order[i][j]);
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
		vector<int> left;
		vector<int> right;
		bool part1 = true;
		for (int i = 0; i < 100; i++) {
			for (int j = 0; j < 100; j++) {
				order[i][j] = false;
			}
		}
		while (part1)
		{
			getline(infile, s);
			if (s.empty()) {
				part1 = false;
			}
			else {
				stringstream ss(s);
				getline(ss, s, '|');
				int first = stoi(s);
				getline(ss, s, '|');
				int second = stoi(s);
				//cout << "Rule for " << first << "," << second << "\n";
				order[first][second] = true;
			}
		}

		while (getline(infile, s)) {
			stringstream ss(s);
			//cout << s << "\n";
			vector<int> v;
			while (getline(ss, s, ',')) {
				v.push_back(stoi(s));
			}
			int result = check_line(v);
			if (result != 0) {
				answer1 += result;
			}
			else {
				sort(v.begin(), v.end(), sort_function);
				answer2 += v[(v.size() - 1) / 2];
			}
			v.clear();
		}


		cout << "Final answer for part 1 is " << answer1 << "\n";
		cout << "Final answer for part 2 is " << answer2 << "\n";
	}
	else {
		cout << "can't find file?\n";
	}



}