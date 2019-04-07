#pragma once
#include "ListNode.h"

template <typename T>
class List
{
private:
	ListNode <T> *head;
	ListNode <T> *tail;
	size_t list_size;

public:
	List<T>() { head = nullptr; tail = nullptr; list_size = 0; }
	~List<T>() { if (head) clear(); }

	// add new element after the tail of the list
	void push_back(T new_item)
	{
		if (!head)
		{
			head = new ListNode<T>(new_item);
			tail = head;
		}
		else
		{
			tail->next = new ListNode<T>(new_item);
			tail = tail->next;
		}
		list_size++;
	}

	// add new element before the head of the list
	void push_front(T new_item)
	{
		ListNode<T>* node = head;
		head = new ListNode<T>(new_item);
		head->next = node;
		if (!tail) tail = head;
		list_size++;
	}

	// delete last element
	void pop_back()
	{
		if (!head) throw out_of_range("You tried to delete an item from empty list");
		if (list_size == 1)
		{
			delete head;
			head = tail = nullptr;
		}
		else
		{
			ListNode<T> *node = head;
			while (node->next != tail)
				node = node->next;
			tail = node;
			(node->next)->~ListNode<T>();
			tail->next = nullptr;
		}
		list_size--;


	}

	// delete first element
	void pop_front()
	{
		if (!head) throw out_of_range("You tried to delete an item from empty list");
		if (list_size == 1)
		{
			delete head;
			head = tail = nullptr;
		}
		else
		{
			ListNode<T>* node = head;
			head = head->next;
			node->~ListNode<T>();
		}
		list_size--;

	}

	// add new element before the one with this index
	void insert(T new_item, size_t index)
	{
		if (!index) this->push_front(new_item);
		else
			if (index + 1 > list_size) throw out_of_range("Index is greater than list size");
			else
			{
				ListNode<T> *current = head;
				for (int i = 0; i < index - 1; i++)
					current = current->next;
				ListNode<T> *new_node = new ListNode<T>(new_item);
				new_node->next = current->next;
				current->next = new_node;
				list_size++;
			}

	}

	// get an element by the index
	T at(size_t index)
	{
		if (index + 1 > list_size) throw out_of_range("Too big index");

		ListNode<T> *node = head;
		for (int i = 0; i < index; i++)
			node = node->next;
		return node->get_item();

	}

	// delete an element by the index
	void remove(size_t index)
	{
		if (!head) throw out_of_range("You tried to remove an item from empty list");
		else
			if (index + 1 > list_size) throw out_of_range("Index is greater than list size");
		if (!index)
			pop_front();
		else if (index == list_size - 1)
			pop_back();
		else
		{
			ListNode<T>* node = head;
			for (int i = 0; i < index - 1; i++)
				node = node->next;
			ListNode<T>* to_delete = node->next;
			node->next = node->next->next;
			delete to_delete;
			list_size--;
		}

	}

	// get the list size
	size_t get_size()
	{
		return list_size;
	}

	// delete the list
	void clear()
	{
		if (head)
		{
			ListNode<T>* current = head;
			do
			{
				ListNode<T>* to_delete = current;
				current = current->next;
				delete to_delete;
			} while (current);
		}
		head = nullptr;
		tail = nullptr;
		list_size = 0;
	}

	//replace an element by index
	void set(T new_item, size_t index)
	{
		if (index + 1 > list_size) throw out_of_range("Index is greater than list size");
		if (index == list_size - 1) tail->set_item(new_item);
		else
		{
			ListNode<T>* current_node = head;
			//finding an element with this index
			for (int i = 0; i < index; i++) { current_node = current_node->next; }
			current_node->set_item(new_item);
		}
	}

	//check isf list is empty
	bool is_empty()
	{
		if (list_size || head != nullptr) return false;
		return true;
	}

	//output operator
	friend std::ostream & operator <<(std::ostream & out, List<T>& list) {
		ListNode<T> * node = list.head;
		while (node)
		{
			out << node->get_item() << " ";// << endl;
			node = node->next;
		}
		return out;
	}

	//add a list of elements after the tail
	void push_back_list(List<T> list)
	{
		if (!list.is_empty())
		{
			if (head)
				tail->next = list.head;
			else
			{
				head = list.head;
				tail = list.tail;
			}
			list_size += list.list_size;
		}

	}
};



