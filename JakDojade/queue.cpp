#include "queue.h"

Queue::Queue()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

void Queue::enqueue(int data)
{
    Node* node = new Node();
    node->data = data;
    node->next = nullptr;

    if (head == nullptr) {
        head = node;
        tail = node;
    }
    else {
        tail->next = node;
        tail = node;
    }

    size++;
}

int Queue::dequeue()
{
    int data = head->data;
    Node* temp = head;
    head = head->next;
    delete temp;

    size--;

    return data;
}

int Queue::getSize()
{
    return size;
}

bool Queue::isEmpty()
{
    return size==0;
}

Queue::~Queue()
{
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}
