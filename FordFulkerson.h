#pragma once
#include <string.h>
#include  <time.h>
#include  <conio.h>
#include  <iostream>
#include  <malloc.h>
#include  <fstream>
#include "List.h"

using namespace std;

int str_to_int(char* s)
{
	if (s == NULL)
		return NULL;

	if (*s == '\0')
		return NULL;

	int i = 0,
		n = 0,
		a = 0,
		sign;

	if (*s == '-')
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
			n *= 10;
			a = ((int)s[i]) - 48;
			n += a;
			i++;
		}
		else
		{
			n = NULL;
			flag = 0;
		}
	} while (s[i] != '\0' && flag);

	n *= sign;
	return n;
}

template <class T>
T* cut_array(T* array, size_t& array_length, size_t new_length)
{
	if (array_length > new_length) return array;
	T* new_array = (T*)malloc(new_length * sizeof(T));
	for (int i = 0; i < new_length; i++)
		new_array[i] = array[i];
	array_length = new_length;
	return new_array;
}

class Node;

typedef struct Edges
{
	Node* begin;
	Node* end;
	int bandwidth;
	int flow;
}Edge;

class Node
{
public:
	char name;
	Edge** out;
	Edge** in;
	int number_out;
	int number_in;

	Node(char n_name) { name = n_name; in = nullptr;  out = nullptr; number_out = 0; number_in = 0; }
	~Node() { if (out) free(out); if (in) free(in); }

	Edge** find_way(Node* sink, Edge** way, size_t& way_length)
	{
		size_t len = way_length;
		for (int i = 0; i < way_length; i++)
		{
			cout << way[i]->begin->name << way[i]->end->name << "[" << way[i]->flow << "/" << way[i]->bandwidth << "]";
		}
		cout << endl;
		if (!this) return nullptr;
		/*cout << "  cur node: " << name << endl;
		cout << "     ";
		for (int j = 0; j < number_out; j++)
		{
			cout << out[j]->end->name << "{" << out[j]->flow << "/" << out[j]->bandwidth << "}";
		}cout << endl;
		cout << "     ";
		for (int j = 0; j < number_in; j++)
		{
			cout << in[j]->begin->name << "{" << in[j]->flow << "/" << in[j]->bandwidth << "}";
		}cout << endl;
		*/
		if (this == sink) return way;
		way = (Edge**)realloc(way, (len + 1) * sizeof(Edge*));
		if (out || in)
		{
			Edge** current_way = nullptr;
			for (int i = 0; i < number_out; i++)
			{
				bool no_cycles = true;
				for (int j = 0; j < way_length && no_cycles; j++)
					if (way[j] == out[i])
						no_cycles = false;
				//cout << "     cur edge: " << out[i]->begin->name << out[i]->end->name << endl;
				//
				if (out[i]->flow < out[i]->bandwidth && no_cycles)
				{
					way[way_length] = out[i];
					way_length = len + 1;
					current_way = out[i]->end->find_way(sink, way, way_length);
					if (current_way)
						return current_way;
					way = cut_array(way, way_length, len + 1);
				}

			}
			for (int i = 0; i < number_in; i++)
			{
				bool no_cycles = true;
				for (int j = 0; j < way_length && no_cycles; j++)
					if (way[j] == in[i])
						no_cycles = false;
				//cout << "     cur edge: " << in[i]->begin->name << in[i]->end->name << endl;
				//
				if (in[i]->flow > 0 && no_cycles)
				{
					way[way_length] = in[i];
					way_length = len + 1;
					current_way = in[i]->begin->find_way(sink, way, way_length);
					if (current_way)
						return current_way;
					way = cut_array(way, way_length, len + 1);
				}

			}
		}
		return nullptr;
	}
};

class Web
{
private:
	Node * source;
	Node* sink;
	Edge** edges; //array of pointers to edges
	int number_edges;
	bool calculated;

	void res_show_in_width(Node* current)
	{
		for (int i = 0; i < current->number_out; i++)
		{
			cout << current->name << (current->out[i])->end->name << " " << (current->out[i])->flow << "/" << (current->out[i])->bandwidth << ";  "/*<< endl*/;
			res_show_in_width(current->out[i]->end);
		}
	};

public:
	Web()
	{
		source = nullptr;
		sink = nullptr;
		edges = nullptr;
		number_edges = 0;
		calculated = 0;
	};

	~Web()
	{
		if (source) free(source);
		if (edges) 	free(edges);
	}

