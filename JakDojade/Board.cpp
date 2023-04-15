#include "Board.h"

Board::Board(int x, int y) :size_x(x), size_y(y)
{
	board = new char* [y];
	for (int i = 0; i < y; i++) {
		board[i] = new char[x];
	}graph = nullptr;
}

void Board::print()
{
	for (int i = 0; i < size_y; i++) {
		for (int j = 0; j < size_x; j++) {
			std::cerr << board[i][j];
		}std::cerr << std::endl;
	}
}

void Board::printGraph() {
	std::cerr << std::endl;
	for (int i = 0; i < cites.lng(); i++) {
		for (int j = 0; j < i + 1; j++) {
			int dur = graph->m_graph[i][j];
			if (dur != -1)
				std::cerr << *cites[i]->name << " " << *cites[j]->name << " " << dur << std::endl;

		}
	}
}

void Board::findCites() {
	for (int i = 0; i < cites.lng(); i++) {
		findCity(i);
	}
}

void Board::findCity(int id) {
	City* temp = cites[id];
	int cityX = temp->pos.x;
	int cityY = temp->pos.y;
	Pos firstLetter;
	Pos lastLetter;
	if (cityX != 0 && cityY + 1 != size_y && board[cityY + 1][cityX - 1] != '.' && board[cityY + 1][cityX - 1] != '#' && board[cityY + 1][cityX - 1] != '*') {
		firstLetter = findFirstLetter(cityX - 1, cityY + 1);
		lastLetter = findLastLetter(cityX - 1, cityY + 1);
	}
	else if (cityX != 0 && board[cityY][cityX - 1] != '.' && board[cityY][cityX - 1] != '#' && board[cityY][cityX - 1] != '*') {
		firstLetter = findFirstLetter(cityX - 1, cityY);
		lastLetter = findLastLetter(cityX - 1, cityY);
	}
	else if (cityX != 0 && cityY != 0 && board[cityY - 1][cityX - 1] != '.' && board[cityY - 1][cityX - 1] != '#' && board[cityY - 1][cityX - 1] != '*') {
		firstLetter = findFirstLetter(cityX - 1, cityY - 1);
		lastLetter = findLastLetter(cityX - 1, cityY - 1);
	}
	else if (cityX + 1 != size_x && cityY + 1 != size_y && board[cityY + 1][cityX + 1] != '.' && board[cityY + 1][cityX + 1] != '#' && board[cityY + 1][cityX + 1] != '*') {
		firstLetter = findFirstLetter(cityX + 1, cityY + 1);
		lastLetter = findLastLetter(cityX + 1, cityY + 1);
	}
	else if (cityX + 1 != size_x && board[cityY][cityX + 1] != '.' && board[cityY][cityX + 1] != '#' && board[cityY][cityX + 1] != '*') {
		firstLetter = findFirstLetter(cityX + 1, cityY);
		lastLetter = findLastLetter(cityX + 1, cityY);
	}
	else if (cityX + 1 != size_x && cityY != 0 && board[cityY - 1][cityX + 1] != '.' && board[cityY - 1][cityX + 1] != '#' && board[cityY - 1][cityX + 1] != '*') {
		firstLetter = findFirstLetter(cityX + 1, cityY - 1);
		lastLetter = findLastLetter(cityX + 1, cityY - 1);
	}
	else if (cityY != size_y && board[cityY + 1][cityX] != '.' && board[cityY + 1][cityX] != '#' && board[cityY + 1][cityX] != '*') {
		firstLetter = findFirstLetter(cityX, cityY + 1);
		lastLetter = findLastLetter(cityX, cityY + 1);
	}
	else if (cityY != 0 && board[cityY - 1][cityX] != '.' && board[cityY - 1][cityX] != '#' && board[cityY - 1][cityX] != '*') {
		firstLetter = findFirstLetter(cityX, cityY - 1);
		lastLetter = findLastLetter(cityX, cityY - 1);
	}

	int lng = lastLetter.x - firstLetter.x + 1;
	char* txt = new char[lng + 1];
	memcpy(txt, board[firstLetter.y] + firstLetter.x, lng);
	txt[lng] = '\0';
	cites[id]->name = new String(txt, lng);
}

int Board::findCityByPos(Pos pos)
{
	for (int i = 0; i < cites.lng(); i++) {
		if (pos == cites[i]->pos)return i;
	}return -1;
}

int Board::findCityByString(String string)
{
	for (int i = 0; i < cites.lng(); i++) {
		if (string == *cites[i]->name)return i;
	}return -1;
}

int Board::cityCount() const
{
	return cites.lng();
}

char* Board::operator[](int y)
{
	return board[y];
}

