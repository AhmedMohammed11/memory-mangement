/**
* MemoryManagement.cpp
*/
#include "MemoryManagement.h"
using namespace std;

MemoryManagement::MemoryManagement() {
	Block *pb = new Block;
	pb->occupied = true;
	pb->type = OS;
	pb->size = 28;
	pb->processID = 0;
	pb->next = NULL;

	totalMemory = pb;

	pb = new Block;
	pb->occupied = false;
	pb->type = UserPrograms;
	pb->size = 100;
	pb->processID = -1;
	pb->next = NULL;

	totalMemory->next = pb;

	processIDCounter = 0;
	activeProcessCount = 0;
}

MemoryManagement::~MemoryManagement() {
	Block *pmm;
	while (totalMemory != NULL) {
		pmm = totalMemory->next;
		delete totalMemory;
		totalMemory = pmm;
	}
}


int MemoryManagement::loadProcess(Process p) {
	Block *pb, *prev = totalMemory, *pmm = totalMemory->next;
	bool found = false;
	// find the first available memory
	while (pmm != NULL) {
		if (!pmm->occupied && pmm->size >= p.size) {
			found = true;
			break;
		}
		prev = pmm;
		pmm = pmm->next;
	}

	if (!found)
		return -1;

	// create new block to be occupied by the process
	pb = new Block;
	pb->type = UserPrograms;
	pb->occupied = true;
	pb->size = p.size;
	pb->processID = p.id;
	pb->next = pmm;
	// decrease the non-occupied node by the process size
	pmm->size -= p.size;
	// append the block to the list, just before the empty node
	prev->next = pb;

	activeProcessCount++;

	return p.id;
}


void MemoryManagement::unloadProcess(int id) {
	Block *prev, *pmm = totalMemory;
	int ps;
	while (pmm != NULL) {
		// at least will be on second node to make sure not to edit the os node
		prev = pmm;
		pmm = pmm->next;

		if (pmm->processID == id) {
			ps = pmm->size;
			// reserve the size as empty
			// add the size to prev node if is not occupied
			if (prev->type == UserPrograms && !prev->occupied)
				prev->size += ps;
			// add the size to next node if is not occupied
			else if (pmm->next && !pmm->next->occupied)
				pmm->next->size += ps;
			// create new empty non-occupied node and make it the prev node
			else {
				Block *tmp = new Block;
				tmp->occupied = false;
				tmp->type = UserPrograms;
				tmp->processID = -1;
				tmp->size = ps;
				tmp->next = pmm;
				prev->next = tmp;
				prev = tmp;
			}

			// remove the process from the memory
			prev->next = pmm->next;
			delete pmm;
			pmm = prev->next;
			activeProcessCount--;
			break;
		}
	}

	// merge two nodes if is empty
	if (prev->type == UserPrograms && !prev->occupied && pmm && !pmm->occupied) {
		prev->size += pmm->size;
		prev->next = pmm->next;
		delete pmm;
	}
}


int MemoryManagement::_countDigits(int num) {
	int count = 0;
	if (num == 0)
		return 1;

	while (num) {
		count++;
		num /= 10;
	}
	return count;
}

void MemoryManagement::_printTopBottom() {
	Block *pmm;
	int c, i;
	cout << "+";
	for (pmm = totalMemory; pmm; pmm = pmm->next) {
		c = _countDigits(pmm->size) + 2;
		for (i = 0; i < c; i++)
			cout << "-";

		cout << "+";
	}
	cout << endl;
}

void MemoryManagement::print() {
	Block *pmm;
	int c, i;
	// print top line
	_printTopBottom();
	// print top symbol if occupied
	cout << "|";
	for (pmm = totalMemory; pmm; pmm = pmm->next) {
		c = _countDigits(pmm->size) + 2;
		for (i = 0; i < c; i++)
			cout << (pmm->occupied ? "#" : " ");

		cout << "|";
	}
	cout << endl;
	// print middle line
	cout << "|";
	for (pmm = totalMemory; pmm; pmm = pmm->next) {
		cout << " " << pmm->size << " |";
	}
	cout << endl;
	// print bottom line
	_printTopBottom();
}

