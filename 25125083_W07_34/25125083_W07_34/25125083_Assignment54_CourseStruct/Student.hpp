//
//  Student.hpp
//  Learning
//
//  Created by Huy Nguyen on 25/11/25.
//

#ifndef Student_hpp
#define Student_hpp

#include "DynamicArray.hpp"
#include "String.hpp"
#include "Date.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>

template <typename T>
using List = DynamicArray<T>;

const int PRECISION = 2;

struct Student
{
    String id;
    String fullName;
    double gpa;
    String address;
    Date dob;
    
    bool operator==(const Student& other) const
    {
        // Suppose id is unique
        return strcmp(this->id, other.id);
    }
};

std::istream& operator >>(std::istream& is, Student& s);
std::ostream& operator <<(std::ostream& os, const Student& s);

void outputStudent(std::ostream& os, const Student& s);
void outputStudentList(std::ostream& os, List<Student> list);

void inputStudentFromConsole(Student& s);
void outputStudentToConsole(const Student& s);

bool inputStudentFromFile(Student& s, const String& filename);
bool outputStudentToFile(const Student& s, const String& filename);
bool outputStudentInfoToFile(const Student& s, const String& filename);
bool outputStudentListToFile(const List<Student> list, const String& filename);

String extractClass(const Student& s);

int compareByID(const Student& s1, const Student& s2);
int compareByGPA_ID(const Student& s1, const Student& s2);
int compareByName_ID(const Student& s1, const Student& s2);
int compareByFirstName_ID(const Student& s1, const Student& s2);
int compareByLastName_ID(const Student& s1, const Student& s2);
int compareByDOB_ID(const Student& s1, const Student& s2);


#endif /* Student_hpp */
