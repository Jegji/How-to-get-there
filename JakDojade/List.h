#pragma once
#include "City.h"
template<typename T>
class List
{
	class Node {
	public:
		T* data;
		Node* next;
		Node* prev;
		Node(Node* prev, T* data);
		~Node();
	};
	Node* head;
	clock_t start = clock();
	Node* tail;
	int m_lng;
public:
	List();
	void insert(T* element);
	int lng()const;
	bool contains(T item);
	T* getById(int id);
	T* operator[] (int id);
	void erase();
	int getSize();
	double getTime();
	~List();
};

template<typename T>
inline List<T>::List()
{
	head = nullptr;
	tail = nullptr;
	m_lng = 0;
}

template<typename T>
inline void List<T>::insert(T* element)
{
	m_lng++;
	Node* temp = new Node(tail, element);
	if (tail == nullptr) {
		head = temp;
		tail = temp;
	}
	else {
		tail->next = temp;
		tail = tail->next;
	}
}

template<typename T>
inline int List<T>::lng() const
{
	return m_lng;
}

template<typename T>
inline bool List<T>::contains(T item)
{
	if (head == nullptr)return false;
	Node* temp = head;
	while (temp->next != nullptr) {
		if (*temp->data == item)
			return true;
		temp = temp->next;
	}return false;
}

template<typename T>
inline T* List<T>::getById(int id)
{
	if (id >= m_lng) {
		return nullptr;
	}
	Node* temp = head;
	for (int i = 0; i < id; i++) {
		temp = temp->next;
	}return temp->data;
}

template<typename T>
inline T* List<T>::operator[](int id)
{
	if (id >= m_lng) {
		return nullptr;
	}
	Node* temp = head;
	for (int i = 0; i < id; i++) {
		temp = temp->next;
	}return temp->data;
}

template<typename T>
inline void List<T>::erase()
{
	this->~List();
	this->m_lng = 0;
	this->head = nullptr;
	this->tail = nullptr;
}

template<typename T>
inline int List<T>::getSize()
{

	return m_lng;
}

template<typename T>
inline double List<T>::getTime()
{
	clock_t end = clock();
	double time= (float)(end - start) / CLOCKS_PER_SEC;
	end = start;
	return time;
}

template<typename T>
inline List<T>::~List()
{
	if (head != nullptr) {
		Node* temp = head;
		while (temp->next != nullptr) {
			temp = temp->next;
			delete temp->prev;
		}delete temp;
	}
}

template<typename T>
inline List<T>::Node::Node(Node* prev, T* data) :data(data), next(nullptr), prev(prev) {}

template<typename T>
inline List<T>::Node::~Node()
{
	//delete data;
}
