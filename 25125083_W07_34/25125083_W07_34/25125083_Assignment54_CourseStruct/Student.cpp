//
//  Student.cpp
//  Learning
//
//  Created by Huy Nguyen on 25/11/25.
//

#include "Student.hpp"

std::istream& operator >>(std::istream& is, Student& s)
{
    getline(is, s.id);
    s.id.normalize();
    
    getline(is, s.fullName);
    s.fullName.normalize();
    
    is >> s.gpa;
    is.ignore();
    
    getline(is, s.address);
    s.address.normalize();
    
    is >> s.dob;
    
    return is;
}

std::ostream& operator <<(std::ostream& os, const Student& s)
{
    os << s.id << '\n';
    os << s.fullName << '\n';
    os << std::fixed << std::setprecision(PRECISION) << s.gpa << '\n';
    os << s.address << '\n';
    os << s.dob << '\n';
    
    return os;
}

void outputStudent(std::ostream& os, const Student& s)
{
    os << "ID: " << s.id << '\n';
    os << "Full name: " << s.fullName << '\n';
    os << "GPA: " << std::fixed << std::setprecision(2) << s.gpa << '\n';
    os << "Address: " << s.address << '\n';
    os << "Date of birth: " << s.dob << '\n';
}

void outputStudentList(std::ostream& os, List<Student> list)
{
    for (int i = 0; i < list.size; ++i) {
        os << i + 1 << ". ";
        outputStudent(os, list[i]);
    }
}

void inputStudentFromConsole(Student& s)
{
    std::cout << "Enter ID: ";
    getline(std::cin, s.id);
    s.id.normalize();
    
    std::cout << "Enter full name: ";
    getline(std::cin, s.fullName);
    s.fullName.normalize();
    
    std::cout << "Enter GPA: ";
    std::cin >> s.gpa;
    std::cin.ignore();
    
    std::cout << "Enter address: ";
    getline(std::cin, s.address);
    s.address.normalize();
    
    std::cout << "Enter date of birth (dd/MM/yyyy): ";
    std::cin >> s.dob;
}

void outputStudentToConsole(const Student& s)
{
    outputStudent(std::cout, s);
}

bool inputStudentFromFile(Student& s, const String& filename)
{
    std::ifstream fin;
    fin.open(filename);
    if (!fin) {
        std::cout << "File cannot be opened.\n";
        return false;
    }
    
    fin >> s;
    fin.close();
    return true;
}

bool outputStudentToFile(const Student& s, const String& filename)
{
    std::ofstream fout;
    fout.open(filename);
    if (!fout) {
        std::cout << "File cannot be opened.\n";
        return false;
    }
    
    fout << s;
    fout.close();
    return true;
}

bool outputStudentInfoToFile(const Student& s, const String& filename)
{
    std::ofstream fout;
    fout.open(filename);
    if (!fout) {
        std::cout << "File cannot be opened.\n";
        return false;
    }
    
    String firstName = getFirstName(s.fullName);
    String lastName = getLastName(s.fullName);
    
    Date age = calculateAge(s.dob);
    
    // for observing
    fout << "ID: " << s.id << '\n';
    fout << "First name: " << firstName << '\n';
    fout << "Last name: " << lastName << '\n';
    fout << "GPA: " << std::fixed << std::setprecision(2) << s.gpa << '\n';
    fout << "Address: " << s.address << '\n';
    fout << "Date of birth: " << getFormattedDate(s.dob, "dd/MM/yyyy") << '\n';
    
    String yearManip = (age.year > 1) ? " years " : " year ";
    String monthManip = (age.month > 1) ? " months " : " month ";
    String dayManip = (age.day > 1) ? " days " : " day ";
    fout << "Age: " << age.year << yearManip << age.month << monthManip << age.day << dayManip << '\n';
    
    fout.close();
    return true;
}

bool outputStudentListToFile(const List<Student> list, const String& filename)
{
    std::ofstream fout;
    fout.open(filename);
    if (!fout) {
        std::cout << "File cannot be opened.\n";
        return false;
    }
    
    outputStudentList(fout, list);
    return true;
}

String extractClass(const Student& s)
{
    if (s.id.size() < 2) return "K_Invalid";
    return "K" + s.id.substring(0, 2);
}

int compareByID(const Student& s1, const Student& s2)
{
    return strcmp(s1.id, s2.id);
}

int compareByGPA_ID(const Student& s1, const Student& s2)
{
    if (s1.gpa < s2.gpa) return -1;
    if (s1.gpa > s2.gpa) return 1;
    return compareByID(s1, s2);
}
int compareByName_ID(const Student& s1, const Student& s2)
{
    int cmp = strcmp(s1.fullName, s2.fullName);
    if (cmp != 0) return cmp;
    return compareByID(s1, s2);
}

int compareByFirstName_ID(const Student& s1, const Student& s2)
{
    String fn1 = getFirstName(s1.fullName);
    String fn2 = getFirstName(s2.fullName);
    
    int cmp = strcmp(fn1, fn2);
    if (cmp != 0) return cmp;
    return compareByID(s1, s2);
}

int compareByLastName_ID(const Student& s1, const Student& s2)
{
    String ln1 = getLastName(s1.fullName);
    String ln2 = getLastName(s2.fullName);
    
    int cmp = strcmp(ln1, ln2);
    if (cmp != 0) return cmp;
    return compareByID(s1, s2);
}

int compareByDOB_ID(const Student& s1, const Student& s2)
{
    int dobCompare = compareDate(s1.dob, s2.dob);
    if (dobCompare != 0) return dobCompare;
    return compareByID(s1, s2);
}
