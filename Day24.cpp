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

struct gate {
	string input1;
	string input2;
	string output;
	string op;
};

map<string, bool> values;
vector<gate> gates;
vector<string> v;

int starts_with(string s, char c) {
	if (s[0] == c) {
		return stoi(s.substr(1, 2));
	}
	return -1;
}

gate find_gate_with_output(string s) {
	for (int i = 0; i < gates.size(); i++) {
		if (gates[i].output.compare(s) == 0) {
			return gates[i];
		}
	}
}

void print_gate(gate g) {
	cout << "The gate '" << g.input1 << " " << g.op << " " << g.input2 << " => " << g.output << "' ";
 }

int main(int argc, char* argv[]) {
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string s;
		long long answer1 = 0;
		string answer2 = "";
		while (getline(infile, s)) {
			if (s.empty()) {
				break;
			}
			string variable = s.substr(0, 3);
			bool v = (s[5] == '1');
			values[variable] = v;
		}
		while (getline(infile, s)) {
			stringstream ss(s);
			string input1;
			string input2;
			string output;
			string op;
			ss >> input1;
			ss >> op;
			ss >> input2;
			ss >> s;
			ss >> output;
			gate g;
			g.input1 = input1;
			g.input2 = input2;
			g.op = op;
			g.output = output;
			gates.push_back(g);
		}

		bool success = true;
		while (success) {
			success = false;
			for (int i = 0; i < gates.size(); i++) {
				gate g = gates[i];
				map<string, bool>::iterator outp = values.find(g.output);
				if (outp == values.end()) { // this gate hasn't fired yet
					map<string, bool>::iterator iter1 = values.find(g.input1);
					map<string, bool>::iterator iter2 = values.find(g.input2);
					if (iter1 != values.end() && iter2 != values.end()) // input values are available
					{
						bool out;
						if (g.op == "OR") {
							out = iter1->second || iter2->second;
						}
						else if (g.op == "AND") {
							out = iter1->second && iter2->second;
						}
						else { // XOR
							out = iter1->second != iter2->second;
						}
						values[g.output] = out;
						success = true;
						if (g.output[0] == 'z' && out) {
							long long num = stoll(g.output.substr(1, 2));
							answer1 += pow(2, num);
						}
					}
				}
			}
		}
		for (int i = 0; i < gates.size(); i++) {
			gate g = gates[i];
			if (g.op == "XOR") {
				if ((starts_with(g.input1, 'x') != -1) || (starts_with(g.input1, 'y') != -1) && (starts_with(g.input2, 'x') != -1) || (starts_with(g.input2, 'y') != -1)) {
					bool match = false;
					for (int j = 0; j < gates.size(); j++) {
						gate h = gates[j];
						if (h.op == "XOR" && (h.input1.compare(g.output) == 0 || h.input2.compare(g.output) == 0)) {
							match = true;
						}
					}
					if (g.output.compare("z00") != 0 && !match) {
						print_gate(g);
						cout << " is a starting XOR gate with no XOR gate following it" << endl;
						v.push_back(g.output);
					}
				}
				else if (starts_with(g.output, 'z') == -1) {
					print_gate(g);
					cout << " should have a Zxx output " << endl;
					v.push_back(g.output);
				}
			}
			if (g.op != "XOR" && starts_with(g.output, 'z') != -1 && starts_with(g.output, 'z') != 45) {
				print_gate(g);
				cout << " is a gate that outputs Z but isn't XOR!" << endl;
				v.push_back(g.output);
			}
			else if (g.op == "AND") {
				bool match = false;
				for (int j = 0; j < gates.size(); j++) {
					gate h = gates[j];
					if (h.op == "OR" && (h.input1.compare(g.output) == 0 || h.input2.compare(g.output) == 0)) {
						match = true;
					}
				}
				if (!match && starts_with(g.input1, 'x') != 0 && starts_with(g.input2, 'x') != 0) {
					print_gate(g);
					cout << " is an AND gate not followed by an OR gate" << endl;
					v.push_back(g.output);
				}

			}




		}
		sort(v.begin(), v.end());
		for (int i = 0; i < v.size(); i++) {
			answer2 += v[i] + ",";
		}
		answer2.pop_back();
		cout << "Final answer for part 1 is " << answer1 << "\n";
		cout << "Final answer for part 2 is " << answer2 << "\n";
	}

	else {
		cout << "can't find file?\n";
	}
}
