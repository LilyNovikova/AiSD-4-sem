#pragma once
#include "Node.h"

template <typename T>
class List
{
private:
	Node <T> *head;
	Node <T> *tail;
	int list_size;

public:
	List<T>() { head = nullptr; tail = nullptr; list_size = 0; }
	~List<T>() { if (head) head->destroy_from_this(head); }
	/*void push_back(T new_item); // add new element after the tail of the list
	void push_front(T new_item);  // add new element before the head of the list
	void pop_back(); // delete last element
	void pop_front(); // delete first element
	void insert(T new_item, int index); // add new element before the one with this index
	T at(int index); // get an element by the index
	void remove(int index); // delete an element by the index
	int get_size(); // get the list size
	void clear(); // delete the list
	void set(T new_item, int index); // замена элемента по индексу на передаваемый элемент
	bool isEmpty(); // проверка на пустоту списка
	*/
	//friend std::ostream operator<<(std::ostream & os, List<T>& list);	//Перегрузка оператора вывода

	void push_back(T new_item)
	{
		Node<T> node = Node<T>(new_item);
		if (!head)
		{
			head = &node;
			tail = &node;
		}
		else
			tail = &node;
		tail = &node;
		list_size++;
	}

	void push_front(T new_item)
	{
		Node<T> node = Node<T>(new_item);
		node.next = head;
		head = &node;
		if (!tail) tail = &node;
		list_size++;
	}

	void pop_back()
	{
		if (!head) throw out_of_range("You tried to delete an item from empty list");

		Node<T> *node = head;
		while (node->next != tail)
			node = node->next;
		tail = node;
		*(node->next).~Node();
		tail->next = nullptr;
		list_size--;


	}

	void pop_front()
	{
		if (!head) throw out_of_range("You tried to delete an item from empty list");
		Node<T>* node = head;
		head = head->next;
		*node.~Node();
		list_size--;

	}

	void insert(T new_item, int index)
	{
		if (index < 0) throw invalid_argument("Item index < 0");
		if (index >= list_size) throw out_of_range("Too big index");
		else
		{
			Node<T> new_node = Node<T>(new_item);
			if (!index) {
				new_node.next = head;
				head = &new_node;
			}
			else {
				Node<T> *node = head;
				for (int i = 0; i < index - 1; i++)
					node = node->next;
				new_node.next = node->next;
				node->next = &new_node;
			}
		}
		list_size++;
	}

	T at(int index)
	{
		if (index < 0) throw invalid_argument("Item index < 0");
		if (index + 1 > list_size) throw out_of_range("Too big index");

		Node<T> *node = head;
		for (int i = 0; i < index; i++)
			node = node->next;
		return node->get_item();

	}

	void remove(int index)
	{
		if (index < 0) throw invalid_argument("Item index < 0");
		if (index + 1 > list_size) throw out_of_range("Too big index");

		if (!index) {
			Node<T>* to_delete = head;
			head = head->next;
			delete to_delete;
		}
		else
		{
			Node<T>* node = head;
			for (int i = 0; i < index - 1; i++)
				node = node->next;
			Node<T>* to_delete = node->next;
			node->next = node->next->next;
			delete to_delete;
		}
		list_size--;
	}

	int get_size()
	{
		return list_size;
	}

	void clear()
	{
		if (head) destroy_from_this(head);
		head = nullptr;
		tail = nullptr;
		list_size = 0;
	}

	void set(T new_item, int index)
	{
		if (index < 0) throw invalid_argument("Item index < 0");
		if (index + 1 > list_size) throw out_of_range("Too big index");
		Node<T> new_node = Node<T>(new_item);
		Node<T>* current_node = head;
		//finding an element with this index
		for (int i = 0; i < index; i++) { current_node = current_node->next; }

		new_node.next = (current_node->next)->next;
		current_node = &new_node;
	}

	bool isEmpty()
	{
		if (list_size) return false;
		return true;
	}

	friend std::ostream & operator <<(std::ostream & out, List<T>& list) {
		Node<T> * node = list.head;
		while (node)
		{
			out << node->get_item() << endl;
			node = node->next;
		}
		return out;
	}
};



