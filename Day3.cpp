#include <iostream>
#include <algorithm>    
#include <cmath>    
#include <fstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <regex>


using namespace std;

int main(int argc, char* argv[])
{
	ifstream infile;
	infile.open("data.txt");

	if (infile.is_open())
	{
		string s;
		long long answer1 = 0;
		long long answer2 = 0;
		bool enabled = true;
		regex mul("^mul\\((\\d+),(\\d+)\\).*");
		regex re_do("^do\\(\\).*");
		regex dont("^don't\\(\\).*");
		smatch match;
		while (infile >> s) {
			for (int i = 0; i < s.size(); i++) {
				string sub = s.substr(i, 15);
				if (regex_search(sub, match, re_do) == true) {
					enabled = true;
				}
				else if (regex_search(sub, match, dont) == true) {
					enabled = false;
				}
				else if (regex_search(sub, match, mul) == true) {
					long long n1 = stoll(match.str(1));
					long long n2 = stoll(match.str(2));
					answer1 += n1 * n2;
					if (enabled) {
						answer2 += n1 * n2;
					}
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
