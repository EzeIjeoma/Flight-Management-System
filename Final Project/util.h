#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

namespace util {


    // Sort function
    template<typename T, typename CompareKey>
    void insertionSort(vector<T>& vec, CompareKey T::* key, bool ascending = true) {
        for (size_t i = 1; i < vec.size(); i++) {
            T temp = vec[i];
            int j = i - 1;

            if (ascending) {
                while (j >= 0 && vec[j].*key > temp.*key) {
                    vec[j + 1] = vec[j];
                    j--;
                }
            }
            else {
                while (j >= 0 && vec[j].*key < temp.*key) {
                    vec[j + 1] = vec[j];
                    j--;
                }
            }
            vec[j + 1] = temp;
        }
    }


    template<typename ItemType>
    class TwoDArrayADT {
    private:
        vector<vector<ItemType>> array;
        size_t rows;
        size_t cols;
        ItemType defaultValue;
        int length; // Used to track the next insertion row

    public:
        TwoDArrayADT(size_t rows, size_t cols, const ItemType& initialValue = ItemType())
            : rows(rows), cols(cols), defaultValue(initialValue), array(rows, vector<ItemType>(cols, initialValue)), length(0) {}

        size_t getLength() const {
            return static_cast<size_t>(length);
        }

        bool isFull() const {
            return static_cast<size_t>(length) == rows;
        }

        ItemType getItem(size_t row, size_t col) const {
            if (row >= rows || col >= cols) throw out_of_range("Array access out of range.");
            return array[row][col];
        }

        void putItem(const vector<ItemType>& items) {
            if (length >= static_cast<int>(rows)) throw out_of_range("2D Array is full. Cannot insert more items.");

            for (size_t col = 0; col < cols; ++col) {
                array[length][col] = (col < items.size()) ? items[col] : defaultValue;
            }

            length++;
        }

        void EmptyList() {
            for (auto& row : array) {
                fill(row.begin(), row.end(), defaultValue);
            }
            length = 0;
        }

        void print() const {
            for (const auto& row : array) {
                if (row[0] == defaultValue)
                    break;
                for (const auto& item : row) {
                    cout << item << " ";
                }
                cout << endl;
            }
        }
    };
}
