#pragma once
#include "lib.h"
#include"List.h"
enum NodeColor
{
	RED = true,
	BLACK = false
};

template <class KeyT, class ValT>
class MapNode
{
public:
	NodeColor color;
	KeyT key;
	ValT value;
	MapNode* parent;
	MapNode* left;
	MapNode* right;
	size_t level;

	MapNode()
	{
		color = RED;
		level = 0;
		parent = left = right = nullptr;
	}

	MapNode(KeyT new_key, ValT new_value)
	{
		color = RED;
		key = new_key;
		value = new_value;
		level = 0;
		parent = left = right = nullptr;
	}

	MapNode* brother()
	{
		if (!parent)return nullptr;
		if (side())
			return parent->left;
		else
			return parent->right;

	}

	MapNode* grandparent()
	{
		if (this && parent)
			return parent->parent;
		return nullptr;
	}

	MapNode* uncle()
	{
		MapNode *grandparent = this->grandparent();
		if (!grandparent)
			return nullptr; // No grandparent means no uncle
		if (parent->side())
			return grandparent->left;
		return grandparent->right;
	}

	//if node is right child: 1, if left: 0, node has no parent: -1
	int side()
	{
		if (!parent) return -1;
		if (this == parent->right)
			return 1;
		return 0;
	}

	void rotate_left()
	{
		if (this)
		{
			MapNode *pivot = right;

			pivot->parent = parent;
			//pivot could become root of tree
			if (parent) {
				if (this->side() == 0)
					parent->left = pivot;
				else
					parent->right = pivot;
			}

			right = pivot->left;
			if (pivot->left)
				pivot->left->parent = this;

			parent = pivot;
			pivot->left = this;
		}
	}

	void rotate_right()
	{
		if (this)
		{
			MapNode *pivot = left;

			pivot->parent = parent;
			//pivot could become root of tree
			if (parent) {
				if (this->side() == 0)
					parent->left = pivot;
				else
					parent->right = pivot;
			}

			left = pivot->right;
			if (pivot->right)
				pivot->right->parent = this;

			parent = pivot;
			pivot->right = this;
		}

	}

	MapNode* insert(KeyT new_key, ValT new_value)
	{
		if (is_empty(new_key)) throw invalid_argument("Empty key");
		MapNode* node = new MapNode(new_key, new_value);
		//if tree is empty
		if (!this)
		{
			node->color = BLACK;
			return node;
		}
		else
		{
			MapNode* cur = this;
			MapNode* prev = nullptr;
			//find nil
			while (cur != nullptr)
			{
				prev = cur;
				if (*node == *cur) throw invalid_argument("This is key is already in tree");
				else
					if (*node > *cur) cur = cur->right;
					else cur = cur->left;
			}
			if (*node > *prev) prev->right = node;
			else prev->left = node;
			node->parent = prev;

			return fix_insert(node);
		}
		return this;
	}

	MapNode* fix_insert(MapNode* node)
	{
		if (node->parent)
			if (node->parent->color == RED)
			{
				MapNode* node_grandparent = node->grandparent(); //if node`s parent is RED, it must have grandparent
				if (!node_grandparent) throw runtime_error("Error in building the tree");
				MapNode* node_uncle = node->uncle();
				if (node_uncle)
				{
					if (node_uncle->color == RED)
					{
						node->parent->color = BLACK;
						node_uncle->color = BLACK;
						if (node_grandparent->parent)
						{
							node_grandparent->color = RED;
							return fix_insert(node_grandparent);
						}
					}
					else
					{
						if (node->parent->side())
						{
							if (!node->side())
								//rotate right
								node->parent->rotate_right();
							//rotate left
							node_grandparent->rotate_left();
						}
						else
						{
							if (node->side())
							{
								//rotate left
								node->parent->rotate_left();
							}
							//rotate right
							node_grandparent->rotate_right();
						}
						node_grandparent->color = RED;
						node_grandparent->parent->color = BLACK;
						if (parent)
							return parent->fix_insert(node_grandparent);
						return fix_insert(node_grandparent);
					}
				}
				else
				{
					if (node->parent->side())
					{
						if (!node->side())
							//rotate right
							node->parent->rotate_right();
						//rotate left
						node_grandparent->rotate_left();
					}
					else
					{
						if (node->side())
						{
							//rotate left
							node->parent->rotate_left();
						}
						//rotate right
						node_grandparent->rotate_right();
					}
					node_grandparent->color = RED;
					node_grandparent->parent->color = BLACK;
					if (parent)
						return parent->fix_insert(node_grandparent);
					return fix_insert(node_grandparent);
				}
			}

		return this;
	}

