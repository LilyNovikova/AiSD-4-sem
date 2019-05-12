#pragma once
#include <string.h>
#include  <time.h>
#include  <conio.h>
#include  <iostream>
#include  <malloc.h>
#include  <fstream>
#include <stdexcept>

using namespace std;


//return strind filled with this number of this character
char* give_some_chars(int number, char c)
{
	if (number > 0)
	{
		char* string = (char*)malloc((number + 1) * sizeof(char));
		for (int i = 0; i < number; i++)
			*(string + i) = c;
		*(string + number) = 0;
		return string;
	}
	else return nullptr;
}

//copy string 
char *string_copy(char* string)
{
	if (string)
	{
		char *new_str = (char*)malloc((strlen(string) + 1) * sizeof(char));
		for (int i = 0; i < strlen(string); i++)
			*(new_str + i) = *(string + i);
		*(new_str + strlen(string)) = 0;
		return new_str;
	}
	else return nullptr;
}

char *string_concat(char* dest, char* from)
{
	if (dest)
	{
		if (from)
		{
			char *new_str = (char*)malloc((strlen(dest) + strlen(from) + 1) * sizeof(char));
			for (int i = 0; i < strlen(dest); i++)
				*(new_str + i) = *(dest + i);
			for (int i = 0; i < strlen(from); i++)
				*(new_str + strlen(dest) + i) = *(from + i);
			*(new_str + strlen(dest) + strlen(from)) = 0;
			return new_str;
		}
		else return string_copy(dest);
	}
	else return string_copy(from);
}

//if s1 = s2 returns 0, if s1 > s2 returns 1, if s1 < s2 returns -1 
int compare_str(char * s1, char * s2)
{
	if (!s1 && !s2)
		return 0;
	if (s1 && !s2)
		return 1;
	if (!s1 && s2)
		return -1;

	int len = strlen(s1) > strlen(s2) ? strlen(s2) : strlen(s1);

	for (int i = 0; i <= len; i++)
	{
		if (s1[i] > s2[i])
			return 1;
		if (s1[i] < s2[i])
			return -1;
	}
	return 0;
}

char * str_by_sym(char * s, char split, int& number_of_symbol)
{
	if (!s) return nullptr;
	int new_s_len = 0;
	char* s1 = nullptr;

	if (number_of_symbol <= strlen(s))
	{
		while (s[number_of_symbol] == split) number_of_symbol++;
		char g;
		int k;
		for (int i = number_of_symbol; s[i] != split && i <= strlen(s); i++, number_of_symbol++)
		{

			k = i;
			s1 = (char*)realloc(s1, (new_s_len + 2) * sizeof(char));
			s1[new_s_len] = s[i];
			s1[new_s_len + 1] = '\0';
			new_s_len++;
		}
		g = s[k];
	}
	number_of_symbol++;
	return s1;

}

int str_to_int(char* s)
{
	if (!s || !s[0])
		throw invalid_argument("Empty string");
	int i = 0,
		number = 0,
		cur_digit = 0,
		sign;

	if (s[0] == '-')
	{
		sign = -1;
		i++;
	}
	else
		sign = 1;

	int flag = 1;

	do
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			number *= 10;
			cur_digit = ((int)s[i]) - '0';
			number += cur_digit;
			i++;
		}
		else
		{
			number = NULL;
			flag = 0;
		}
	} while (s[i] != '\0' && flag);

	number *= sign;
	return number;
}


struct Link;

struct Node
{
	char* name;
	Link *link;	//outcomming edges
	int number_link;

	bool opened;
	int distance;
	char *path;
};

struct Link
{
	Node* out;
	Node* in;
	int value;
};

struct List
{
	Node* node;
	List* next;
};

class Dijkstra
{
public:
	Dijkstra()
	{
		list = nullptr;
		size = 0; //number of nodes
		departure = 0;
	};

	~Dijkstra()
	{
		clear();
	};

	void clear()
	{
		clear_list(list);
		size = 0;
		departure = 0;
	};

	//add an edge between nodes From and To, create this nodes if necessary
	void add_link(char* from, char* to, int val)
	{
		if (compare_str(from, to) && val > 0)
		{
			List* cur = list;
			Node* start = nullptr;
			Node* finish = nullptr;

			while (cur)//try to find a From or To node
			{
				if (compare_str(cur->node->name, from) == 0) start = cur->node;
				if (compare_str(cur->node->name, to) == 0) finish = cur->node;
				cur = cur->next;
			}

			if (!start) start = push_front_node(from);
			if (!finish) finish = push_front_node(to);

			start->link = (Link*)realloc(start->link, (start->number_link + 1) * sizeof(Link));
			start->link[start->number_link].out = start;
			start->link[start->number_link].in = finish;
			start->link[start->number_link].value = val;
			start->number_link++;
		}
		else
			if (compare_str(from, to) == 0) throw invalid_argument("Cant add edge with equal start and finish");
			else  throw invalid_argument("Cant add edge with value less 1");
	};

