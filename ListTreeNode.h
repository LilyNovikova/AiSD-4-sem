#pragma once
#include "lib.h"

class ListTreeNode
{
public:
	char* item;
	size_t frequency;
	char* code;
	ListTreeNode* parent;
	ListTreeNode* left;
	ListTreeNode* right;
	ListTreeNode* next;
	ListTreeNode* prev;

	ListTreeNode()
	{
		item = nullptr;
		frequency = 0;
		parent = left = right = next = prev = nullptr;
		code = nullptr;
	}
	ListTreeNode(char* new_item, size_t new_frequency)
	{
		item = copy_str(new_item);
		frequency = new_frequency;
		parent = left = right = next = prev = nullptr;
		code = nullptr;
	}

	ListTreeNode(size_t new_frequency)
	{
		item = nullptr;
		frequency = new_frequency;
		parent = left = right = next = prev = nullptr;
		code = nullptr;
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
			try
			{
				right->set_code();
			}
			catch (runtime_error e)
			{
				throw runtime_error("Node doesn`t exist");
			}
		}
		if (left)
		{
			left->code = con_str(code, (char*)"0");
			left->set_code();
		}
	}

	//add a list of elements after the tail
	ListTreeNode* push_front(ListTreeNode* node)
	{
		if (!this) return node;
		prev = node;
		node->next = this;
		return node;

	}
	ListTreeNode* list_of_symbols(ListTreeNode* list)
	{
		if (!this) throw runtime_error("Node doesn`t exist");
		if (right) list = right->list_of_symbols(list);
		if (left) list = left->list_of_symbols(list);

		if (!right && !left)
			list = list->push_front(this);
		return list;
	}

	ListTreeNode* find(char* item_to_find)
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

	void output_list()
	{
		if (this)
		{
			if (code)
				cout << '[' << item << ';' << frequency << ';' << code << ']';
			else
				cout << '[' << item << ';' << frequency << ';' << " ]";
			if (next) next->output_list();
			else
				cout << endl;
		}
	}

	void output_tree(size_t level)
	{
		if (this)
		{

			if (right)
				right->output_tree(level + 1);
			for (int i = 1; i < level; i++)
			{
				cout << print_nchar(' ', 11) << '|';
			}
			if (level)
				cout << print_nchar(' ', 12);
			if (code)
				cout << '[' << item << ';' << frequency << ';' << code << ']';
			else
				printf("[%s;%i; ]", item, frequency);
				//cout << '[' << item << ';' << frequency << ';' << " ]";
			if (left&&right)
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
			if (left)
				left->output_tree(level + 1);
			cout << endl;
		}
	}

	void clear_tree()
	{
		if (right) right->clear_tree();
		if (left) left->clear_tree();
		delete(this);
	}

	~ListTreeNode()
	{
		if (item) free(item);
		if (code) free(code);
	}

	/*bool operator>(const ListTreeNode& node1, const ListTreeNode& node2)
	{
		out < str.front();
		return out;
	}*/
};

