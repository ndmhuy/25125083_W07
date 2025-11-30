//
//  Course.hpp
//  Learning
//
//  Created by Huy Nguyen on 26/11/25.
//

#ifndef Course_hpp
#define Course_hpp

#include "DynamicArray.hpp"
#include "String.hpp"
#include "Date.hpp"
#include "Student.hpp"

#include <iostream>
#include <fstream>
#include <cstring>

template <typename T>
using List = DynamicArray<T>;

struct Course
{
    String id;
    String name;
    List<Student> attendants;
    bool isOpening;
    size_t minStudent;
    size_t maxStudent;
};

std::istream& operator >>(std::istream& is, Course& c);
std::ostream& operator <<(std::ostream& os, const Course& c);

bool inputCourseFromFile(Course& c, const String& filename);
bool outputCourseToSave(const Course& c, const String& filename);
bool outputCourseToRead(const Course& c, const String& filename);

bool addStudent(Course& c, const Student& s);
bool removeStudent(Course& c, const Student& s);

List<Student> GetBornThisMonth(const Course& c);
List<Student> GetBornThisDate(const Course& c);
List<Student> GetLegalDrivingLicenses(const Course& c);
List<Student> GetStudentsOfClass(const Course& c, const String& className);
Student GetStudentWithId(const Course& c, const String& id);
List<Student> GetStudentsWithName(const Course& c, const String& searchName);

void sortStudentById(Course& c);
void sortStudentByFirstName(Course& c);
void sortStudentByGpa(Course& c);
void sortStudentByDOB(Course& c);

#endif /* Course_hpp */
