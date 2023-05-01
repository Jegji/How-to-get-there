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
	if(graph->m_graph[firstID][secondID]>duration || graph->m_graph[firstID][secondID]==-1)
	graph->m_graph[firstID][secondID] = duration;
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

void Board::exploreNeighbours(int x, int y, List<Pos>* visited, Queue* xQ, Queue* yQ,int* node_next_layer)
{
	int dx[] = { -1,1,0,0 };
	int dy[] = { 0,0,-1,+1 };
	int nextx;
	int nexty;
	for (int i = 0; i < 4; i++) {
		nextx = x + dx[i];
		nexty = y + dy[i];

		if (nextx < 0 || nexty < 0)
			continue;
		if (nextx >= size_x || nexty >= size_y)
			continue;
		if (board[nexty][nextx] != '*' && board[nexty][nextx] != '#')
			continue;
		Pos* nextpos = new Pos{ nextx,nexty };
		if (visited->contains(*nextpos))
			continue;

		xQ->enqueue(nextx);
		yQ->enqueue(nexty);
		visited->insert(nextpos);
		*node_next_layer +=1;
	}
}

void Board::readRoad(Pos pos,int idCity)
{
	int move_count = 0;
	int node_left = 1;
	int node_next_layer = 0;
	Queue xQ;
	Queue yQ;
	xQ.enqueue(pos.x);
	yQ.enqueue(pos.y);

	List<Pos> visited;
	visited.insert(&pos);

	int x, y;
	while (!xQ.isEmpty())
	{
		x = xQ.dequeue();
		y = yQ.dequeue();

		if (board[y][x] == '*' && move_count != 0) {
			int id = findCityByPos({ x,y });
			if (graph->m_graph[id][idCity] > move_count || graph->m_graph[id][idCity] == -1) {
				graph->m_graph[id][idCity] = move_count;
				graph->m_graph[idCity][id] = move_count;
			}
		}else
			exploreNeighbours(x, y,&visited,&xQ,&yQ,&node_next_layer);
		node_left--;
		if (node_left == 0) {
			std::cout << move_count <<" "<<xQ.getSize()<<" "<<visited.getSize()<<" "<<visited.getTime() << std::endl;
			node_left = node_next_layer;
			node_next_layer = 0;
			move_count++;
		}
	}
}

void Board::readRoads()
{
	for (int i = 0; i < cites.lng(); i++) {
		readRoad(cites[i]->pos,i);
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
