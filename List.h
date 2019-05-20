#pragma once
#include "ListNode.h"

template <class T>
class List
{
private:
	ListNode <T> *head;
	ListNode <T> *tail;
	size_t list_size;

public:
	List<T>() { head = nullptr; tail = nullptr; list_size = 0; }
	~List<T>() { if (head) clear(); }
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

	ListNode<T>* get_head() { return head; }

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
			tail->next->prev = tail;
			tail = tail->next;
		}
		list_size++;
	}

	// add new element before the head of the list
	void push_front(T new_item)
	{
		head->prev = new ListNode<T>(new_item);
		head->prev->next = head;
		head = head->prev;
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
			ListNode<T> *node = tail;
			tail = tail->prev;
			tail->next = nullptr;
			node->~ListNode();
			
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
			head->prev = nullptr;
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
			while (current)
			{
				ListNode<T>* to_delete = current;
				current = current->next;

				delete to_delete;
			}
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

	List* push_back(List* list)
	{
		/*if (!this || is_empty()) return list;
		if (!list->is_empty())
		{
			tail->next = list->head;
			tail = list->tail;
		}
		return this;*/



	}

	void add_sort(T new_item)
	{if (!head) push_front(new_item);
		else
		{
			ListNode<T>* cur = head;
			ListNode<T>* prev = nullptr;
			
			while (cur)
			{
				if (*new_item < *(cur->get_item()))
				{
					if (!prev) //add as head of list
					{
						head = new ListNode<T>(new_item);
						head->next = cur;
					}
					else //add to the middle of list
					{
						ListNode<T>* node = new ListNode<T>(new_item);
						node->next = cur;
						prev->next = node;
					}
					cur = nullptr;
					list_size++;
				}
				else 
					if (!cur->next) //add to tail
				{
					push_back(new_item);
					cur = nullptr;
				}
				else
				{
					prev = cur;
					cur = cur->next;
				}
			}
		}
		
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
};



