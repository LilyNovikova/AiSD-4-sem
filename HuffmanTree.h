#pragma once
#include "Map.h"
#include "List.h"

class TreeNode
{
public:
	char* item;
	char* code;
	size_t frequency;
	TreeNode* parent;
	TreeNode* right;
	TreeNode* left;
	TreeNode()
	{
		item = nullptr;
		code = nullptr;
		parent = nullptr;
		right = nullptr;
		left = nullptr;
	}
	TreeNode(char* new_item, size_t new_frequency)
	{
		item = copy_str(new_item);
		frequency = new_frequency;
		code = nullptr;
		parent = nullptr;
		right = nullptr;
		left = nullptr;
	}

	void node_out(size_t level)
	{
		for (int i = 1; i < level; i++)
		{
			cout << print_nchar(' ', 11) << '|';
		}
		if (level)
			cout << print_nchar(' ', 12);
		if (code)
			printf("[%s;%i;%s]", item, frequency, code);
			//cout << '[' << item << ';' << frequency << ';' << code << ']';
		else
			printf("[%s;%i; ]", item, frequency);
		//cout << '[' << item << ';' << frequency << ';' << " ]";
		if (left && right)
		{
			cout << "<" << endl;
		}
		else
			if (right)
			{
				cout << "/" << endl;
			}
			else
				if (left)
				{
					cout << "\\" << endl;
				}
				else
				{
					cout << endl;
				}
	}

	void tree_out(size_t level)
	{
		if (right)
			right->tree_out(level + 1);
		node_out(level);
		if (left)
			left->tree_out(level + 1);
		cout << endl;
	}


	TreeNode* find(char* item_to_find)
	{
		if (!this) throw runtime_error("Node doesn`t exist");
		if (compare_str(item, item_to_find) == 0) return this;
		else if (!left && !right) throw invalid_argument("Can`t find this item");
		if (right)
			if (contain(right->item, item_to_find))
				return right->find(item_to_find);
		if (left)
			if (contain(left->item, item_to_find))
				return left->find(item_to_find);


	}

	void set_code()
	{
		if (!this) throw runtime_error("Node doesn`t exist");
		if (!right && !left && !parent)
		{
			code = (char*)"0";
		}
		if (right)
		{
			right->code = con_str(code, (char*)"1");
			right->set_code();
		}
		if (left)
		{
			left->code = con_str(code, (char*)"0");
			left->set_code();
		}
	}

	void clear()
	{
		if (this)
		{
			right->clear();
			left->clear();
			if (item)
			{
				//free(item);
				item = nullptr;
			}
			if (code)
			{
				//free(code);
				code = nullptr;
			}
		}
	}

	~TreeNode()
	{
		if (code) //free(code);
			if (item) //free(item);
				code = nullptr;
		item = nullptr;
	}
	friend bool operator< (TreeNode& node1, TreeNode& node2)
	{
		if (node1.frequency < node2.frequency)
			return true;
		return false;
	}
};


class HuffmanTree
{
private:
	TreeNode * root;
	Map<char, size_t>* alphabet;
	size_t alph_size;

public:
	HuffmanTree()
	{
		root = nullptr;
		alph_size = 0;
		alphabet = new Map<char, size_t>;
	}
	~HuffmanTree()
	{
		clear();
	}

	void clear()
	{
		root->clear();
		root = nullptr;
	}

	void show_tree()
	{
		root->tree_out(0);
	}

	void set_alphabet(char* message)
	{
		if (!message) throw invalid_argument("Message to code is empty");
		if (message[0] == 0) throw invalid_argument("Message to code is empty");

		for (int i = 0; i < strlen(message); i++)
		{
			size_t item_frequency = 1;
			for (int j = i + 1; j < strlen(message); j++)
				if (message[i] == message[j]) item_frequency++;

			try
			{
				alphabet->insert(message[i], item_frequency);
				alph_size++;
			}
			catch (invalid_argument e)
			{
				//do nothing; it means this item is already in alphabet
			}
		}
	}

	List<char>* get_alphabet()
	{
		return alphabet->get_keys();
	}

	void huffman()
	{
		if (alphabet->is_empty()) throw runtime_error("Coding alphabet is empty");
		//create list sorted by frequency
		List<char>* symbols_list = alphabet->get_keys();
		List<TreeNode*>* list = new List<TreeNode*>;
		while (!symbols_list->is_empty())
		{
			list->add_sort(new TreeNode(char_to_str(symbols_list->at(0)), alphabet->find(symbols_list->at(0))));
			symbols_list->pop_front();
		}
		bool tree_built = false;
		while (!list->is_empty() && !tree_built)
		{
			if (list->get_size() == 1)
			{
				root = list->get_head()->get_item();
				tree_built = true;
			}
			else
			{
				TreeNode *node1 = list->at(0),
					*node2 = list->at(1);
				TreeNode* new_node = new TreeNode(con_str(node1->item, node2->item), node1->frequency + node2->frequency);
				node1->parent = new_node;
				node2->parent = new_node;
				new_node->left = node1;
				new_node->right = node2;
				list->pop_front();
				list->pop_front();
				list->add_sort(new_node);
			}
		}
	}

	char* code(char* message)
	{
		char* coded_message = nullptr;

		set_alphabet(message);
		//alphabet->output_list();
		huffman();

		root->set_code();
		show_tree();
		for (int i = 0; i < strlen(message); i++)
		{
			char* item_to_find = char_to_str(message[i]);
			TreeNode* node = root->find(item_to_find);
			if (!node) throw runtime_error("Unknown symbol in a message to code");
			char * item_code = node->code;
			coded_message = con_str(coded_message, item_code);
			//coded_message = con_str(coded_message, (char*)" ");
		}

		return coded_message;
	}

	char* decode(char* message)
	{
		if (!message) throw invalid_argument("Message to decode is empty");
		char* decoded_message = nullptr;
		TreeNode* cur = root;
		if (root)
			for (int i = 0; i < strlen(message); i++)
			{
				if (!cur->left && !cur->right)
				{
					decoded_message = con_str(decoded_message, cur->item);
					cur = root;
					i++;
				}
				if (message[i] == '1') cur = cur->right;
				else if (message[i] == '0') cur = cur->left;
				else if (cur != root)throw runtime_error("Unknown symbol in coded message");
			}
		return decoded_message;
	}
};
