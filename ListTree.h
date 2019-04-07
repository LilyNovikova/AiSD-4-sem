#pragma once
#include "ListTreeNode.h"
#include "List.h"

class ListTree
{
private:
	ListTreeNode * head,
		*root,
		*tail,
		*alphabet;
	size_t alphabet_size;

public:


	ListTree() { head = root = tail = alphabet = nullptr; }

	void add_to_alphabet(char* item, size_t frequency)
	{
		add_to_list(new ListTreeNode(item, frequency));
		alphabet_size++;
	}

	void add_to_list(ListTreeNode* node)
	{
		if (!head)
		{
			head = node;
			tail = head;
		}
		else
			if (head->frequency <= node->frequency)
			{
				node->next = head;
				head->prev = node;
				head = node;
			}
			else
				if (tail->frequency >= node->frequency)
				{
					tail->next = node;
					node->prev = tail;
					tail = node;
				}
				else
				{
					ListTreeNode* cur = tail;
					while (node->frequency > cur->frequency && cur->prev)
						cur = cur->prev;
					node->prev = cur;
					node->next = cur->next;
					cur->next = node;
				}
	}

	void pop_back()
	{
		if (!head) throw out_of_range("You tried to delete an item from empty list");
		if (head == tail)
			head = tail = nullptr;
		else
		{
			tail = tail->prev;
			tail->next->prev = nullptr;
			tail->next = nullptr;
		}
	}

	void huffman()
	{
		while (head != tail)
		{
			ListTreeNode* node1 = tail;
			ListTreeNode* node2 = tail->prev;
			ListTreeNode* sum_node = new ListTreeNode(con_str(node1->item, node2->item),node1->frequency + node2->frequency);
			node1->parent = node2->parent = sum_node;
			sum_node->left = node1;
			sum_node->right = node2;
			pop_back();
			pop_back();
			add_to_list(sum_node);
		}
		root = head;
	}

	void list_of_symbols()
	{
		alphabet = nullptr;
		alphabet = root->list_of_symbols(alphabet);
	}

	char* code(char* message)
	{
		huffman();
		//output_tree();
		root->set_code();
		list_of_symbols();
		alphabet->output_list();
		char* coded_message = nullptr;
		for (int i = 0; i < strlen(message); i++)
		{
			char* item_to_find = char_to_str(message[i]);
			char * item_code = (root->find(item_to_find))->code;
				coded_message = con_str(coded_message, item_code);
				coded_message = con_str(coded_message, (char*)" ");
			//else throw runtime_error("Unknown symbol in a message to code");
		}
		return coded_message;
	}

	char* decode(char* message)
	{
		char* decoded_message = nullptr;
		char* current_message = copy_str(message);
		while (message)
		{
			ListTreeNode* node = root->decode_node(current_message);
			decoded_message = con_str(decoded_message, node->item);
			current_message = current_message + strlen(node->code);
		}
		return decoded_message;
	}

	void output_tree()
	{
		root->output_tree(0);
	}

	void output_list()
	{
		head->output_list();
	}

	void clear_list()
	{

	}

	~ListTree() {}
};

