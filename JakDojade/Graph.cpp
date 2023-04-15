#include "Graph.h"

bool Graph::checkIfcontsins(int* container, int size, int item)
{
	for (int i = 0; i < size; i++) {
		if (container[i] == item)
			return true;
	}return false;
}

Graph::Graph(int Vcount) :Vcount(Vcount) {
	m_graph = new int* [Vcount];
	for (int i = 0; i < Vcount; i++) {
		m_graph[i] = new int[Vcount];
	}

	for (int i = 0; i < Vcount; i++) {
		for (int j = 0; j < Vcount; j++) {
			if (i == j)
				m_graph[i][j] = 0;
			else
				m_graph[i][j] = -1;
		}
	}
}

void Graph::djikstra(int first, int second, bool draw, List<City>* cites) {
	int* visited = new int[Vcount];
	int* distance = new int[Vcount];
	int* prevVer = new int[Vcount];
	int visitedCount = 0;

	for (int i = 0; i < Vcount; i++) {
		visited[i] = -1;
		distance[i] = -1;
		prevVer[i] = -1;
	}
	distance[first] = 0;
	visited[0] = first;
	visitedCount = 1;
	int current = first;
	int next = -1;
	while (current != second) {

		for (int i = 0; i < Vcount; i++) {
			if (m_graph[current][i] > 0) {
				if (!checkIfcontsins(visited, visitedCount, i)) {
					if (distance[i] == -1 || distance[i] > distance[current] + m_graph[current][i]) {
						distance[i] = distance[current] + m_graph[current][i];
						prevVer[i] = current;
					}
				}
			}
		}for (int i = 0; i < Vcount; i++) {
			if (prevVer[i] != -1 && i != current) {
				if (next == -1 || distance[i] < distance[next]) {
					if (!checkIfcontsins(visited, visitedCount, i))
						next = i;
				}
			}
		}
		visited[visitedCount] = next;
		visitedCount++;
		current = next;
		next = -1;
	}std::cout << distance[current];
	if (draw) {
		while (prevVer[prevVer[current]] != -1) {

			std::cout << " " << *cites->getById(prevVer[current])->name;
			current = prevVer[current];
		}
	}
	std::cout << std::endl;
	delete[] prevVer;
	delete[] distance;
	delete[] visited;
}

Graph::~Graph()
{
	for (int i = 0; i < Vcount; i++) {
		delete[] m_graph[i];
	}
}
