//
//  Course.cpp
//  Learning
//
//  Created by Huy Nguyen on 26/11/25.
//

#include "Course.hpp"

std::istream& operator >>(std::istream& is, Course& c)
{
    getline(is, c.id);
    getline(is, c.name);
    size_t studentNum;
    is >> studentNum;
    is.ignore();
    
    for (size_t i = 0; i < studentNum; ++i)
    {
        Student s;
        is >> s;
        c.attendants.add(s);
    }
    
    String temp;
    getline(is, temp);
    if (temp == "Opening") c.isOpening = true;
    if (temp == "Closing") c.isOpening = false;
    
    is >> c.minStudent;
    is >> c.maxStudent;
    is.ignore();
    
    return is;
}

std::ostream& operator <<(std::ostream& os, const Course& c)
{
    os << c.id << '\n';
    os << c.name << '\n';
    os << c.attendants.size << '\n';
    
    for (int i = 0; i < c.attendants.size; ++i) {
        os << c.attendants[i];
    }
    
    if (c.isOpening) os << "Opening\n";
    else os << "Closing\n";
    os << c.minStudent << '\n';
    os << c.maxStudent << '\n';
    
    return os;
}

bool inputCourseFromFile(Course& c, const String& filename)
{
    std::ifstream fin;
    fin.open(filename);
    if (!fin) {
        std::cout << "File cannot be opened.\n";
        return false;
    }

    fin >> c;
    
    fin.close();
    return true;
}

bool outputCourseToSave(const Course& c, const String& filename)
{
    std::ofstream fout;
    fout.open(filename);
    if (!fout) {
        std::cout << "File cannot be opened.\n";
        return false;
    }
    
    fout << c;
    
    fout.close();
    return true;
}

bool outputCourseToRead(const Course& c, const String& filename)
{
    std::ofstream fout;
    fout.open(filename);
    if (!fout) {
        std::cout << "File cannot be opened.\n";
        return false;
    }
    
    fout << "Course ID: " << c.id << '\n';
    fout << "Course name: " << c.name << '\n';
    fout << "Number of students: " << c.attendants.size << '\n';
    fout << "List of student:\n";
    outputStudentList(fout, c.attendants);
    String temp = (c.isOpening) ? "Opening" : "Closing";
    fout << "Course is " << temp << ".\n";
    fout << "Min student: " << c.minStudent << '\n';
    fout << "Max student: " << c.maxStudent << '\n';
    
    fout.close();
    return true;
}

bool addStudent(Course& c, const Student& s)
{
    if (!c.isOpening) {
        std::cout << "Course is closing.\n";
        return false;
    }
    if (c.attendants.size >= c.maxStudent) {
        std::cout << "Course is full.\n";
        return false;
    }
    
    if (c.attendants.indexOf(s) != -1) {
        std::cout << "Student already exists in course.\n";
        return false;

    }
    
    c.attendants.add(s);
    return true;
}

bool removeStudent(Course& c, const Student& s)
{
    if (c.attendants.size <= c.minStudent)
    {
        std::cout << "Course must have at least " << c.minStudent << " students.\n";
        return false;
    }
    
    int index = c.attendants.indexOf(s);
    if (index == -1) {
        std::cout << "Student not found in course.\n";
        return false;
    }
    
    c.attendants.removeAt(index);
    return true;
}

List<Student> GetBornThisMonth(const Course& c)
{
    Date today = getTodayDate();
    List<Student> list;
    
    for (int i = 0; i < c.attendants.size; ++i) {
        if (c.attendants[i].dob.month == today.month) {
            list.add(c.attendants[i]);
        }
    }
    
    return list;
}

List<Student> GetBornThisDate(const Course& c)
{
    Date today = getTodayDate();
    List<Student> list;
    
    for (int i = 0; i < c.attendants.size; ++i) {
        if (c.attendants[i].dob.month == today.month && c.attendants[i].dob.day == today.day) {
            list.add(c.attendants[i]);
        }
    }
    
    return list;
}

List<Student> GetLegalDrivingLicenses(const Course& c)
{
    List<Student> list;
    
    for (int i = 0; i < c.attendants.size; ++i) {
        Date age = calculateAge(c.attendants[i].dob);
        if (age.year >= 18) {
            list.add(c.attendants[i]);
        }
    }
    
    return list;
}

List<Student> GetStudentsOfClass(const Course& c, const String& className)
{
    List<Student> list;
    
    for (int i = 0; i < c.attendants.size; ++i) {
        if (extractClass(c.attendants[i]) == className) {
            list.add(c.attendants[i]);
        }
    }
    
    return list;
}

Student GetStudentWithId(const Course& c, const String& id)
{
    for (int i = 0; i < c.attendants.size; ++i) {
        if (c.attendants[i].id == id) {
            return c.attendants[i];
        }
    }
    
    Student emptyS;
    emptyS.id[0] = '\0';
    return emptyS;
}

List<Student> GetStudentsWithName(const Course& c, const String& searchName)
{
    String searchNameLower = searchName.toLowerCase();
    String studentNameLower;
    List<Student> list;
    
    for (int i = 0; i < c.attendants.size; ++i) {
        studentNameLower = c.attendants[i].fullName.toLowerCase();
        if (strstr(studentNameLower, searchNameLower) != nullptr) {
            list.add(c.attendants[i]);
        }
    }
    
    return list;
}

void sortStudentById(Course& c) { c.attendants.sort(compareByID); }

void sortStudentByFirstName(Course& c) { c.attendants.sort(compareByFirstName_ID); }

void sortStudentByGpa(Course& c) { c.attendants.sort(compareByGPA_ID); }

void sortStudentByDOB(Course& c) { c.attendants.sort(compareByDOB_ID); }
