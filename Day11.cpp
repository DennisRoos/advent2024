#include <iostream>
#include <algorithm>    
#include <cmath>    
#include <fstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

map<long long, long long> stones;
map<long long, long long> change;

void add_to_change(long long key, long long value) {
	if (change.find(key) != change.end()) { //key is already in map
		change[key] += value;
	}
	else {
		change[key] = value;
	}
	return;
}

void update_stones(long long key) {
	if (stones.find(key) != stones.end()) { //key is already in map
		stones[key] += change[key];
	}
	else {
		stones[key] = change[key];
	}
	return;
	
}

int main(int argc, char* argv[]) {
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		long long n;
		long long answer = 0;
		while (infile >> n) {
			stones[n] = 1;  // Assumes all starting stones are unique
		}

		for (int blinks = 1; blinks <= 75; blinks++) { //blink 25 times
			for (auto const& x : stones)
			{
				long long key = x.first;
				long long number = x.second;
				if (number != 0) {
					string s = to_string(key);
					if (key == 0) {
						add_to_change(0, -number);
						add_to_change(1, number);
					}
					else if (s.size() % 2 == 0) { //even number of digits
						string first = s.substr(0, s.size() / 2);
						string second = s.substr((s.size() / 2), s.size() / 2);
						add_to_change(key, -number);
						add_to_change(stoll(first), number);
						add_to_change(stoll(second), number);
					}
					else {
						add_to_change(key, -number);
						add_to_change(key * 2024, number);
					}
				}
			}
			for (auto const& x : change) {
				long long key = x.first;
				update_stones(key);
				answer += stones[key];
				change[key] = 0;
			}
			if (blinks == 25) {
				cout << "After 25 blinks there are " << answer << " stones" << endl;
			}
			else if (blinks == 75) {
				cout << "After 75 blinks there are " << answer << " stones" << endl;
			}
			answer = 0;
		}

	}

	else {
		cout << "can't find file?\n";
	}
}