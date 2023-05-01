#pragma once
class Queue
{
	class Node {
	public:
		int data;
		Node* next;
	};
	Node* head;
	Node* tail;
	int size;
public:
	Queue();
	void enqueue(int data);
	int dequeue();
	int getSize();
	bool isEmpty();
	~Queue();
};

