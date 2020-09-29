/**
* main.cpp
*/
#include "MemoryManagement.h"
#include "QueueLL.h"
#include "QueueLL.cpp"

using namespace std;

int main() {
	MemoryManagement mm;
	QueueLL<Process> Q;
	Process pr;
	int i, j, r, x,
		// ready processes sizes
		readyProcesses[] = { 32, 4, 8, 8, 18, 6, 16, 18, 30, 4, 24, 32, 9, 18 };

	for (i = 0; i < 14; i++) {
		pr.id = i + 1;
		pr.size = readyProcesses[i];
		pr.loaded = false;
		Q.enqueue(pr);
	}

	cout << "Memory is initialized: " << endl;
	mm.print();

	// load ready process to memory until memory is full
	for (i = 0; i < 14; i++) {
		pr = Q.queueFront();
		if (!pr.loaded) {
			x = mm.loadProcess(pr);
		}
			
		
		// set the loaded process to 0 to not be load again
		if (x > -1) {
			Q.dequeue(pr);
			pr.loaded = true;
			Q.enqueue(pr);
		}
			
	}

	cout << endl << "Some ready process is loaded: " << endl;
	mm.print();

	// remove at least 3 process to free the memory for another process to be loaded
	for (i = 0, r = 0; i < 14 && r < 3; i++) {
		Q.dequeue(pr);
		if (pr.loaded) {
			mm.unloadProcess(pr.id);
			r++;
			pr.loaded = false;
		}
		Q.enqueue(pr);

		// loop to load ready process in the freed memory location
		for (j = 0; j < 14; j++) {
			Q.dequeue(pr);
			if (!pr.loaded) {
				x = mm.loadProcess(pr);
				if (x > -1) {
					pr.loaded = true;
				}
			}
			Q.enqueue(pr);
		}
	}

	cout << endl << "Some ready process is unloaded to free memory and others is loaded: " << endl;
	mm.print();


	cout << endl;
	system("pause");
	return 0;
}