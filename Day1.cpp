#include <iostream>
#include <algorithm>    
#include <cmath>    
#include <fstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


using namespace std;

int main(int argc, char* argv[])
{
	ifstream infile;
	infile.open("data.txt");

	if (infile.is_open())
	{
		int num;
		int answer1 = 0;
		int answer2 = 0;
		vector<int> left;
		vector<int> right;
		while (infile >> num)
		{
			left.push_back(num);
			infile >> num;
			right.push_back(num);
		}
		sort(left.begin(), left.end());
		sort(right.begin(), right.end());
		for (int i = 0; i < left.size(); i++) {
			int difference = abs(left[i] - right[i]);
			answer1 += difference;
			int count = 0;
			for (int j = 0; j < right.size(); j++){
				if (right[j] == left[i]) {
					count++;
				}
			}
			answer2 += count * left[i];
		}
		cout << "Final answer for part 1 is " << answer1 << "\n";
		cout << "Final answer for part 2 is " << answer2 << "\n";
	}
	else {

		cout << "can't find file?\n";
	}



}