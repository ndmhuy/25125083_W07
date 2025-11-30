// 25125083
// Nguyen Dinh Minh Huy
// 25A01

#include <iostream>
#include <algorithm>
#include <cstdlib>

int* initializeArray(int n);
void inputArray(int* arr, int n);
void outputArray(int* arr, int n);
long long elementSum(int* arr, int n);
int findLargestIndex(int* arr, int n);
void deleteElement(int*& arr, int& n, int id);
void insertElement(int*& arr, int& n, int val, int id);
void reverseArray(int* arr, int n);

int main()
{
    int n;
    std::cout << "Enter size of array: ";
    std::cin >> n;
    
    if (n <= 0) {
        std::cout << "Invalid size.\n";
        return 0;
    }

    int* arr = initializeArray(n);
    std::cout << "Enter " << n << " elements:\n";
    inputArray(arr, n);
    std::cout << "The array you have entered:\n";
    outputArray(arr, n);
    
    std::cout << "Sum of all elements: " << elementSum(arr, n) << '\n';
    
    int id = findLargestIndex(arr, n);
    if (id != -1)
        std::cout << "Largest value: " << arr[id] << '\n';
    else
        std::cout << "There are no elements so there are no largest value\n";
    
    if (n > 0) {
        std::cout << "Deleting largest value... New array:\n";
        deleteElement(arr, n, id);
        outputArray(arr, n);
    }
    
    int val;
    std::cout << "Enter the value you want to insert: ";
    std::cin >> val;
    std::cout << "Enter the index you want to insert: ";
    std::cin >> id;
    
    insertElement(arr, n, val, id);
    outputArray(arr, n);
    
    std::cout << "Reversing array...\n";
    reverseArray(arr, n);
    outputArray(arr, n);
    
    delete[] arr;
    
    return EXIT_SUCCESS;
}

int* initializeArray(int n)
{
    return new int[n];
}

void inputArray(int* arr, int n)
{
    for (int i = 0; i < n; ++i)
        std::cin >> *(arr + i);
}

void outputArray(int* arr, int n)
{
    if (n == 0) {
        std::cout << "(empty)\n";
        return;
    }
    for (int i = 0; i < n; ++i)
        std::cout << *(arr + i) << ' ';
    std::cout << '\n';
}

long long elementSum(int* arr, int n)
{
    long long sum = 0LL;
    for (int i = 0; i < n; ++i)
        sum += *(arr + i);
    
    return sum;
}

int findLargestIndex(int* arr, int n)
{
    if (n <= 0) return -1;
    int largestId = 0;
    
    int largest = *arr;
    for (int i = 1; i < n; ++i)
        if (*(arr + i) > largest)
        {
            largest = *(arr + i);
            largestId = i;
        }
    
    return largestId;
}

void deleteElement(int*& arr, int& n, int id)
{
    if (id >= n || id < 0) return;
    
    if (n == 1) {
        delete[] arr;
        arr = nullptr;
        n = 0;
        return;
    }

    int* newArr = new int[n - 1];
    int i = 0, j = 0;
    while (j < n)
    {
        if (j == id) {
            ++j;
        } else {
            newArr[i++] = arr[j++];
        }
    }
    
    delete[] arr;
    arr = newArr;
    --n;
}

void insertElement(int*& arr, int& n, int val, int id)
{
    if (id > n || id < 0) {
        std::cout << "Invalid position.\n";
        return;
    }
    
    int* newArr = new int[n + 1];
    int i = 0;
    int j = 0;
    
    while (i < n + 1)
    {
        if (i == id) {
            newArr[i++] = val;
        } else {
            newArr[i++] = arr[j++];
        }
    }
    
    if (arr != nullptr) delete[] arr;
    arr = newArr;
    ++n;
}

void reverseArray(int* arr, int n)
{
    int i = 0;
    int j = n - 1;
    while (i < j)
    {
        std::swap(arr[i], arr[j]);
        ++i;
        --j;
    }
}
