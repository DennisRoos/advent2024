#include <iostream>
#include <algorithm>    
#include <cmath>    
#include <fstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

struct block {
	long long id;
	long long length;
	long long index;
	block* next;
	block* prev;
};

void defragment(long long id, long long length, block* initial) {
	block* current = initial;
	while (length > 0) {
		while (current->id != -1) {
			current = current->next;
		}
		// hit the leftmost empty block
		if (length >= current->length) {// empty block completely filled by data
			current->id = id;
			length -= current->length;
			current = current->next;
		}
		else { //empty block partially filled with data
			block* new_block = new block();
			new_block->id = id;
			new_block->length = length;
			new_block->index = current->index;
			current->index += length;
			current->length -= length;
			length = 0;
			current->prev->next = new_block;
			new_block->prev = current->prev;
			current->prev = new_block;
			new_block->next = current;
			current = current->next;
		}
	}
	return;
}


void defragment_2(long long id, long long length, block* initial) {
	block* current = initial;
	while (current->id != -1 || length > current->length) { // find a large enough empty block
		current = current->next;
	}
	//cout << id << ": " << current->index << "," << current->length << " " << current->id << endl;
	// hit the leftmost empty block that's big enough to fit the data
	if (length == current->length) {// block fits exactly
		current->id = id;
		current = current->next;
	}
	else { //empty block partially filled with data
		block* new_block = new block();
		new_block->id = id;
		new_block->length = length;
		new_block->index = current->index;
		current->index += length;
		current->length -= length;
		current->prev->next = new_block;
		new_block->prev = current->prev;
		current->prev = new_block;
		new_block->next = current;
		current = current->next;
	}
	return;
}

void print(block* cur) {
	while (cur != NULL) {
		string s;
		if (cur->id == -1) {
			s = string(cur->length, '.');
		}
		else {
			s = string(cur->length, char(cur->id + '0'));
		}
		cout << s;
		cur = cur->next;
	}
	cout << endl;
}

int main(int argc, char* argv[]) {
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string s;
		infile >> s;
		long long answer1 = 0;
		long long answer2 = 0;
		block* initial = new block();
		long long current_id = 0;
		long long current_index = 0;
		initial->id = current_id;
		initial->length = s[0] - '0';
		initial->index = 0;
		initial->prev = NULL;
		block* current = initial;

		for (int i = 1; i < s.size(); i += 2) {
			current_id++;
			current_index += current->length;
			block* empty = new block();
			empty->id = -1;
			empty->length = s[i] - '0';
			empty->index = current_index;
			empty->prev = current;
			current->next = empty;
			current = empty;
			current_index += current->length;
			block* new_block = new block();
			new_block->id = current_id;
			new_block->length = s[i+1] - '0';
			new_block->index = current_index;
			new_block->next = NULL;
			new_block->prev = empty;
			current->next = new_block;
			current = new_block;
		}
		current = initial;
		while (current->next != NULL) {
			current = current->next;
		}
		while (current != NULL) {
			if (current->id == -1) { // empty block
				current = current->prev;
			}
			else {
				long long length = current->length;
				long long id = current->id;
				current->id = -1;
				current = current->prev;
				defragment(id, length, initial);
				//print(initial);
			}
		}
		current = initial;
		while (current != NULL) {
			if (current->id != -1) {

				long long sum;
				sum = (current->index + current->index + current->length - 1) * (current->length) / 2;
				answer1 += sum * current->id;
			}
			current = current->next;
		}


		current_id = 0;
		current_index = 0;
		block* initial_2 = new block();
		initial_2->id = current_id;
		initial_2->length = s[0] - '0';
		initial_2->index = 0;
		initial_2->prev = NULL;
		current = initial_2;

		for (int i = 1; i < s.size(); i += 2) {
			current_id++;
			current_index += current->length;
			block* empty = new block();
			empty->id = -1;
			empty->length = s[i] - '0';
			empty->index = current_index;
			empty->prev = current;
			current->next = empty;
			current = empty;
			current_index += current->length;
			block* new_block = new block();
			new_block->id = current_id;
			new_block->length = s[i + 1] - '0';
			new_block->index = current_index;
			new_block->next = NULL;
			new_block->prev = empty;
			current->next = new_block;
			current = new_block;
		}
		current = initial_2;
		while (current->next != NULL) {
			current = current->next;
		}
		while (current != NULL) {
			if (current->id == -1) { // empty block
				current = current->prev;
			}
			else {
				long long length = current->length;
				long long id = current->id;
				current->id = -1;
				current = current->prev;
				defragment_2(id, length, initial_2);
				//print(initial);
			}
		}

		current = initial_2;
		while (current != NULL) {
			if (current->id != -1) {

				long long sum;
				sum = (current->index + current->index + current->length - 1) * (current->length) / 2;
				answer2 += sum * current->id;
			}
			current = current->next;
		}

		cout << "Final answer for part 1 is " << answer1 << "\n";
		cout << "Final answer for part 2 is " << answer2 << "\n";
	}

	else {
		cout << "can't find file?\n";
	}
}