Pos Board::findFirstLetter(int x, int y) {
	while (x != 0 && board[y][x - 1] != '*' && board[y][x - 1] != '.' && board[y][x - 1] != '#') {
		x--;
	}return Pos(x, y);
}

Pos Board::findLastLetter(int x, int y)
{
	while (x + 1 != size_x && board[y][x + 1] != '*' && board[y][x + 1] != '.' && board[y][x + 1] != '#') {
		x++;
	}return Pos(x, y);
}

void Board::createFlight(String const first, String const second, int duration)
{
	int firstID = findCityByString(first);
	int secondID = findCityByString(second);
	if (firstID == -1 || secondID == -1)return;

	graph->m_graph[firstID][secondID] = duration;
}

void Board::readRoad(Pos pos, Dir dir, List<int>* ends, List<int>* lngs, int lng, List<Pos>* cords)
{
	char temp;
	int* val;
	int* Llng;
	cords->insert(new Pos(pos));
	if (pos.x != 0 && dir != left && !cords->contains({ pos.x - 1,pos.y })) {
		temp = board[pos.y][pos.x - 1];
		if (temp == '#') {
			readRoad({ pos.x - 1,pos.y }, right, ends, lngs, lng + 1, cords);
		}
		if (temp == '*') {
			Llng = new int(lng + 1);
			lngs->insert(Llng);
			val = new int(findCityByPos({ pos.x - 1,pos.y }));
			ends->insert(val);
		}
	}
	if (pos.x + 1 != size_x && dir != right && !cords->contains({ pos.x + 1,pos.y })) {
		temp = board[pos.y][pos.x + 1];
		if (temp == '#') {
			readRoad({ pos.x + 1,pos.y }, left, ends, lngs, lng + 1, cords);
		}
		if (temp == '*') {
			Llng = new int(lng + 1);
			lngs->insert(Llng);
			val = new int(findCityByPos({ pos.x + 1,pos.y }));
			ends->insert(val);
		}
	}
	if (pos.y != 0 && dir != down && !cords->contains({ pos.x ,pos.y - 1 })) {
		temp = board[pos.y - 1][pos.x];
		if (temp == '#') {
			readRoad({ pos.x,pos.y - 1 }, up, ends, lngs, lng + 1, cords);
		}
		if (temp == '*') {
			Llng = new int(lng + 1);
			lngs->insert(Llng);
			val = new int(findCityByPos({ pos.x ,pos.y - 1 }));
			ends->insert(val);
		}
	}
	if (pos.y + 1 != size_y && dir != up && !cords->contains({ pos.x,pos.y + 1 })) {
		temp = board[pos.y + 1][pos.x];
		if (temp == '#') {
			readRoad({ pos.x,pos.y + 1 }, down, ends, lngs, lng + 1, cords);
		}
		if (temp == '*') {
			Llng = new int(lng + 1);
			lngs->insert(Llng);
			val = new int(findCityByPos({ pos.x ,pos.y + 1 }));
			ends->insert(val);
		}
	}
	return;
}

void Board::readCitys() {
	char sign;
	int curX = 0;
	int curY = -1;
	while (curY != size_y) {
		sign = std::cin.get();
		switch (sign)
		{
		case'\n':
			curX = 0;
			curY++;
			break;
		case'*':
			cites.insert(new City(curY, curX));
			board[curY][curX] = sign;
			curX++;
			break;
		default:
			board[curY][curX] = sign;
			curX++;
			break;
		}
	}
	std::cout << std::endl;
	findCites();
	graph = new Graph(cites.lng());
}

void Board::readRoads()
{
	List<int> ends;
	List<int> lngs;
	List<Pos> cords;
	for (int i = 0; i < cites.lng(); i++) {
		readRoad(cites[i]->pos, none, &ends, &lngs, 0, &cords);
		if (ends.lng() != 0) {
			for (int j = 0; j < ends.lng(); j++) {
				if (graph->m_graph[i][*ends[j]] == -1 || graph->m_graph[i][*ends[j]] > *lngs[j]) {
					graph->m_graph[i][*ends[j]] = *lngs[j];
					graph->m_graph[*ends[j]][i] = *lngs[j];
				}
			}
		}
		cords.erase();
		ends.erase();
		lngs.erase();
	}
}

void Board::readFlights() {
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
	createFlight(str2, str, dur);
}

void Board::findConnection(String str, String str2, bool draw)
{
	int first = findCityByString(str);
	int second = findCityByString(str2);
	if (first == -1 || second == -1)return;
	if (first == second) {
		std::cout << 0 << " " << std::endl;
		return;
	}
	graph->djikstra(first, second, draw, &cites);
}

Graph* Board::getGraph()
{
	return graph;
}
