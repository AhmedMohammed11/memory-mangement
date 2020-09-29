#ifndef A_QUEUE_LL_H
#define A_QUEUE_LL_H
#include <iostream>

template <typename T>
class QueueLL {
public:
	QueueLL();
	~QueueLL();

	bool isEmpty();

	int getLength();

	void enqueue(T data);
	void dequeue(T &data);

	T queueFront() const;

private:
	struct QueueNode {
		T data;
		QueueNode *next;
	} *front, *rear;

	int length;
};

#endif //!A_QUEUE_LL_H