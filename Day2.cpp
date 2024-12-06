#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <sstream>
#include <algorithm> 



using namespace std;

bool safe(int first, int second, bool increasing) {
	int diff;
	if (increasing) {
		diff = second - first;
	}
	else {
		diff = first - second;
	}
	return diff >= 1 && diff <= 3;
}



bool safe_set(vector<int> v) {
	bool increasing;
	if (v[0] < v[1]) {//incrementing
		increasing = true;
	}
	else {
		increasing = false;
	}
	for (int i = 0; i < v.size() - 1; i++) {
		if (!safe(v[i], v[i + 1], increasing)) {
			return false;
		}
	}
	return true;
}


bool one_fault(vector<int> v) {
	for (int i = 0; i < v.size(); i++) {
		vector<int> v2;
		v2.assign(v.begin(), v.end());
		v2.erase(v2.begin() + i);
		if (safe_set(v2)){
			return true;
		}
	}

	return false;
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
		while (getline(infile, s)) {
			stringstream ss(s);
			vector<int> v;
			int n;
			while (ss >> n) {
				v.push_back(n);
			}
			if (safe_set(v)) {
				answer1++;
				answer2++;
				cout << "Immediately safe " << s << "\n";
			}
			else if (one_fault(v)) {
				answer2++;
			}
		}
		
		cout << "Final answer for part 1 is " << answer1 << "\n";
		cout << "Final answer for part 2 is " << answer2 << "\n";
	}
	else {

		cout << "can't find file?\n";
	}



}