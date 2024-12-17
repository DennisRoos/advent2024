#include <iostream>
#include <algorithm>    
#include <cmath>    
#include <fstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

long long A;
long long B;
long long C;
long long ip;
vector<long long> v;

long long combo(long long operand) {
	if (operand <= 3) {
		return operand;
	}
	else if (operand == 4) {
		return A;
	}
	else if (operand == 5) {
		return B;
	}
	else if (operand == 6) {
		return C;
	}
}

string run_program(bool part2) {
	string output = "";
	ip = 0;
	long long program_size = v.size();
	long long two = 2;
	long long eight = 8;
	while (ip < program_size) {
		long long opcode = v[ip];
		long long operand = v[ip + 1];

		if (opcode == 0) { // adv
			A = A / (pow(two, combo(operand)));
		}
		else if (opcode == 1) { // bxl
			B = B ^ operand;
		}
		else if (opcode == 2) { // bst
			B = combo(operand) % eight;
		}
		else if (opcode == 3) { // jnz
			if(A != 0){
				ip = operand - 2;  // Compensate for incrementing 2 later
			}
		}
		else if (opcode == 4) { // bxc
			B = B ^ C;
		}
		else if (opcode == 5) { // out
			long long out = combo(operand) % eight;
			if (part2) {  // when doing part 2, exit upon outputting
				return to_string(out);
			}
			output += to_string(out) + ",";
		}
		else if (opcode == 6) { // bdv
			B = A / (pow(two, combo(operand)));;
		}
		else if (opcode == 7) { // cdv
			C = A / (pow(two, combo(operand)));;
		}
		ip += 2;
	}
	output.pop_back();
	return output;
}

long long answer2;

void generate_A(long long i, long long currentA) {
	for (long long j = 0; j < 8; j++) {
		A = currentA + j;
		string temp = run_program(false);
		A = currentA + j;
		ip = 0;
		long long result = stoll(run_program(true));
		if (result == v[i]) {
			if (i == 0) {
				answer2 = min(answer2, currentA + j);
				return;
			}
			long long newA = (currentA + j) * 8;
			generate_A(i-1, newA);
		}
	}
	return;
}

int main(int argc, char* argv[]) {
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string s;
		string program;
		string answer1;
		answer2 = 1399999999999999;
		ip = 0;
		infile >> s;
		infile >> s;
		infile >> A;
		infile >> s;
		infile >> s;
		infile >> B;
		infile >> s;
		infile >> s;
		infile >> C;
		infile >> s;
		infile >> program;
		long long n;
		stringstream ss(program);
		while (getline(ss, s, ',')) {
			n = stoll(s);
			v.push_back(n);
		}
		answer1 = run_program(false);
		cout << "Final answer for part 1 is " << answer1 << "\n";

		generate_A(v.size() - 1, 0);
		A = answer2;
		string output_program = run_program(false);
		if (output_program.compare(program) != 0) {
			cout << "Something went wrong, the output " << output_program << " is not the same as " << program << endl;
		}
		else {
			cout << "Final answer for part 2 is " << answer2 << " which outputs " << output_program << "\n";
		}
	}

	else {
		cout << "can't find file?\n";
	}
}


// 321369175486 too low
// 20567627247063 too low