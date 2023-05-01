#include <iostream>
#include <stdio.h>
#include <time.h>

#include "Board.h"
#include "Graph.h"
void readCommands(Board* board) {
	int n;
	std::cin >> n;
	for (int i = 0; i < n; i++) {
		if (std::cin.peek() == '\n')std::cin.ignore(1);
		char buffor[32];
		std::cin.getline(buffor, 32, ' ');
		int lng = std::cin.gcount();
		char* txt = new char[lng];
		memcpy(txt, buffor, lng);
		String str(txt, lng);
		std::cin.getline(buffor, 32, ' ');
		lng = std::cin.gcount();
		char* txt2 = new char[lng];
		memcpy(txt2, buffor, lng);
		String str2(txt2, lng);
		int dur;
		std::cin >> dur;
		board->findConnection(str2, str, dur);
	}return;
}

int main() {
	
	int x;
	int y;
	std::cin >> x;
	std::cin >> y;
	clock_t start = clock();
	Board board(x, y);
	board.readCitys();
	board.readRoads();
	int n;
	std::cin >> n;
	for (int i = 0; i < n; i++) {
		board.readFlights();
	}
	//board.printGraph();
	readCommands(&board);
	clock_t end = clock(); 
	long double seconds = (float)(end - start) / CLOCKS_PER_SEC;
	std::cout << seconds;
}