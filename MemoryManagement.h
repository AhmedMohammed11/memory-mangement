/**
 * MemoryManagement.h
 */
#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H
#include <iostream>

enum BlockType {
	OS = 1,
	UserPrograms = 2
};
struct Process {
	int id, size;
	bool loaded;
};


class MemoryManagement {
public:
	MemoryManagement();
	~MemoryManagement();

	int loadProcess(Process pr);
	void unloadProcess(int id);

	void print();

private:
	struct Block {
		bool occupied;
		int size, processID;
		BlockType type;
		Block *next;
	} *totalMemory;

	int processIDCounter, activeProcessCount;
	int _countDigits(int num);
	void _printTopBottom();
};

#endif // !MEMORY_MANAGEMENT_H
