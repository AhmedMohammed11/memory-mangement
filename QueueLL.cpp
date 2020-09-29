#include "QueueLL.h"
using namespace std;

template <typename T>
QueueLL<T>::QueueLL() {
	length = 0;
	front = NULL;
	rear = NULL;
}

template <typename T>
QueueLL<T>::~QueueLL() {
	QueueNode *ptr;
	while (front != NULL) {
		ptr = front;
		front = front->next;
		delete ptr;
	}
	front = NULL;
	rear = NULL;
}

template <typename T>
bool QueueLL<T>::isEmpty() {
	return length == 0;
}

template <typename T>
int QueueLL<T>::getLength() {
	return length;
}

template <typename T>
void QueueLL<T>::enqueue(T data) {
	QueueNode *ptr = new QueueNode;
	ptr->data = data;
	ptr->next = NULL;

	if (front == NULL) {
		front = ptr;
		rear = ptr;
	}
	else {
		rear->next = ptr;
		rear = ptr;
	}

	length++;
}

template <typename T>
void QueueLL<T>::dequeue(T &data) {
	if (front == NULL) {
		return;
	}
	data = front->data;
	QueueNode *ptr = front;
	front = front->next;
	delete ptr;
	length--;
}

template <typename T>
T QueueLL<T>::queueFront() const {
	if (front != NULL)
		return front->data;

	//return NULL;
}