	//calculate distance from start to nodes
	void find_ways_from_departure(char* dep)
	{
		if (list)
		{
			set_start_to_head(dep);
			list->node->distance = 0;
			list->node->opened = 1;
			list->node->path = nullptr;

			Link* link_to_open = list->node->link;
			List* cur = list;
			Node* just_opened = list->node;
			for (int i = 0; i < size - 1; i++)
			{
				for (int i = 0; i < just_opened->number_link; i++)	// calculate or try relax distance
				{
					if (!(just_opened->link[i].in->opened))	// if neighbour is not opened
						if (just_opened->link[i].in->distance == -1)
							just_opened->link[i].in->distance = just_opened->link[i].out->distance + just_opened->link[i].value;
						else
							if (just_opened->link[i].in->distance > just_opened->link[i].out->distance + just_opened->link[i].value)
								just_opened->link[i].in->distance = just_opened->link[i].out->distance + just_opened->link[i].value;;
				}

				List* cur = list;
				int min = INT_MAX;	// find not opened node with the least distance
				while (cur)
				{
					if (cur->node->opened)			//check edges of opened nodes
						for (int j = 0; j < cur->node->number_link; j++)
							if (!(cur->node->link[j].in->opened))		//if node on the other side of this edge is not opened
								if (min > cur->node->link[j].value)
								{
									min = cur->node->link[j].value;		//find min
									link_to_open = &(cur->node->link[j]);
								}
					cur = cur->next;
				}

				link_to_open->in->opened = 1;	//mark found node as opened 
				link_to_open->in->path = string_concat(link_to_open->out->path, string_concat((char*)" ", link_to_open->out->name));
				just_opened = link_to_open->in;
			}
		}
		else throw runtime_error("The list is empty"); //нет списка
	};

	//check added edges
	void show_edges()
	{
		if (list)
		{
			List* cur = list;
			while (cur)
			{
				cout << cur->node->name << ":  ";
				for (int i = 0; i < cur->node->number_link; i++)
					cout << cur->node->link[i].out->name << cur->node->link[i].in->name << " " << cur->node->link[i].value << ",  ";
				cout << endl;
				cur = cur->next;
			}
		}
	}

	//print "name: path. distance" to every node
	void show_result()
	{
		if (list)
		{
			if (list->node->opened)	//if result is calculated
			{
				List* cur = list;
				while (cur)
				{
					if (cur == list)
						cout << cur->node->name << ": start. distance = " << cur->node->distance << endl;
					else
						if (cur->node->distance != -1)
							cout << cur->node->name << ":  " << cur->node->path << ". distance = " << cur->node->distance << endl;
						else
							cout << cur->node->name << ":  cant be reached from the departure node" << endl;
					cur = cur->next;
				}
			}
			else throw runtime_error("Result is not calculated");
		}
		else throw runtime_error("The list is empty");
	}

	//return distance of node with this name
	int get_distance(char* node)
	{
		if (list)
		{
			List* cur = list;
			while (cur)
			{
				if (compare_str(cur->node->name, node) == 0) return cur->node->distance;
				cur = cur->next;
			}
			throw invalid_argument("No node with this name");
		}
		else throw runtime_error("Can't be found in empty list");
	}

	void from_file(char* file_name)
	{
		char buff1[160];

		std::ifstream fin;
		fin.open(file_name);
		if (!fin)
			throw runtime_error("File not found");
		//go to the beginning of the file
		fin.seekg(fin.beg);
		while (!fin.eof())
		{
			fin.getline(buff1, 160);
			if (buff1[0])
				str_to_link((char*)buff1, ' ');
		}
		fin.close();
	}

	int count_distance(char* from, char* to)
	{
		find_ways_from_departure(from);
		return get_distance(to);
	}

private:
	List * list;
	int size;
	char departure;

	//move departure node to the head of list (errors: ia, re)
	void set_start_to_head(char* departure)
	{
		if (list)
		{
			//if departure node is not first in the list
			if (compare_str(list->node->name, departure))
			{
				List* cur = list;
				bool found = false;
				//find node
				while (cur->next && !found)
					if (compare_str(cur->next->node->name, departure))
						cur = cur->next;
					else
						found = true;
				//set first
				if (found)
				{
					List* to_first = cur->next;
					cur->next = cur->next->next;
					to_first->next = list;
					list = to_first;
				}
				else throw invalid_argument("No node with this name");
			}
		}
		else throw runtime_error("The list is empty");
	};

	//add a new node to the head of list 
	Node* push_front_node(char* name)
	{
		if (list)
		{
			List* n_node = new List;
			n_node->next = list;
			list = n_node;
		}
		else
		{
			list = new List;
			list->next = nullptr;
		}

		list->node = new Node;
		list->node->name = name;
		list->node->link = nullptr;
		list->node->number_link = 0;

		list->node->opened = 0;
		list->node->path = nullptr;
		list->node->distance = -1;

		size++;
		return list->node;
	}

	void clear_list(List* list)
	{
		if (list)
		{
			clear_list(list->next);
			if (list->node)
			{
				free(list->node->link);
				free(list->node);
			}
			free(list);
		}
	}

	void str_to_link(char* str, char split)
	{
		int j = 0;
		char* from = str_by_sym(str, split, j);
		char* to = str_by_sym(str, split, j);
		int val = str_to_int(str_by_sym(str, split, j));
		this->add_link(from, to, val);
	}
};