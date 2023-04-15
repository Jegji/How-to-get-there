#pragma once
#include <iostream>
#include "City.h"
#include "List.h"
class Graph {
	int Vcount;
	bool checkIfcontsins(int* container, int size, int item);
public:
	int** m_graph;
	Graph(int Vcount);
	void djikstra(int first, int second, bool draw, List<City>* cites);
	~Graph();
};