	void add_edge(char n_begin, char n_end, int n_bandwidth)
	{
		if ((n_begin != n_end) && n_bandwidth > 0)
		{
			bool create = true;
			Node* from = nullptr;
			Node* to = nullptr;

			for (int i = 0; i < number_edges && create; i++)	//find out if nodes with this name exist
			{
				//if such edge alreadry exist
				if (edges[i]->begin->name == n_begin && edges[i]->end->name == n_end && edges[i]->bandwidth == n_bandwidth) create = false;

				//if any node already exist
				if (edges[i]->begin->name == n_begin) from = edges[i]->begin;
				if (edges[i]->end->name == n_begin) from = edges[i]->end;

				if (edges[i]->begin->name == n_end) to = edges[i]->begin;
				if (edges[i]->end->name == n_end) to = edges[i]->end;
			}

			if (create)
			{
				if (!from) from = new Node(n_begin);
				if (!to) to = new Node(n_end);

				if (n_begin == 's') source = from;
				if (n_end == 't') sink = to;

				from->out = (Edge**)realloc(from->out, (from->number_out + 1) * sizeof(Edge*));
				to->in = (Edge**)realloc(to->in, (to->number_in + 1) * sizeof(Edge*));

				//initialize the edge
				from->out[from->number_out] = (Edge*)malloc(sizeof(Edge));
				from->out[from->number_out]->begin = from;
				from->out[from->number_out]->end = to;
				from->out[from->number_out]->bandwidth = n_bandwidth;
				from->out[from->number_out]->flow = 0;

				to->in[to->number_in] = from->out[from->number_out];

				edges = (Edge**)realloc(edges, (number_edges + 1) * sizeof(Edge*));
				edges[number_edges] = from->out[from->number_out];

				number_edges++;
				from->number_out++;
				to->number_in++;

			}
			else
				throw invalid_argument("Trying add an existing edge");
		}
		else
		{
			if (n_begin == n_end) throw invalid_argument("Trying to add loop edge");
			else throw invalid_argument("Trying to add edge with bandwidth less 1");
		}
	}

	void FordFulkerson()
	{
		Edge** path = nullptr;
		size_t path_length = 0;
		path = source->find_way(sink, path, path_length);	//find a find_way way from source to sink
		if (!path) throw runtime_error("Can't find way from source to sink");
		while (path)
		{
			/*cout << "\nbefore:";
			for (int i = 0; i < path_length; i++)
			{
				cout << path[i]->begin->name << path[i]->end->name << "[" << path[i]->flow << "/" << path[i]->bandwidth << "]";
			}
			cout << endl;*/
			int min_bandwidth = path[0]->bandwidth - path[0]->flow;
			for (int i = 1; i < path_length; i++)
			{
				if (path[i - 1]->end == path[i]->begin)
				{
					if (path[i]->bandwidth < min_bandwidth)
						min_bandwidth = path[i]->bandwidth - path[i]->flow;
				}
				else
					if (path[i]->flow < min_bandwidth)
						min_bandwidth = path[i]->flow;
			}

			path[0]->flow += min_bandwidth;
			for (int i = 1; i < path_length; i++)
				if (path[i - 1]->end == path[i]->begin)
					path[i]->flow += min_bandwidth;
				else
					path[i]->flow -= min_bandwidth;

			cout << "\nafter: ";
			for (int i = 0; i < path_length; i++)
				cout << path[i]->begin->name << path[i]->end->name << "[" << path[i]->flow << "/" << path[i]->bandwidth << "]";
			path_length = 0;
			
			path = source->find_way(sink, path, path_length);	//find a find_way way from source to sink
		}

	}

	void show_edges()
	{
		for (int i = 0; i < number_edges; i++)
			cout << edges[i]->begin->name << edges[i]->end->name << " " << edges[i]->flow << "/" << edges[i]->bandwidth << ";  " /*<< endl*/;
		cout << endl;
	};

	int summ_flow()
	{
		if (source)
		{
			int res = 0;
			for (int i = 0; i < source->number_out; i++)
				res += source->out[i]->flow;
			return res;
		}
		else throw runtime_error("No source node to count flow");
	};

	void from_file()
	{
		char buff[160];

		std::ifstream fin;
		fin.open("text.txt");
		if (!fin)
			throw runtime_error("File not found");
		//go to the beginning of the file
		fin.seekg(fin.beg);
		while (!fin.eof())
		{
			fin.getline(buff, 160);
			if (buff[0])
			{
				char out = 0;
				char in = 0;
				int bandwidth = 0;
				for (int i = 0; i < strlen(buff); i++)
				{
					if (buff[i] != ' ' && out == 0) out = buff[i];		//set source name
					else
						if (buff[i] != ' ' && in == 0) in = buff[i];	//set fiish name
						else
							if (buff[i] != ' ')							//set bandwidth
							{
								int j = i;
								for (; j < strlen(buff); j++);
								char* to_int = (char*)malloc((1 + j - i) * sizeof(char));
								for (int n = 0; n < j - i; n++)
									to_int[n] = buff[i + n];
								to_int[j - i] = 0;
								add_edge(out, in, str_to_int(to_int));
							}
				}
			}
		}
		fin.close();
	}

};