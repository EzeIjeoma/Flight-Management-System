#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>

using namespace std;

namespace util {


    // Sort function
    template<typename T, typename ReturnType>
    void insertionSort(vector<T>& vec, ReturnType(T::* method)() const, bool ascending = true) {
        for (size_t i = 1; i < vec.size(); i++) {
            T temp = vec[i];
            int j = i - 1;

            if (ascending) {
                while (j >= 0 && (vec[j].*method)() > (temp.*method)()) {
                    vec[j + 1] = vec[j];
                    j--;
                }
            }
            else {
                while (j >= 0 && (vec[j].*method)() < (temp.*method)()) {
                    vec[j + 1] = vec[j];
                    j--;
                }
            }
            vec[j + 1] = temp;
        }
    }
     
    
    //template<typename T, typename CompareKey>
    //void insertionSort(vector<T>& vec, CompareKey T::* key, bool ascending = true) {
    //    for (size_t i = 1; i < vec.size(); i++) {
    //        T temp = vec[i];
    //        int j = i - 1;

    //        if (ascending) {
    //            while (j >= 0 && vec[j].*key > temp.*key) {
    //                vec[j + 1] = vec[j];
    //                j--;
    //            }
    //        }
    //        else {
    //            while (j >= 0 && vec[j].*key < temp.*key) {
    //                vec[j + 1] = vec[j];
    //                j--;
    //            }
    //        }
    //        vec[j + 1] = temp;
    //    }
    //}


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


    template<typename T, typename K>
    class BinarySearchTree {
    private:
        struct Node {
            T data;
            K key;
            Node* left;
            Node* right;

            Node(T data, K key) : data(data), key(key), left(nullptr), right(nullptr) {}
        };

        Node* root;

        // Utility function to add a new node to the BST
        Node* insert(Node* node, T data, K key) {
            if (!node) return new Node(data, key);
            if (key < node->key) node->left = insert(node->left, data, key);
            else node->right = insert(node->right, data, key);
            return node;
        }

        // Utility function for in-order traversal
        void inOrderTraversal(Node* node, std::vector<T>& result) const {
            if (!node) return;
            inOrderTraversal(node->left, result);
            result.push_back(node->data);
            inOrderTraversal(node->right, result);
        }

        // Utility function to search for a node by key
        Node* search(Node* node, K key) const {
            if (!node || node->key == key) return node;
            if (key < node->key) return search(node->left, key);
            return search(node->right, key);
        }

    public:
        BinarySearchTree() : root(nullptr) {}

        // Method to add item to the BST
        void addItem(T data, K key) {
            root = insert(root, data, key);
        }

        // Method to search based on the provided key
        T searchByKey(K key) const {
            Node* result = search(root, key);
            if (!result) throw std::runtime_error("Item not found.");
            return result->data;
        }

        // Method for traversal which returns a vector of items in the BST
        std::vector<T> traverse() const {
            std::vector<T> result;
            inOrderTraversal(root, result);
            return result;
        }
    };
}
