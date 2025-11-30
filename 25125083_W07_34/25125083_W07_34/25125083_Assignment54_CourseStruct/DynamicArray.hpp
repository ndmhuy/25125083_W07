//
//  DynamicArray.hpp
//  Learning
//
//  Created by Huy Nguyen on 25/11/25.
//

#ifndef DynamicArray_hpp
#define DynamicArray_hpp

#include <iostream>
#include <algorithm>

template <typename T>
struct DynamicArray
{
    using Comparator = int (*)(const T& a, const T& b);
    
    T* data;
    size_t size;
    size_t capacity;
    
    T& operator[](size_t index)
    {
        return data[index];
    }
    
    const T& operator[](size_t index) const{
        return data[index];
    }
    
    DynamicArray(size_t initCap = 16)
    {
        capacity = (initCap == 0) ? 1 : initCap;
        size = 0;
        data = new T[capacity];
    }
    
    DynamicArray(const DynamicArray& other)
    {
        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];
        
        for (size_t i = 0; i < size; ++i)
            data[i] = other.data[i];
    }
    
    ~DynamicArray()
    {
        delete[] data;
    }
    
    DynamicArray& operator =(const DynamicArray& other)
    {
        if (this != &other)
        {
            delete[] data;
            
            size = other.size;
            capacity = other.capacity;
            data = new T[capacity];
            
            for (size_t i = 0; i < size; ++i)
                data[i] = other.data[i];
        }
        
        return *this;
    }
    
    void add (const T& elem)
    {
        if (size + 1 >= capacity) {
            if (capacity == 0) capacity = 1;
            else capacity *= 2;
            
            T* new_data = new T[capacity];
            for (int i = 0; i < size; ++i) new_data[i] = data[i];
            
            delete[] data;
            data = new_data;
        }
        
        data[size++] = elem;
    }
    
    int indexOf(const T& elem)
    {
        for (int i = 0; i < size; ++i)
        {
            if (data[i] == elem)
                return i;
        }
        return -1;
    }
    
    T removeAt(int index)
    {
        if (index >= size || index < 0)
        {
            std::cerr << "Error: Index Out of Bound.\n";
            return T();
        }
        
        T rmElem = data[index];
        for (size_t i = index; i < size - 1; ++i)
            data[i] = data[i + 1];
        --size;
        
        return rmElem;
    }
    
    bool remove(const T& elem)
    {
        int index = indexOf(elem);
        if (index == -1) return false;
        removeAt(index);
        return true;
    }
    
    void quicksort(T* arr, size_t left, size_t right, Comparator comp)
    {
        size_t i = left, j = right;
        T pivot = arr[(left + right) / 2];
        
        while (i <= j)
        {
            while (comp(arr[i], pivot) < 0) ++i;
            while (comp(arr[j], pivot) > 0) --j;
            if (i <= j)
            {
                std::swap(arr[i], arr[j]);
                ++i;
                --j;
            }
        }
        
        if (left < j) quicksort(arr, left, j, comp);
        if (right > i) quicksort(arr, i, right, comp);
    }
    
    void sort(Comparator comp)
    {
        if (size > 1) quicksort(data, 0, size - 1, comp);
    }
};

#endif // !DynamicArray_hpp
