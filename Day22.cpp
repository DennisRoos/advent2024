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

using namespace std;

int price[1540][19][19][19][19];

int num_buyers;

long long mix_and_prune(long long a, long long b) {
	return (a ^ b) % 16777216;
}

int main(int argc, char* argv[]) {
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		long long secret;
		long long answer1 = 0;
		long long answer2 = 0;
		num_buyers = 0;
		for (int i = 0; i < 1540; i++) {
			for (int a = 0; a < 19; a++) {
				for (int b = 0; b < 19; b++) {
					for (int c = 0; c < 19; c++) {
						for (int d = 0; d < 19; d++) {
							price[i][a][b][c][d] = -1;
						}
					}
				}
			}
		}

		while (infile >> secret)
		{
			vector<int> C;
			vector<int> P;
			int old_bananas = secret % 10;

			secret = mix_and_prune(secret, secret * 64);
			secret = mix_and_prune(secret, secret / 32);
			secret = mix_and_prune(secret, secret * 2048);
			int new_bananas = secret % 10;
			int diff1 = (new_bananas - old_bananas) + 9;
			old_bananas = new_bananas;

			secret = mix_and_prune(secret, secret * 64);
			secret = mix_and_prune(secret, secret / 32);
			secret = mix_and_prune(secret, secret * 2048);
			new_bananas = secret % 10;
			int diff2 = (new_bananas - old_bananas) + 9;
			old_bananas = new_bananas;

			secret = mix_and_prune(secret, secret * 64);
			secret = mix_and_prune(secret, secret / 32);
			secret = mix_and_prune(secret, secret * 2048);
			new_bananas = secret % 10;
			int diff3 = (new_bananas - old_bananas) + 9;
			old_bananas = new_bananas;


			for (int i = 3; i < 2000; i++) {
				secret = mix_and_prune(secret, secret * 64);
				secret = mix_and_prune(secret, secret / 32);
				secret = mix_and_prune(secret, secret * 2048);
				new_bananas = secret % 10;
				int diff4 = (new_bananas - old_bananas) + 9;
				old_bananas = new_bananas;
				if (price[num_buyers][diff1][diff2][diff3][diff4] == -1) {
					price[num_buyers][diff1][diff2][diff3][diff4] = new_bananas;
				}
				diff1 = diff2;
				diff2 = diff3;
				diff3 = diff4;
			}
			answer1 += secret;
			num_buyers++;
		}
		cout << "Final answer for part 1 is " << answer1 << "\n";

		int best = 0;
		for (int a = 0; a < 19; a++) {
			for (int b = 0; b < 19; b++) {
				for (int c = 0; c < 19; c++) {
					for (int d = 0; d < 19; d++) {
						int result = 0;
						for (int i = 0; i < num_buyers; i++) {
							int p = price[i][a][b][c][d];
							if (p != -1) {
								result += p;
							}
						}
						if (result > best) {
							best = result;
						}
					}
				}
			}
		}
		answer2 = best;
		cout << "Final answer for part 2 is " << answer2 << "\n";
	}

	else {
		cout << "can't find file?\n";
	}
}