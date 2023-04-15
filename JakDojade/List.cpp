//#include "List.h"
//
//template<typename T>
//List<T>::Node::Node(Node* prev, T* data):data(data),next(nullptr),prev(prev){}
//
//template<typename T>
//List<T>::Node::~Node()
//{
//	delete data;
//}
//
//template<typename T>
//List<T>::List()
//{
//	head = nullptr;
//	tail = nullptr;
//	m_lng = 0;
//}
//
//template<typename T>
//void List<T>::insert(T* element)
//{
//	m_lng++;
//	Node* temp = new Node(tail, element);
//	if (tail == nullptr) {
//		head = temp;
//		tail = temp;
//	}
//	else {
//		tail->next = temp;
//		tail = tail->next;
//	}
//}
//template<typename T>
//int List<T>::lng() const
//{
//	return m_lng;
//}
//template<typename T>
//T* List<T>::operator[](int id)
//{
//	if (id >= m_lng) {
//		return nullptr;
//	}
//	Node* temp = head;
//	for (int i = 0; i < id; i++) {
//		temp = temp->next;
//	}return temp->data;
//}
//template<typename T>
//List<T>::~List()
//{
//	if (head != nullptr) {
//		Node* temp = head;
//		while (temp->next != nullptr) {
//			temp = temp->next;
//			delete temp->prev;
//		}delete temp;
//	}
//}