	MapNode* find(KeyT key_to_find)
	{
		if (!this) return nullptr;
		if (is_empty(key_to_find)) throw invalid_argument("Key to find is empty");
		MapNode to_find = MapNode(key_to_find, NULL);
		if (to_find == *this) return this;
		else
			if (to_find > *this && right)
				return right->find(key_to_find);
			else
				if (to_find < *this && left)
					return left->find(key_to_find);
		return nullptr;
	}

	MapNode* remove(KeyT key_to_delete)
	{
		if (is_empty(key_to_delete)) throw invalid_argument("Empty key");
		MapNode* node = this->find(key_to_delete);
		if (!node) throw invalid_argument("Attemt of removing nonexisting element");
		//if node has both childen or only left child
		if (node->left)
		{
			MapNode* cur = node->left;
			MapNode* prev = nullptr;
			//find the largent key in left subtree
			while (cur)
			{
				prev = cur;
				cur = cur->right;
			}
			//copy value and key from node which wiil be deleted
			node->key = prev->key;
			prev->key = NULL;
			node->value = prev->value;

			//if node to delete is black
			if (prev->color == BLACK)
				return fix_remove(prev);
			else
			{
				if (prev->side())
					prev->parent->right = nullptr;
				else
					prev->parent->left = nullptr;
				delete prev;
				return this;
			}
		}
		else
			//if node has only right child
			if (node->right)
			{
				MapNode* cur = node->right;
				MapNode* prev = nullptr;
				//find the least key in right subtree
				while (cur)
				{
					prev = cur;
					cur = cur->left;
				}
				//copy value and key from node which wiil be deleted
				node->key = prev->key;
				prev->key = NULL;
				node->value = prev->value;

				//if node to delete is black
				if (prev->color == BLACK)
					return fix_remove(prev);
				else
				{
					if (prev->side())
						prev->parent->right = nullptr;
					else
						prev->parent->left = nullptr;
					delete prev;
					return nullptr;
				}
			}
		//if node has no childen
			else
			{
				if (!node->parent)
				{
					delete node;
					return nullptr;
				}
				//if node to delete is black
				if (node->color == BLACK)
					return fix_remove(node);
				else
				{
					if (node->side())
						node->parent->right = nullptr;
					else
						node->parent->left = nullptr;
					delete node;
					return nullptr;
				}
			}
	}

	MapNode* fix_remove(MapNode* node)
	{
		fix_black(node);
		if (node->side())
			node->parent->right = nullptr;
		else
			node->parent->left = nullptr;

		delete node;
		return this;

	}

	MapNode* fix_black(MapNode* node)
	{
		MapNode* right_nephew = node->brother()->right;
		MapNode* left_nephew = node->brother()->left;
		if (node->parent->color == RED)
		{

			//node has no nephews
			if (!left_nephew && !right_nephew)
			{
				node->parent->color = BLACK;
				node->brother()->color = RED;
			}
			else
				//node is right child
				if (node->side())
				{
					if (!left_nephew || left_nephew->color == BLACK)
					{
						node->brother()->rotate_left();
						right_nephew->color = BLACK;
						right_nephew->left->color = RED;
					}
					node->parent->rotate_right();
				}
				else
				{
					if (!right_nephew || right_nephew->color == BLACK)
					{
						node->brother()->rotate_right();
						left_nephew->color = BLACK;
						left_nephew->right->color = RED;
					}
					node->parent->rotate_left();
				}

		}
		else
			if (node->brother()->color == RED)
			{
				//node is right child
				if (node->side())
				{
					node->parent->rotate_right();
					node->parent->color = BLACK;
					node->grandparent()->color = BLACK;
					node->brother()->color = RED;
				}
				else
				{
					node->parent->rotate_left();
					node->parent->color = BLACK;
					node->grandparent()->color = BLACK;
					node->brother()->color = RED;
				}
			}
			else
				if (!left_nephew && !right_nephew)
				{
					node->brother()->color = RED;
					fix_black(node->parent);
				}
				else
				{
					if (node->side())
					{
						if (!left_nephew || left_nephew->color == BLACK)
						{
							node->brother()->rotate_left();
							node->brother()->color = BLACK;
						}
						node->parent->rotate_right();
					}
					else
					{
						if (!right_nephew || right_nephew->color == BLACK)
						{
							node->brother()->rotate_right();
							node->brother()->color = BLACK;
						}
						node->parent->rotate_left();
					}
				}
		//if root changed
		MapNode* root = this;
		while (root->parent)
			root = root->parent;
		return root;
	}

