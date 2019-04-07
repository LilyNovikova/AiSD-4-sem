#pragma once
#include "lib.h"

class ListTreeNode
{
public:
	char* item;
	size_t frequency;
	char* code;
	size_t level;
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
		if (right) list = right->list_of_symbols(list);
		if (left) list = left->list_of_symbols(list);

		if (!right && !left)
			list = list->push_front(this);
		return list;
	}

	ListTreeNode* find(char* item_to_find)
	{
		if (compare_str(item, item_to_find)) return this;
		if (right)
			if (contain(right->item, item_to_find))
				return right->find(item_to_find);
		if (left)
			if (contain(left->item, item_to_find))
				return left->find(item_to_find);
		//throw invalid_argument("Can`t find this item");
	}

	ListTreeNode* decode_node(char* item_code)
	{
		if (!right && !left) return this;
		if (item_code[0] == '1')
			return right->decode_node(item_code++);
		else
			if (item_code[0] == '0')
				return left->decode_node(item_code++);
	}

	void output_list()
	{
		if (code)
			cout << '[' << item << ';' << frequency << ';' << code << ']';
		else
			cout << '[' << item << ';' << frequency << ';' << " ]";
		if (next) next->output_list();
		else
			cout << endl;
	}

	void output_tree(size_t level)
	{
		if (this)
		{

			if (right)
				right->output_tree(level + 1);
			for (int i = 1; i < level; i++)
			{
				cout << print_nchar(' ', 8) << '|';
			}
			if (level)
				cout << print_nchar(' ', 9);
			cout << '(' << item << ';' << frequency << ';' /*<< (code)?code:' '*/ << ')';
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
						cout << "L" << endl;
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


	~ListTreeNode() {}
};

