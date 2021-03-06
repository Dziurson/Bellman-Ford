#include "pch.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Graph1
{
private:

	class Edge
	{
	public:
		int a;
		int b;
		int weight;

		Edge(int a, int b, int weight)
		{
			this->a = a;
			this->b = b;
			this->weight = weight;
		}

		void print()
		{
			cout << a << ", " << b << ", " << weight << endl;
		}
	};

	int node_count;
	int edge_count;
	Edge** edges;
	int* distance;
	int* previous;

	Graph1(int node_count, int edge_count)
	{
		this->node_count = node_count;
		this->edge_count = edge_count;
		edges = new Edge*[edge_count];
		distance = new int[node_count];
		previous = new int[node_count];
	}

public:
	static Graph1* createFromFile(const char* filename)
	{
		ifstream _filestream;
		int _a, _b, _weight, _line_no = 0;
		string _line;
		_filestream.open(filename);
		Graph1* result = NULL;
		while (_filestream >> _a >> _b >> _weight)
		{
			if (_line_no == 0)
			{
				result = new Graph1(_a, _b);
				_line_no++;
				continue;
			}
			result->edges[_line_no - 1] = new Edge(_a, _b, _weight);
			_line_no++;
		}
		_filestream.close();
		return result;
	}
	void calculateFrom(int s)
	{
		for (int i = 0; i < node_count; i++)
		{
			distance[i] = INT32_MAX;
			previous[i] = -1;
		}
		distance[s] = 0;
		Edge* edge;
		for (int i = 0; i < node_count; i++)
		{
			for (int j = 0; j < edge_count; j++)
			{
				edge = edges[j];
				if (distance[edge->a] != INT32_MAX && distance[edge->a] + edge->weight < distance[edge->b])
				{
					distance[edge->b] = distance[edge->a] + edge->weight;
					previous[edge->b] = edge->a;
				}
			}
		}
	}
	void showGraph()
	{
		cout << "Edges: " << endl;
		for (int i = 0; i < edge_count; i++)
		{
			edges[i]->print();
		}
		cout << "Distance: " << endl;
		for (int i = 0; i < node_count; i++)
		{
			cout << distance[i] << " ";
		}
		cout << "\nPrevious: " << endl;
		for (int i = 0; i < node_count; i++)
		{
			cout << previous[i] << " ";
		}
		cout << endl;
	}

	~Graph1()
	{
		for (int i = 0; i < edge_count; i++)
		{
			delete edges[i];
		}
		delete[] edges;
		delete[] distance;
		delete[] previous;
	}
};

class Graph2
{
private:
	int node_count;
	int edge_count;
	int** matrix;
	int* distance;
	int* previous;

	Graph2(int node_count, int edge_count)
	{
		this->node_count = node_count;
		this->edge_count = edge_count;
		distance = new int[node_count];
		previous = new int[node_count];
		matrix = new int*[node_count];
		for (int i = 0; i < node_count; i++)
		{
			matrix[i] = new int[node_count];
			for (int j = 0; j < node_count; j++)
			{
				matrix[i][j] = 0;
			}
		}
	}

public:
	static Graph2* createFromFile(const char* filename)
	{
		ifstream _filestream;
		int _a, _b, _weight, _line_no = 0;
		string _line;
		_filestream.open(filename);
		Graph2* result = NULL;
		while (_filestream >> _a >> _b >> _weight)
		{
			if (_line_no == 0)
			{
				result = new Graph2(_a, _b);
				_line_no++;
				continue;
			}
			result->matrix[_a][_b] = _weight;
			_line_no++;
		}
		_filestream.close();
		return result;
	}
	void calculateFrom(int s)
	{
		for (int i = 0; i < node_count; i++)
		{
			distance[i] = INT32_MAX;
			previous[i] = -1;
		}
		distance[s] = 0;		
		for (int i = 0; i < node_count; i++)
		{
			for (int j = 0; j < node_count; j++)
			{				
				for (int k = 0; k < node_count; k++)
				{
					if (distance[j] != INT32_MAX && matrix[j][k] != 0 && distance[j] + matrix[j][k] < distance[k])
					{
						distance[k] = distance[j] + matrix[j][k];
						previous[k] = j;
					}
				}
			}
		}
	}
	void showGraph()
	{
		cout << "Edges: " << endl;
		for (int i = 0; i < node_count; i++)
		{
			for (int j = 0; j < node_count; j++)
			{
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
		cout << "Distance: " << endl;
		for (int i = 0; i < node_count; i++)
		{
			cout << distance[i] << " ";
		}
		cout << "\nPrevious: " << endl;
		for (int i = 0; i < node_count; i++)
		{
			cout << previous[i] << " ";
		}
		cout << endl;
	}

	~Graph2()
	{
		for (int i = 0; i < node_count; i++)
		{
			delete matrix[i];
		}
		delete[] matrix;
		delete[] distance;
		delete[] previous;
	}
};

int main()
{
	Graph1* graph1 = Graph1::createFromFile("data.txt");
	Graph2* graph2 = Graph2::createFromFile("data.txt");
	graph1->calculateFrom(0);
	graph1->showGraph();
	graph2->calculateFrom(0);
	graph2->showGraph();
	delete graph1;
	delete graph2;
	cin.get();
	cin.get();
}