	MapNode* get_max()
	{
		MapNode* cur = this;
		while (cur->right)
			cur = cur->right;
		return cur;
	}

	MapNode* get_min()
	{
		MapNode* cur = this;
		while (cur->left)
			cur = cur->left;
		return cur;
	}

	List<KeyT>* get_keys(List<KeyT>* keys)
	{
		if (right)
			keys = right->get_keys(keys);
		keys->push_back(this->key);
		if (left)
			keys = left->get_keys(keys);
		return keys;
	}

	List<ValT>* get_values(List<ValT>* values)
	{
		if (right)
			values = right->get_values(values);
		values->push_back(this->value);
		if (left)
			values = left->get_values(values);
		return values;
	};

	int black_height()
	{
		if (!this) return 1;
		if (!parent && !right && !left) return 1;
		if (!right && !left)
			if (color == BLACK) return 2;
			else return 1;
		else
		{
			int this_h = color == BLACK ? 1 : 0;
			int right_h = right->black_height();
			if (right_h == left->black_height()) return right_h + this_h;
			else return -1;
		}
	}

	void output_tree(size_t level)
	{
		if (this)
		{
			//right subtree
			if (right)
				right->output_tree(level + 1);

			//this
			for (int i = 1; i < level; i++)
			{
				cout << print_nchar(' ', 11) << '|';
			}
			if (level)
				cout << print_nchar(' ', 12);
			char node_color = (color == BLACK) ? 'B' : 'R';
			if (color == RED) SetColor(Red, Black);
			cout << '[' << key << ';' << value << ';' << node_color << ']';
			SetColor(White, Black);
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

			//left subtree
			if (left)
				left->output_tree(level + 1);
			cout << endl;
		}
	}

	void clear()
	{
		if (this)
		{
			if (right)
				right->clear();
			if (left)
				left->clear();
			delete this;
		}
	}

	~MapNode()
	{
		if (std::is_same<KeyT, char*>::value)
			if (key)
			{
				//free(key);
				key = nullptr;
			}
	}

	friend bool operator >(MapNode& node1, MapNode& node2) {
		
		if (std::is_same<KeyT, char*>::value)
		{
			if (compare_str(node1.key, node2.key) == 1)
				return true;
			return false;
		}
		else
			return (node1.key > node2.key) ? true : false;
	}

	friend bool operator <(MapNode& node1, MapNode& node2) {

		if (std::is_same<KeyT, char*>::value)
		{
			if (compare_str(node1.key, node2.key) == -1)
				return true;
			return false;
		}
		else
			return (node1.key < node2.key) ? true : false;
	}
	friend bool operator >=(MapNode& node1, MapNode& node2) {

		if (std::is_same<KeyT, char*>::value)
		{
			if (compare_str(node1.key, node2.key) != -1)
				return true;
			return false;
		}
		else
			return (node1.key >= node2.key) ? true : false;
	}
	friend bool operator <=(MapNode& node1, MapNode& node2) {

		if (std::is_same<KeyT, char*>)
		{
			if (compare_str(node1.key, node2.key) != 1)
				return true;
			return false;
		}
		else
			return (node1.key <= node2.key) ? true : false;
	}
	friend bool operator ==(MapNode& node1, MapNode& node2) {

		if (std::is_same<KeyT, char*>::value)
		{
			if (compare_str(node1.key, node2.key) == 0)
				return true;
			return false;
		}
		else
			return (node1.key == node2.key) ? true : false;
	}

	bool is_empty(KeyT key_to_check)
	{
		if (std::is_same<KeyT, char*> :: value)
		{
			if (!key_to_check || !key_to_check[0]) return true;
			return false;
		}
		return key_to_check == NULL ? true : false;
		
	}
};


