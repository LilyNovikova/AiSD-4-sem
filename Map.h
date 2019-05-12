#pragma once
#include "MapNode.h"

template <class KeyT, class ValT>
class Map
{
private:
	MapNode<KeyT, ValT>* root;
public:
	//
	Map()
	{
		root = nullptr;
	}
	void insert(KeyT key, ValT value)
	{
		try
		{
			root=root->insert(key, value);
		}
		catch (invalid_argument e)
		{
			throw invalid_argument(e.what());
			//or do nothing
		}
		catch (runtime_error e)
		{
			throw runtime_error(e.what());
		}
	}

	ValT find(KeyT key)
	{
		try
		{
			MapNode<KeyT, ValT>* node = root->find(key);
			if (node)
				return node->value;
			else
				throw invalid_argument("No such element in the map");
		}
		catch (invalid_argument e)
		{
			throw invalid_argument(e.what());
			//or do nothing
		}
	}

	void remove(KeyT key)
	{
		try
		{
			root=root->remove(key);
		}
		catch (invalid_argument e)
		{
			throw invalid_argument(e.what());
			//or do nothing
		}
	}

	void out()
	{
		root->output_tree(0);
	}

	List<KeyT> get_keys()
	{

		List<KeyT>* keys = new List<KeyT>;
		if (root)
			keys = root->get_keys(keys);
		return *keys;
	}

	List<ValT> get_values()
	{
		List<ValT>* values = new List<ValT>;
		if (root)
			values = root->get_values(values);
		return *values;
	}

	bool is_ok()
	{
		return (root->black_height() != -1) ? true : false;
	}

	bool is_empty()
	{
		return (root == nullptr) ? true : false;
	}

	~Map()
	{
		root->clear();
	}

};