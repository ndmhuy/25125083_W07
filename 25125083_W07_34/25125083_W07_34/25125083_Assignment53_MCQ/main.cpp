// 25125083
// Nguyen Dinh Minh Huy
// 25A01

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

char* readAnswers(const char* filename, int& size)
{
    std::ifstream fin(filename);
    
    if (!fin) {
        std::cout << "Error: Cannot open file " << filename << '\n';
        size = 0;
        return nullptr;
    }
    
    fin >> size;
    char* arr = new char[size];
    
    for (int i = 0; i < size; ++i) {
        fin >> arr[i];
    }
    
    fin.close();
    return arr;
}

int main()
{
    int correctCount = 0;
    int studentCount = 0;
    
    char* correctAnswers = readAnswers("CorrectAnswers.txt", correctCount);
    char* studentAnswers = readAnswers("StudentAnswers.txt", studentCount);
    
    if (correctAnswers == nullptr || studentAnswers == nullptr) {
        delete[] correctAnswers;
        delete[] studentAnswers;
        return EXIT_FAILURE;
    }
    
    if (correctCount != studentCount) {
        std::cout << "The number of answers in the two files do not match.\n";
        delete[] correctAnswers;
        delete[] studentAnswers;
        return EXIT_FAILURE;
    }
    
    int totalMissed = 0;
    
    std::cout << "--- Grading Report ---\n";
    std::cout << "List of missed questions:\n";
    
    for (int i = 0; i < correctCount; ++i) {
        if (correctAnswers[i] != studentAnswers[i]) {
            totalMissed++;
            std::cout << "Question " << (i + 1) << ": "
                 << "Correct Answer (" << correctAnswers[i] << "), "
                 << "Student Answer (" << studentAnswers[i] << ")\n";
        }
    }
    
    if (totalMissed == 0) {
        std::cout << "(None)\n";
    }
    
    double percentage = (double)(correctCount - totalMissed) / correctCount * 100.0;
    
    std::cout << "\n----------------------------\n";
    std::cout << "Total questions missed: " << totalMissed << '\n';
    std::cout << "Percentage answered correctly: " << std::fixed << std::setprecision(2) << percentage << "%" << '\n';
    
    if (percentage >= 70.0) std::cout << "Result: PASSED\n";
    else std::cout << "Result: FAILED\n";
    
    delete[] correctAnswers;
    delete[] studentAnswers;
    
    return EXIT_SUCCESS;
}
