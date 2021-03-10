#pragma once
#include <iostream>

// for get_keys and get_values() funcs
// dynamic array

template <typename T>
struct _array {
    T* arr = nullptr;
    std::size_t size = 0u;
    std::size_t capacity = 0u;

    _array() {

    }

    ~_array() {
        delete[] arr;
        arr = nullptr;
        size = 0u;
        capacity = 0u;
    }

    void insert(const T& item) {
        if (capacity <= size) {
            capacity += 10;
            copy_old();
        }

        arr[size++] = item;
    }

    // for ASSERT_EQ() func
    bool operator==(_array<T> const& other_arr) {
        if (other_arr.size != size) return false;

        for (size_t i = 0u; i < size; i++) {
            if (other_arr.arr[i] != arr[i]) return false;
        }

        return true;
    }

private:
    void copy_old() {
        T* new_arr = new T[capacity];
        T* old_arr = arr;

        for (int i = 0; i < size; i++) {
            new_arr[i] = old_arr[i];
        }

        arr = new_arr;
        if (old_arr != nullptr)
            delete[] old_arr;
    }
};
