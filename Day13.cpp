#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <sstream>
#include <algorithm> 
using namespace std;



long long cross_multiplication(long long x1, long long x2, long long y1, long long y2, long long c1, long long c2) {
	long long A = (c1 * y2 - c2 * x2) / (x1 * y2 - x2 * y1);
	long long B = (c2 * x1 - c1 * y1) / (x1 * y2 - x2 * y1);
	if (A * x1 + B * x2 == c1 && A * y1 + B * y2 == c2) { // integer solution
		return 3 * A + B;
	}
	else return 0;
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
		regex button("Button [A-Z]: X\\+(\\d+), Y\\+(\\d+)");
		regex prize("Prize: X=(\\d+), Y=(\\d+)");
		smatch match;
		while (getline(infile, s)) {
			long long x1;
			long long x2;
			long long y1;
			long long y2;
			long long c1;
			long long c2;
			if (regex_search(s, match, button) == true) {
				x1 = stoll(match.str(1));
				y1 = stoll(match.str(2));
			}
			getline(infile, s);
			if (regex_search(s, match, button) == true) {
				x2 = stoll(match.str(1));
				y2 = stoll(match.str(2));
			}
			getline(infile, s);
			if (regex_search(s, match, prize) == true) {
				c1 = stoll(match.str(1));
				c2 = stoll(match.str(2));
			}
			getline(infile, s);
			answer1 += cross_multiplication(x1, x2, y1, y2, c1, c2);
			c1 += 10000000000000;
			c2 += 10000000000000;
			answer2 += cross_multiplication(x1, x2, y1, y2, c1, c2);
		}

		cout << "Final answer for part 1 is " << answer1 << "\n";
		cout << "Final answer for part 2 is " << answer2 << "\n";
	}
	else {

		cout << "can't find file?\n";
	}



}