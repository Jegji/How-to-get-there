#include "String.h"

String::String() {
    m_txt = nullptr;
    m_lng = 0;
}

String::String(char* txt, int lng) :m_txt(txt), m_lng(lng) {
}

char* String::txt() const
{
    return m_txt;
}

int String::lng() const
{
    return m_lng;
}

String::~String()
{
    //if(m_txt != nullptr && *m_txt>64)
    //delete[] m_txt;
}

bool String::operator==(String& txt)
{
    if (strcmp(m_txt, txt.m_txt) == 0)return true;
    return false;
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
    std::cout << str.m_txt;
    return os;
}
