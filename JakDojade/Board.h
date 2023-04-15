#pragma once
#include <iostream>
#include "String.h"
#include "List.h"
#include "Graph.h"
enum Dir {
	up,
	down,
	left,
	right,
	none
};
class Board {
private:
	int size_x;
	int size_y;
	char** board;//[y][x] ^y  ->x
	List<City> cites;
	Graph* graph;

	void findCites();
	void findCity(int id);
	int findCityByPos(Pos pos);
	int findCityByString(String string);
	Pos findFirstLetter(int x, int y);
	Pos findLastLetter(int x, int y);
	void createFlight(String first, String second, int duration);
	void readRoad(Pos pos, Dir dri, List<int>* ends, List<int>* lngs, int lng, List<Pos>* cords);
public:
	Board(int x, int y);

	void print();
	void printGraph();
	void readCitys();
	void readRoads();
	void readFlights();
	void findConnection(String str, String str2, bool board);
	Graph* getGraph();
	int cityCount()const;
	char* operator[](int y);
};

