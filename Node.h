#pragma once
#include "basic.h"


using namespace std;
template <typename T>
class Node
{
private:
	T item;


public:
	Node<T> * next;
	Node<T>(T new_item) {
		item = new_item;
		next = nullptr;
	}
	~Node() {}

	T get_item() { return item; }
	void set_item(T new_item) { item = new_item; }
};