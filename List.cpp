#include "List.h"
/*
template<typename T>
inline void List<T>::push_back(T new_item)
{
	Node node = new Node(T);
	if (!head)
	{
		head = &node;
		tail = &node;
	}
	else
		tail->next = &node;
	tail = &node;
	list_size++;
}

template<typename T>
inline void List<T>::push_front(T new_item)
{
	Node node = new Node(T);
	node.next = head;
	head = &node;
	if (!tail) tail = &node;
	list_size++;
}

template<typename T>
inline void List<T>::pop_back()
{
	if (head) {
		Node *node = head;
		while (node->next != tail)
			node = node->next;
		tail = node;
		*(node->next).~Node();
		tail->next = nullptr;
		list_size--;
	}
	else
		throw out_of_range("You tried to delete an item from empty list");
}

template<typename T>
inline void List<T>::pop_front()
{
	if (head)
	{
		Node* node = head;
		head = head->next;
		*node.~Node();
		list_size--;
	}
	else
		throw out_of_range("You tried to delete an item from empty list");

}

template<typename T>
inline void List<T>::insert(T new_item, int index)
{
	if (index < 0) throw invalid_argument("Item index < 0");
	if (index >= list_size) throw out_of_range;
	else
	{
		Node* new_node = new Node;
		new_node->item = new_item;
		if (!index) {
			new_node->next = head;
			head = new_node;
		}
		else {
			Node* node = new Node;
			for (int i = 0; i < index - 1; i++)
				node = node->next;
			new_node->next = node->next;
			node->next = new_node;
		}
	}
	list_size++;
}

template<typename T>
T List<T>::at(int index)
{
	if (index < 0) throw invalid_argument("Item index < 0");
	if (index + 1 > list_size) throw out_of_range;

	Node *node = head;
	for (int i = 0; i < index; i++)
		node = node->next;
	return node->item;

}

template<typename T>
inline void List<T>::remove(int index)
{
	if (index < 0) throw invalid_argument("Item index < 0");
	if (index + 1 > list_size) throw out_of_range;

	if (!index) {
		Node* to_delete = head;
		head = head->next;
		delete to_delete;
	}
	else
	{
		Node* node = head;
		for (int i = 0; i < index - 1; i++)
			node = node->next;
		Node* to_delete = node->next;
		node->next = node->next->next;
		delete to_delete;
	}
	list_size--;
}

template<typename T>
inline int List<T>::get_size()
{
	return list_size;
}

template<typename T>
inline void List<T>::clear()
{
	if (head) destroy_from_this(head);
	head = nullptr;
	tail = nullptr;
	list_size = 0;
}

template<typename T>
void List<T>::set(T new_item, int index)
{
	if (index < 0) throw invalid_argument("Item index < 0");
	if (index + 1 > list_size) throw out_of_range;
	Node<T> new_node = Node<T>(new_item);
	Node<T>* current_node = head;
	//finding an element with this index
	for (int i = 0; i < index; i++) { current_node = current_node->next; }

	new_node.next = (current_node->next)->next;
	current_node = &new_node;
}

template<typename T>
inline bool List<T>::isEmpty()
{
	if (list_size) return false;
	return true;
}


*/