//
// Created by Hans Dulimarta
//

#ifndef LINKEDLISTWITHTEMPLATE_LINKED_LIST_H
#define LINKEDLISTWITHTEMPLATE_LINKED_LIST_H
#include <memory>
#include <stdexcept>
#include <set>
#include <iostream>
#include <vector>

using namespace std;

namespace gv {
    template <typename T> class linked_list {
    private:
        struct Node;
    public:
        /**
         * Default constructor
         */
        linked_list() {
        }

        /**
         * Check if the list contains data items
         * @return true if it is empty, false otherwise
         */
        bool is_empty() const {
            return (head == nullptr);
        }

        /**
         * Count the number of items in the list
         * @return the number of items
         */
        int size() const {
            if (is_empty())
                return 0;

            int count = 0;
            shared_ptr<Node> current = head;
            while (current != nullptr) {
                count++;
                current = current->next;
            }
            return count;
        }

        /**
         * Make the list empty
         */
        void clear() {
            if (!is_empty()){
                head.reset();
                tail.reset();
            }
        }

        /**
         * Return the first data in the list, or throw an length_error exception when the list is empty
         * @return the data stored in the first node
         * @throw length_error when the list is empty
         */
        const T& front() const {
            if (is_empty())
                throw std::length_error("LENGTH ERROR in front()");
            return head->data;
        };

        /**
         * Return the last data in the list, or throw an length_error exception when the list is empty
         * @return the data stored in the first node
         * @throw length_error when the list is empty
         */
        const T& back() const {
            if (is_empty())
                throw std::length_error("LENGTH ERROR in back()");

            shared_ptr<Node> toLock = tail.lock();
            return toLock->data;
        };

        /**
         * Store x as the first data item in the list
         * @param x the value to store
         */
        void push_front(const T& x) {
            Node newNode = {x};
            if (is_empty()){
                head = make_shared<Node>(newNode);
                tail = head;
            } else {
                shared_ptr<Node> newPtr = make_shared<Node>(newNode);
                head->prev = newPtr;
                newPtr->next = head;
                head = newPtr;
                if (size() == 2)
                    tail = newPtr->next;
            }
        }

        /**
         * Store x as the last data item in the list
         * @param x the value to store
         */
        void push_back(const T& x) {
            Node n = {x};
            if (is_empty()) {
                head = make_shared<Node>(n);
                tail = head;
            } else {
                shared_ptr<Node> newNode = make_shared<Node>(n);
                tail.lock()->next = newNode;
                newNode->prev = tail;
                tail = newNode;
                //if (size() == 2)
                //    head = tail.lock()->prev;
            }

        }

        /**
         * Insert x as a new data item at the specified position in the list.
         * As an example: if the list holds string data {"Carbon", "Oxygen"}
         * insert_into ("Neon", 0) => {"Neon", "Carbon", "Oxygen"}
         * insert_into ("Neon", 1) => {"Carbon", "Neon", "Oxygen"}
         * insert_into ("Neon", 2) => {"Carbon", "Oxygen", "Neon"}
         * insert_into ("Neon", N) => throw out_of_range when N < 0 or N > 2
         *
         * @param x the value to store
         * @param pos the position at which x is to be inserted (0 = first)
         * @throw out_of_range exception when pos is invalid (negative or larger than list size)
         */
        void insert_into (const T&x, int pos) {
            if (pos < 0 || pos > size())
                throw std::out_of_range("OUT OF RANGE in insert_into()");
            if (pos == 0)
                push_front(x);
            else if (pos == size())
                push_back(x);
            else {
                Node n = {x};
                shared_ptr<Node> previousNode = getNode(pos - 1);
                shared_ptr<Node> afterNode = previousNode->next;
                shared_ptr<Node> insertNode = make_shared<Node>(n);

                insertNode->prev = previousNode;
                previousNode->next = insertNode;
                insertNode->next = afterNode;
                afterNode->prev = insertNode;
            }
        }

        /**
         * Remove the data at a given position
         * As an example: if the list holds string data {"Carbon", "Oxygen", "Fluor"}
         * remove_from(0) => {"Oxygen", "Fluor"}
         * remove_from(1) => {"Carbon", "Fluor"}
         * remove_from(2) => {"Carbon", "Oxygen"}
         * remove_from(3) => throw out_of_range exception
         * remove_from(-1) => throw out_of_range exception
         *
         * @param pos the position at which the data is to be removed (0 = first)
         * @throw out_of_range exception when pos is invalid (negative or >= list size)
         */
        void remove_from (int pos) {
            if (pos < 0 || pos >= size())
                throw std::out_of_range("OUT OF RANGE in remove_from");
            if (pos == 0)
                pop_front();
            else if (pos == size() - 1)
                pop_back();
            else {
                shared_ptr<Node> removeNode = getNode(pos);
                shared_ptr<Node> previousNode = removeNode->prev.lock();
                shared_ptr<Node> afterNode = removeNode->next;

                previousNode->next = afterNode;
                afterNode->prev = previousNode;
            }
        }

        /**
         * Return the data stored at a given position
         * @param pos the position at which the data is to be retrieved (0 = first)
         * @return the data at the requested position
         * @throw out_of_range exception when pos is invalid (negative or >= list size)
         */
        const T& at (int pos) const {
            if (pos < 0 || pos >= size())
                throw std::out_of_range("OUT OF RANGE in at()");

            int currentPos = 0;
            shared_ptr<Node> currentNode = head;
            while(currentNode != nullptr){
                if (currentPos == pos)
                    break;
                else {
                    currentNode = currentNode->next;
                    currentPos++;
                }
            }
            return currentNode->data;
        };

        /**
         * Remove the first data item
         * @throw length_error when the list is empty
         */
        void pop_front() {
            if (is_empty())
                throw length_error("LENGTH ERROR in pop_front");
            if (size() == 1){
                head.reset();
                tail.reset();
            } else {
                head = head->next;
                //head->prev = nullptr;
            }
        }

        /**
         * Remove the last data item
         * @throw length_error when the list is empty
         */
        void pop_back() {
            if (is_empty())
                throw length_error("LENGTH ERROR in pop_back");
            else if (size() == 1){
                clear();
            } else {
                tail = (tail.lock()->prev);
                tail.lock()->next = nullptr;
            }
        }
        /**
         * Implement self-adjusting list (Problem 3.30b). Search for a given item
         * and move the item to the front of the list (if found)
         * @param val data item to search for in the list
         * @return true if the item is found, false otherwise
         */
        bool find(const T& val) {
            shared_ptr<Node> currentNode = head;
            int count = 0;

            while(currentNode != nullptr){
                if (currentNode->data == val) {
                    remove_from(count);
                    push_front(val);
                    return true;
                }
                count++;
                currentNode = currentNode->next;
            }
            return false;
        }

        void reverseList(){
            shared_ptr<Node> prevNode;
            shared_ptr<Node> currentNode = head;
            shared_ptr<Node> nextNode;

            while(currentNode != nullptr){
                nextNode = currentNode->next;
                currentNode->next = prevNode;
                prevNode = currentNode;
                currentNode = nextNode;
            }

            currentNode = tail.lock();
            while(currentNode != nullptr){
                printf("%i",currentNode->data);
                currentNode = currentNode->next;
            }
        }

    bool checkCycle(int p){
            shared_ptr<Node> cycleStart = getNode(p);
            shared_ptr<Node> currentNode = cycleStart->next;

            while (currentNode != nullptr) {
                if(currentNode == cycleStart)
                    return true;
                currentNode = currentNode->next;
            }
            return false;
        }

    bool checkCycleList(int p){
            shared_ptr<Node> cycleStart = getNode(p);
            auto nodeList = vector<shared_ptr<Node>>();

            while(cycleStart != nullptr){
                for(auto node : nodeList)
                    if (node == cycleStart)
                        return true;

            nodeList.push_back(cycleStart);
            cycleStart = cycleStart->next;
            }
        return false;
        }

    void createCycle() {
            tail.lock()->next = head;
        }

    private:
        // You may add private data/function here
        shared_ptr<Node> getNode(int pos){
            if (is_empty())
                throw std::length_error("LENGTH ERROR in getNode()");
            else {
                shared_ptr<Node> currentNode = head;
                int count = 0;
                while(currentNode != nullptr && count != pos){
                    currentNode = currentNode->next;
                    count++;
                }
                return currentNode;
            }

        }

        // But, DO NOT CHANGE ANYTHING BELOW THIS LINE
        shared_ptr<Node> head;
        weak_ptr<Node> tail;
        struct Node {
            T data;
            shared_ptr<Node> next;
            weak_ptr<Node> prev;
        };
    };
};
#endif //LINKEDLISTWITHTEMPLATE_LINKED_LIST_H
