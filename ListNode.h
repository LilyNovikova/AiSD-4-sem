#pragma once
#include "Useful.h"


using namespace std;
template <class T>
class ListNode
{
private:
	T item;
public:
	ListNode<T> * next;
	ListNode<T>* prev;
	ListNode<T>(T new_item) {
		item = new_item;
		next = nullptr;
		prev = nullptr;
	}
	~ListNode() {}

	T get_item() { 
		if(this)return item; 
	}

	void set_item(T new_item) { item = new_item; }
};