#pragma once
#include <string.h>
#include <iostream>
class String {
private:
	char* m_txt;
	int m_lng;
public:
	String();
	String(char* txt, int lng);
	char* txt()const;
	int lng()const;
	~String();
	bool operator==(String& txt);
	friend std::ostream& operator<<(std::ostream& os, const String& str);

};

