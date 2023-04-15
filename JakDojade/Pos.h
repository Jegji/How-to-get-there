#pragma once
class Pos {
public:
	int x;
	int y;

	Pos();
	Pos(int x, int y);
	bool operator==(Pos& sec);
};

