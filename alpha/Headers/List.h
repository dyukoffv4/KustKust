#pragma once

class Object;

class Node {

public:
	Node* next;
	Node* prev;
	Object* data;

	Node(Node*, Object*, Node*);
};

class List {

private:

	Node* head;

public:
	List();
	~List();

	void push(Object*);
	Object* pop(Object*);

	Object* operator[] (int);
};