#pragma once
#include "ListTreeNode.h"

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

	/*ListTreeNode* sort(ListTreeNode* list_head, ListTreeNode* list_tail)
	{
		if (!list_head) return nullptr;
		size_t pivot = (list_head->frequency + list_tail->frequency) / 2;
		ListTreeNode* new_head1 = nullptr;
		ListTreeNode* new_tail1 = nullptr;
		ListTreeNode* new_head2 = nullptr;
		ListTreeNode* new_tail2 = nullptr;
		ListTreeNode* cur = list_head;
		do
		{
			if (cur->frequency > pivot)
			{
				if (!new_head1) new_tail1 = cur;
				new_head1 = new_head1->push_front(cur);
			}
			else
			{
				if (!new_head2) new_tail2 = cur;
				new_head2 = new_head2->push_front(cur);
			}
			cur = cur->next;
		} while (cur != list_tail);
		return sort(new_head1, new_tail1)->push_front(sort(new_head2, new_tail2));
	}*/

	void set_alphabet(char* message)
	{
		if (!message) throw invalid_argument("Message to code is empty");
		ListTreeNode* list_head = nullptr;
		for (int i = 0; i < strlen(message); i++)
		{
			ListTreeNode* node = new ListTreeNode(char_to_str(message[i]), 1);
			if (!list_head)
				list_head = node;
			else
			{
				ListTreeNode* cur = list_head;
				while (cur)
				{
					if (compare_str(cur->item, node->item) == 0) //if symbol is already in alphabet 
					{
						cur->frequency++;
						cur = nullptr;
					}
					else if (compare_str(cur->item, node->item) == -1)
					{
						if (!cur->prev) //add as head of list
						{
							list_head = node;
							node->next = cur;
							cur->prev = node;

						}
						else //add to the middle of list
						{
							node->next = cur;
							cur->prev->next = node;
							node->prev = cur->prev;
							cur->prev = node;
						}
						cur = nullptr;
					}
					else
					{
						//if symbol is new
						if (!cur->next) //add as tail
						{
							node->prev = cur;
							cur->next = node;
							cur = nullptr;
						}
						else
							cur = cur->next;

					}
				}
			}
			//list_head->output_list();
		}

		//sorting list by frequency
		while (list_head)
		{
			add_to_list(new ListTreeNode(list_head->item, list_head->frequency));
			list_head = list_head->next;
		}
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
					cur->next->prev = node;
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
		if (!head) throw runtime_error("Coding alphabet is empty");
		while (head != tail)
		{
			//head->output_list();
			ListTreeNode* node1 = tail;
			ListTreeNode* node2 = tail->prev;
			ListTreeNode* sum_node = new ListTreeNode(con_str(node1->item, node2->item), node1->frequency + node2->frequency);
			node1->parent = node2->parent = sum_node;
			sum_node->left = node1;
			sum_node->right = node2;
			try
			{
				pop_back();
				pop_back();
			}
			catch (out_of_range e)
			{
				throw runtime_error(e.what());
			}
			add_to_list(sum_node);

		}
		root = head;
	}

	ListTreeNode* get_alphbet()
	{
		alphabet = nullptr;
		alphabet = root->list_of_symbols(alphabet);
		return alphabet;
	}

	char* code(char* message)
	{
		char* coded_message = nullptr;
		try
		{
			set_alphabet(message);
			//alphabet->output_list();
			huffman();
			//root->output_tree(0);
			root->set_code();

			for (int i = 0; i < strlen(message); i++)
			{
				char* item_to_find = char_to_str(message[i]);
				ListTreeNode* node = root->find(item_to_find);
				if (!node) throw runtime_error("Unknown symbol in a message to code");
				char * item_code = node->code;
				coded_message = con_str(coded_message, item_code);
				coded_message = con_str(coded_message, (char*)" ");
			}
		}
		catch (invalid_argument e)
		{
			throw invalid_argument(e.what());
		}
		catch (runtime_error e)
		{
			throw runtime_error(e.what());
		}
		return coded_message;
	}

	char* decode(char* message)
	{
		if (!message) throw invalid_argument("Message to decode is empty");
		char* decoded_message = nullptr;
		ListTreeNode* cur = root;
		if (root)
			for (int i = 0; i < strlen(message); i++)
			{
				if (!cur->left && !cur->right)
				{
					decoded_message = con_str(decoded_message, cur->item);
					cur = root;
				}
				if (message[i] == '1') cur = cur->right;
				else if (message[i] == '0') cur = cur->left;
				else if(cur != root)throw runtime_error("Unknown symbol in coded message");
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

	void clear()
	{
		if (root)
		{
			root->clear_tree();
			root = nullptr;
		}
		else
			if (head)
			{
				do
				{
					ListTreeNode* to_delete = head;
					head = head->next;
					delete(to_delete);
				} while (head);
				head = tail = nullptr;
			}
	}

	~ListTree() {}
};

