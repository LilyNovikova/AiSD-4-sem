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
	/*void destroy_from_this(Node<T> * node);
	~Node<T>();

	T get_item();*/
	//Node<T>* get_next();
	//void set_next(Node<T>* next_node);
	~Node() {}

	void destroy_from_this()
	{
		/*while (this)
		{
			(this->next)->destroy_from_this();
			delete this;
		}*/
	}

	T get_item() { return item; }
	void set_item(T new_item) { item = new_item; }

	//output operator
	friend std::ostream & operator <<(std::ostream & out, Node<T>& node)
	{
			out << node->get_item() << endl;
		return out;
	}
};