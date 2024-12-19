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

vector<string> patterns;
map<string, long long> memo;

long long find_design(string design) {
	if (design.empty()) {
		return 1;
	}
	map<string, long long>::iterator iter = memo.find(design);
	if (iter != memo.end())  // substring has been previously processed
	{
		return iter->second;
	}
	long long results = 0;
	for (int i = 0; i < patterns.size(); i++) {
		if (patterns[i].size() > design.size()) {
			continue;
		}
		string first = design.substr(0, patterns[i].size());

		if (first.compare(patterns[i]) == 0) { //pattern fits
			string second = design.substr(patterns[i].size(), 9999999);
			results += find_design(second);
		}
	}
	memo[design] = results;
	return results;
}

int main(int argc, char* argv[])
{
	ifstream infile;
	infile.open("data.txt");

	if (infile.is_open())
	{
		string s;
		int answer1 = 0;
		long long answer2 = 0;
		infile >> s;
		while (s.back() == ',') {
			s.pop_back();
			patterns.push_back(s);
			infile >> s;
		}
		patterns.push_back(s); // last pattern has no comma
		while (infile >> s) {
			long long result = find_design(s);
			if (result > 0) {
				answer1++;
			}
			answer2 += result;
		}
		
		cout << "Final answer for part 1 is " << answer1 << "\n";
		cout << "Final answer for part 2 is " << answer2 << "\n";
	}
	else {

		cout << "can't find file?\n";
	}
}

