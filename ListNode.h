#pragma once
#include "stdio.h"
#include "conio.h"
#include "cstdlib"
#include "iostream"
#include <string.h>
#include <stdexcept>


using namespace std;
template <typename T>
class ListNode
{
private:
	T item;


public:
	ListNode<T> * next;
	ListNode<T> (T new_item) {
		item = new_item;
		next = nullptr;
	}
	~ListNode() {}

	T get_item() { return item; }
	void set_item(T new_item) { item = new_item; }
};