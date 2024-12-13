#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <sstream>
#include <algorithm> 



using namespace std;


bool attempt_operators(vector<long long> v, int index, long long value, long long test_value) {
	if (value > test_value) {
		return false;
	}
	if (index == v.size()) {
		return value == test_value;
	}
	return attempt_operators(v, index + 1, value * v[index], test_value) || attempt_operators(v, index + 1, value + v[index], test_value);
}



bool attempt_concatenation(vector<long long> v, int index, long long value, long long test_value) {
	if (value > test_value) {
		return false;
	}
	if (index == v.size()) {
		return value == test_value;
	}
	string s1 = to_string(value);
	string s2 = to_string(v[index]);
	string concat = s1 + s2;
	long long concat_value = stoll(concat);
	return
		attempt_concatenation(v, index + 1, concat_value, test_value) ||
		attempt_concatenation(v, index + 1, value * v[index], test_value) ||
		attempt_concatenation(v, index + 1, value + v[index], test_value);
}


int main(int argc, char* argv[])
{
	ifstream infile;
	infile.open("data.txt");

	if (infile.is_open())
	{
		string s;
		long long answer1 = 0;
		long long answer2 = 0;
		while (getline(infile, s)) {
			stringstream ss(s);
			vector<long long> v;
			long long n;
			ss >> s;
			s.pop_back();
			long long test_value = stoll(s);
			while (ss >> n) {
				v.push_back(n);
			}
			if (attempt_operators(v, 1, v[0], test_value)) {
				answer1 += test_value;
				answer2 += test_value;
			}
			else if (attempt_concatenation(v, 1, v[0], test_value)) {
				answer2 += test_value;
			}
		}

		cout << "Final answer for part 1 is " << answer1 << "\n";
		cout << "Final answer for part 2 is " << answer2 << "\n";
	}
	else {

		cout << "can't find file?\n";
	}



}