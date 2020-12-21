#include "../Headers/List.h"
#include "../Headers/TileObject.h"

Node::Node(Node* _prev, Object* _data, Node* _next) : prev(_prev), data(_data), next(_next) {}

List::List() : head(nullptr) {};

List::~List() {

	for (Node* node = head; node != nullptr;) {

		Node* next = node->next;
		delete node;
		node = next;
	}
}

void List::push(Object* obj) {

	head = new Node(nullptr, obj, head);
	head->next->prev = head;
}

Object* List::pop(Object* obj) {

	if (!head || !obj) return nullptr;

	Object* data = nullptr;

	for (Node* node = head; node != nullptr; node = node->next) 
		if (node->data->getName() == obj->getName()) {

			if (node->next) node->next->prev = node->prev;
			if (node->prev) node->prev->next = node->next;
			else (head = node->next);
			data = node->data;
			delete node;
			break;
		}

	return data;
}

bool List::empty() {

	return !head;
}

bool List::isin(char sym) {

	Node* node = head;
	for (node; node; node = node->next)
		if (node->data->getName() == sym) return true;

	return false;
}

Object* List::operator[] (int col) {

	if (!head) return nullptr;

	Node* node = head;

	for (int i = 0; i <= col; i++) {

		node = node->next;
		if (!node) break;
	}
	if (node)
		return node->data;

	return nullptr;
}