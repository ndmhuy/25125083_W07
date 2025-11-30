//
//  String.hpp
//  Learning
//
//  Created by Huy Nguyen on 25/11/25.
//

#ifndef String_hpp
#define String_hpp

#include "DynamicArray.hpp"

#include <iostream>

struct String
{
    DynamicArray<char> data;
    
    String()
    {
        data.add('\0');
    }
    
    size_t size() const
    {
        return data.size - 1;
    }
    
    const char* c_str() const { return data.data; }
    
    operator const char*() const { return this->c_str(); }
    
    String(const char* str)
    {
        size_t len = strlen(str) + 1;
        for (int i = 0; i < len; ++i)
            data.add(str[i]);
        data.add('\0');
    }
    
    String& operator=(const char* str)
    {
        data.size = 0;
        
        size_t len = strlen(str);
        for (size_t i = 0; i < len; ++i) {
            data.add(str[i]);
        }
        
        data.add('\0');
        return *this;
    }
    
    String& operator=(const String& other)
    {
        if (this != &other)
        {
            data = other.data;
        }
        return *this;
    }
    
    String(const String& other) : data(other.data) { }
    
    char& operator[](size_t index)
    {
        return data[index];
    }
    
    const char& operator[](size_t index) const{
        return data[index];
    }
    
    bool operator ==(const String& other) const
    {
        return strcmp(this->c_str(), other.c_str()) == 0;
    }
    
    bool operator==(const char* other) const
    {
        return strcmp(this->c_str(), other);
    }
    
    void replace(const char* from, const char* to)
    {
        if (!from || !to) return;
        size_t lenFrom = strlen(from);
        if (lenFrom == 0) return;
        size_t lenTo = strlen(to);
        
        String result;
        result.data.size = 0;
        size_t n = this->size();
        const char* currentStr = this->c_str();
        
        size_t i = 0;
        while (i < n)
        {
            if (strncmp(currentStr + i, from, lenFrom) == 0)
            {
                for (size_t k = 0; k < lenTo; ++k)
                    result.data.add(to[k]);
                i += lenFrom;
            }
            else result.data.add(currentStr[i++]);
        }
        result.data.add('\0');
        
        *this = result;
    }
    
    String substring(size_t start, size_t end) const
    {
        String result;
        result.data.size = 0;
        
        const char* p = this->data.data + start;
        while (p < this->data.data + end)
            result.data.add(*p++);
        result.data.add('\0');
        
        return result;
    }
    
    String toLowerCase() const
    {
        String result;
        result.data.size = 0;
        
        const char* p = this->data.data;
        while (*p != '\0')
        {
            result.data.add(*p++);
        }
        result.data.add('\0');
        
        return result;
    }
    
    void normalize()
    {
        size_t n = this->size();
        size_t i = 0, j = n - 1;
        
        while (isspace(this->data[i])) ++i;
        while (isspace(this->data[j])) --j;
        
        String normalized;
        normalized.data.size = 0;
        
        for (size_t k = i; k <= j; ++k) {
            if (isspace(this->data[k]))
            {
                normalized.data.add(' ');
                while (isspace(this->data[k])) ++k;
            }
            normalized.data.add(this->data[k]);
        }
        normalized.data.add('\0');
        *this = normalized;
    }
};

std::ostream& operator <<(std::ostream& os, const String& s);
std::istream& operator >>(std::istream& is, String& s);

std::istream& getline(std::istream& is, String& s);

String operator +(const String& a, const String& b);

String getFirstName(const String& fullName);
String getLastName(const String& fullName);

#endif /* String_hpp */
