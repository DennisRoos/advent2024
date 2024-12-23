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

bool connections[676][676];
int max_size = 0;
vector<int> best_vector;

int convert_string(string s) {
	char c1 = s[0];
	char c2 = s[1];
	return (26 * (c1 - 'a')) + (c2 - 'a');
}

string convert_int(int n) {
	int i1 = (n / 26);
	char c1 = i1 + 'a';
	int i2 = (n % 26);
	char c2 = i2 + 'a';
	string s = "";
	s += c1;
	s += c2;
	return s;
}

bool starts_with_t(int n, int start, int end) {
	return n >= start && n < end;
}

void find_cluster(vector<int> v, int n) {
	for (int i = n + 1; i < 676; i++) {
		bool b = true;
		for (int j = 0; j < v.size(); j++) {
			if (b && !connections[i][v[j]]) {
				if (convert_int(n) == "ka") {
				}
				b = false;
			}
		}
		if (b) {// connected to all members of cluster
			v.push_back(i);
		}
	}
	int cluster_size = v.size();
	if (cluster_size > max_size) {
		max_size = cluster_size;
		best_vector.clear();
		copy(v.begin(), v.end(), back_inserter(best_vector));
	}
	return;
}

int main(int argc, char* argv[]) {
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		for (int i = 0; i < 676; i++) {
			for (int j = 0; j < 676; j++) {
				connections[i][j] = false;
			}
		}
		string s;
		int answer1 = 0;
		string answer2;
		while (infile >> s) {
			stringstream ss(s);
			string first;
			string second;
			getline(ss, first, '-');
			getline(ss, second, '-');
			int n = convert_string(first);
			int m = convert_string(second);
			connections[n][m] = true;
			connections[m][n] = true;
		}
		int start_t = 26 * ('t' - 'a');
		int end_t = start_t + 26;
		for (int i = 0; i < 674; i++) {
			for (int j = i + 1; j < 675; j++) {
				if (connections[i][j]) {
					for (int k = j + 1; k < 676; k++) {
						if (connections[i][k] && connections[j][k]) {
							if (starts_with_t(i, start_t, end_t) ||
								starts_with_t(j, start_t, end_t) ||
								starts_with_t(k, start_t, end_t)){
								answer1++;
							}
							vector<int> v = { i, j, k };
							find_cluster(v, k);
							v.clear();
						}
					}
				}
			}
		}
		for (int i = 0; i < best_vector.size(); i++) {
			answer2 += convert_int(best_vector[i]) + ",";
		}
		answer2.pop_back();

		cout << "Final answer for part 1 is " << answer1 << "\n";
		cout << "Final answer for part 2 is " << answer2 << "\n";
	}

	else {
		cout << "can't find file?\n";
	}
}

// 154115708116294 correct p2 for example