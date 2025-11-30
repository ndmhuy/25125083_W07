// 25125083
// Nguyen Dinh Minh Huy
// 25A01

#include <iostream>
#include <cstdlib>

void outputArray(int* arr, int size)
{
    for (int i = 0; i < size; ++i)
        std::cout << arr[i] << ' ';
}

int* doubleArraySize(const int* arr, int size)
{
    if (size <= 0) return nullptr;
    
    int newSize = size * 2;
    int* newArr = new int[newSize];
    
    for (int i = 0; i < size; ++i) {
        newArr[i] = arr[i];
    }
    
    for (int i = size; i < newSize; ++i) {
        newArr[i] = 0;
    }
    
    return newArr;
}

int main()
{
    int size = 5;
    int arr[] = {1, 2, 3, 4, 5};
    
    std::cout << "Original array: ";
    outputArray(arr, size);
    std::cout << '\n';
    
    int* expandedArr = doubleArraySize(arr, size);
    if (expandedArr == nullptr) std::cout << "Empty array.\n";
    else {
        std::cout << "Expanded array: ";
        outputArray(expandedArr, size * 2);
        std::cout << '\n';
    }
    
    delete[] expandedArr;
    return EXIT_SUCCESS;
}
