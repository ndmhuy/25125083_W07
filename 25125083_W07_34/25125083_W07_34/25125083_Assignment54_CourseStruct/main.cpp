// 25125083
// Nguyen Dinh Minh Huy
// 25A01

#include "DynamicArray.hpp"
#include "String.hpp"
#include "Date.hpp"
#include "Student.hpp"
#include "Course.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>

template <typename T>
using List = DynamicArray<T>;

int main()
{
    Course c;
    Student s;
    List<Student> list;
    String findInput;
    
    String inFileName;
    String outFileName;
    String listOutFileName;
    String findFileName;
    
    std::ifstream configFile;
    configFile.open("config.txt");
    
    if (configFile.is_open()) {
        getline(configFile, inFileName);
        inFileName.normalize();
        
        getline(configFile, outFileName);
        outFileName.normalize();
        
        getline(configFile, listOutFileName);
        listOutFileName.normalize();
        
        getline(configFile, findFileName);
        findFileName.normalize();
        
        configFile.close();
        std::cout << "Configuration loaded from config.txt successfully.\n";
    } else {
        std::cout << "Warning: config.txt not found. Using default filenames.\n";
        inFileName = "input.txt";
        outFileName = "output.txt";
        listOutFileName = "list_output.txt";
        findFileName = "find_student_output.txt";
    }
    
    char choice;
    do {
        std::cout << "\n--- Assignment 54: Course struct handling ---\n";
        std::cout << "1. Input a course from text file (" << inFileName << ")\n";
        std::cout << "2. Output a course to text file (" << outFileName << ")\n";
        std::cout << "3. Save current course\n";
        std::cout << "4. Add a student to course\n";
        std::cout << "5. Remove a student from course\n";
        std::cout << "6. Get students who born this month\n";
        std::cout << "7. Get students who born this date\n";
        std::cout << "8. Get students who are legal to have driving licenses\n";
        std::cout << "9. Get students who are in class\n";
        std::cout << "a. Find student by ID\n";
        std::cout << "b. Find student by name\n";
        std::cout << "c. Sort students by ID\n";
        std::cout << "d. Sort students by first name\n";
        std::cout << "e. Sort students by GPA\n";
        std::cout << "f. Sort students by date of birth\n";
        std::cout << "0. Return to Main Menu\n";
        std::cout << "Enter your choice: ";

        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case '1':
                if (inputCourseFromFile(c, inFileName))
                    std::cout << "Data loaded from " << inFileName << " successfully.\n";
                break;
            case '2':
                if (outputCourseToRead(c, outFileName))
                    std::cout << "Data written to " << outFileName << " successfully.\n";
                break;
            case '3':
                if (outputCourseToSave(c, inFileName))
                    std::cout << "Data written to " << inFileName << " successfully.\n";
                break;
            case '4':
                std::cout << "Enter student info:\n";
                inputStudentFromConsole(s);
                if (addStudent(c, s))
                    std::cout << "Add student successfully.\n";
                break;
            case '5':
                std::cout << "Enter student info:\n";
                inputStudentFromConsole(s);
                if (removeStudent(c, s))
                    std::cout << "Remove student successfully.\n";
                break;
            case '6':
                list = GetBornThisMonth(c);
                if (outputStudentListToFile(list, listOutFileName))
                    std::cout << "Data written to " << listOutFileName << " successfully.\n";
                break;
            case '7':
                list = GetBornThisDate(c);
                if (outputStudentListToFile(list, listOutFileName))
                    std::cout << "Data written to " << listOutFileName << " successfully.\n";
                break;
            case '8':
                list = GetLegalDrivingLicenses(c);
                if (outputStudentListToFile(list, listOutFileName))
                    std::cout << "Data written to " << listOutFileName << " successfully.\n";
                break;
            case '9':
                std::cout << "Enter class name (e.g. K19): ";
                getline(std::cin, findInput);
                findInput.normalize();
                list = GetStudentsOfClass(c, findInput);
                if (outputStudentListToFile(list, listOutFileName))
                    std::cout << "Data written to " << listOutFileName << " successfully.\n";
                break;
            case 'a':
                std::cout << "Enter search ID: ";
                getline(std::cin, findInput);
                findInput.normalize();
                s = GetStudentWithId(c, findInput);
                if (outputStudentInfoToFile(s, findFileName))
                    std::cout << "Data written to " << findFileName << " successfully.\n";
                break;
            case 'b':
                std::cout << "Enter search name: ";
                getline(std::cin, findInput);
                findInput.normalize();
                list = GetStudentsWithName(c, findInput);
                if (outputStudentListToFile(list, listOutFileName))
                    std::cout << "Data written to " << listOutFileName << " successfully.\n";
                break;
            case 'c':
                std::cout << "Sorted by ID\n";
                sortStudentById(c);
                if (outputCourseToRead(c, outFileName))
                    std::cout << "Data written to " << outFileName << " successfully.\n";
                break;
            case 'd':
                std::cout << "Sorted by first name\n";
                sortStudentByFirstName(c);
                if (outputCourseToRead(c, outFileName))
                    std::cout << "Data written to " << outFileName << " successfully.\n";
                break;
            case 'e':
                std::cout << "Sorted by GPA\n";
                sortStudentByGpa(c);
                if (outputCourseToRead(c, outFileName))
                    std::cout << "Data written to " << outFileName << " successfully.\n";
                break;
            case 'f':
                std::cout << "Sorted by date of birth\n";
                sortStudentByDOB(c);
                if (outputCourseToRead(c, outFileName))
                    std::cout << "Data written to " << outFileName << " successfully.\n";
                break;
            case '0':
                std::cout << "Returning to main menu...\n";
                break;
            default:
                std::cout << "Unknown command!\n";
                break;
        }
    } while (choice != '0');
    
    return EXIT_SUCCESS;
}
