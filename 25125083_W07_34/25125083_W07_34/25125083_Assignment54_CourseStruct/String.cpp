//
//  String.cpp
//  Learning
//
//  Created by Huy Nguyen on 25/11/25.
//

#include "String.hpp"

std::ostream& operator <<(std::ostream& os, const String& s)
{
    os << s.c_str();
    return os;
}

std::istream& operator >>(std::istream& is, String& s)
{
    char buffer[1000];
    is >> buffer;
    s = buffer;
    return is;
}

std::istream& getline(std::istream& is, String& s)
{
    char buffer[1000];
    is.getline(buffer, 1000);
    s = buffer;
    return is;
}

String operator +(const String& a, const String& b)
{
    String result;
    result.data.size = 0;
    const char* p = a.data.data;
    
    while (*p != '\0')
        result.data.add(*p++);
    p = b.data.data;
    
    while (*p != '\0')
        result.data.add(*p++);
    result.data.add('\0');
    
    return result;
}

String getFirstName(const String& fullName)
{
    String firstName;
    firstName.data.size = 0;
    
    const char* p = fullName.data.data;
    while (!isspace(*p))
        firstName.data.add(*p++);
    firstName.data.add('\0');
    
    return firstName;
}

String getLastName(const String& fullName)
{
    String lastName;
    lastName.data.size = 0;
    
    const char* p = fullName.data.data;
    while (!isspace(*p)) ++p;
    ++p;
    
    while (*p != '\0')
        lastName.data.add(*p++);
    lastName.data.add('\0');
    
    return lastName;
}
