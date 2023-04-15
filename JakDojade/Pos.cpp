#include "Pos.h"

Pos::Pos() :x(-1), y(-1)
{
}

Pos::Pos(int x, int y) :x(x), y(y)
{
}

bool Pos::operator==(Pos& sec)
{
	if (x == sec.x && y == sec.y)return true;
	return false;
}
