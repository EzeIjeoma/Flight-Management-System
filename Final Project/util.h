#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>
#include <string>
#include <iomanip>

using namespace std;

namespace util {

    // Sort Algorithm that uses insertion sort
    template<typename ItemType, typename ReturnType>
    void insertionSort(vector<ItemType>& vec, ReturnType(ItemType::* method)() const, bool ascending = true) {
        for (size_t i = 1; i < vec.size(); i++) {
            ItemType temp = vec[i];
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

    // Two Dimensional Array ADT
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

    // Binary Search Tree ADT
    template<typename ItemType, typename Key>
    class BinarySearchTree {
    private:
        struct Node {
            ItemType data;
            Key key;
            Node* left;
            Node* right;

            Node(ItemType data, Key key) : data(data), key(key), left(nullptr), right(nullptr) {}
        };

        Node* root;

        Node* insert(Node* node, ItemType data, Key key) {
            if (!node) return new Node(data, key);
            if (key < node->key) node->left = insert(node->left, data, key);
            else node->right = insert(node->right, data, key);
            return node;
        }

        void inOrderTraversal(Node* node, vector<ItemType>& result) const {
            if (!node) return;
            inOrderTraversal(node->left, result);
            result.push_back(node->data);
            inOrderTraversal(node->right, result);
        }

        Node* search(Node* node, Key key) const {
            if (!node || node->key == key) return node;
            if (key < node->key) return search(node->left, key);
            return search(node->right, key);
        }

    public:
        BinarySearchTree() : root(nullptr) {}

        void addItem(ItemType data, Key key) {
            root = insert(root, data, key);
        }

        ItemType searchByKey(Key key) const {
            Node* result = search(root, key);
            if (!result) throw runtime_error("Item not found.");
            return result->data;
        }

        vector<ItemType> traverse() const {
            vector<ItemType> result;
            inOrderTraversal(root, result);
            return result;
        }
    };

    // Linked List Implementation of a Queue
    template<typename ItemType>
    class Queue {
    private:
        struct Node {
            ItemType value;
            Node* next;
            Node(const ItemType& val, Node* nextNode = nullptr) : value(val), next(nextNode) {}
        };
        Node* frontNode = nullptr; // Points to the front of the queue
        Node* backNode = nullptr; // Points to the back of the queue
        size_t queueSize = 0;

    public:
        Queue() {}
        ~Queue() {
            while (!empty()) {
                dequeue();
            }
        }
        void enqueue(const ItemType& value) {
            Node* newNode = new Node(value);
            if (empty()) {
                frontNode = backNode = newNode; // The queue was empty
            }
            else {
                backNode->next = newNode; // Link the new node to the back of the queue
                backNode = newNode; // Update the back pointer to the new node
            }
            ++queueSize;
        }
        void dequeue() {
            if (empty()) {
                throw std::out_of_range("Queue is empty");
            }
            Node* temp = frontNode;
            frontNode = frontNode->next;
            if (frontNode == nullptr) {
                backNode = nullptr; // The queue is now empty
            }
            delete temp;
            --queueSize;
        }
        ItemType& front() {
            if (empty()) {
                throw std::out_of_range("Queue is empty");
            }
            return frontNode->value;
        }
        bool empty() const {
            return frontNode == nullptr;
        }
        size_t size() const {
            return queueSize;
        }
    };

    // Linked List implementation of Stack
    template<typename ItemType>
    class Stack {
    private:
        struct Node {
            ItemType value;
            Node* next;
            Node(const ItemType& val, Node* nextNode = nullptr) : value(val), next(nextNode) {}
        };
        Node* topNode = nullptr;
        size_t stackSize = 0;

    public:
        Stack() {}
        ~Stack() {
            while (!empty()) {
                pop();
            }
        }
        void push(const ItemType& value) {
            Node* newNode = new Node(value, topNode);
            topNode = newNode;
            ++stackSize;
        }
        void pop() {
            if (empty()) {
                throw std::out_of_range("Stack is empty");
            }
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
            --stackSize;
        }
        ItemType& top() {
            if (empty()) {
                throw std::out_of_range("Stack is empty");
            }
            return topNode->value;
        }
        bool empty() const {
            return topNode == nullptr;
        }
        size_t size() const {
            return stackSize;
        }
    };

    // Create console tables
    class ConsoleTable {
    private:
        vector<vector<string>> rows;
        vector<size_t> columnWidths;
        const char columnSeparator = '|';
        const size_t padding = 1;
    public:
        void addHeaders(const vector<string>& headers) {
            rows.push_back(headers);
            updateColumnWidths(headers);
        }
        void addRow(const vector<string>& row) {
            rows.push_back(row);
            updateColumnWidths(row);
        }
        void printTable() const {
            for (const auto& row : rows) {
                cout << "\t";
                printSeparatorLine();
                cout<< "\t";
                printRow(row);
            }
            cout << "\t";
            printSeparatorLine();
        }
    private:
        void updateColumnWidths(const vector<string>& row) {
            for (size_t i = 0; i < row.size(); ++i) {
                if (columnWidths.size() <= i) {
                    columnWidths.push_back(row[i].size() + 2 * padding);
                }
                else {
                    columnWidths[i] = max(columnWidths[i], row[i].size() + 2 * padding);
                }
            }
        }
        void printSeparatorLine() const {
            cout << columnSeparator;
            for (size_t width : columnWidths) {
                cout << setfill('-') << setw(width) << "" << columnSeparator;
            }
            std::cout << std::endl;
        }
        void printRow(const vector<string>& row) const {
            cout << columnSeparator;
            for (size_t i = 0; i < row.size(); ++i) {
                cout << setfill(' ') << setw(padding) << ""
                    << left << std::setw(columnWidths[i] - 2 * padding) << row[i]
                    << setw(padding) << "" << columnSeparator;
            }
            cout << endl;
        }
    };
}
