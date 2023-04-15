#pragma once
#include "String.h"
#include "Pos.h"
class City {
public:
	Pos pos;
	String* name;
	City(int y, int x);
	City(Pos pos);
};

