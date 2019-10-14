//
// Created by Hans Dulimarta.
//

#ifndef BINARYTREES_BINARYSEARCHTREE_H
#define BINARYTREES_BINARYSEARCHTREE_H
#include <memory>
#include <iostream>
#include <stdexcept>
#include <queue>
#include <stack>

using namespace std;

namespace gv {
    template<typename E>     // textbook code E is Comparable
    class BinaryTree {

    public:
        /** WARNING: You will find a few overloaded functions declared in
         * both the public and private sections. This design is intentional
         * because many tree algorithms are recursive and the private counterpart
         * are the ones implementing the recursive work and they usually
         * require additional input argument(s).
         *
         * The non-recursive public functions simply call their recursive
         * counterpart to initiate the recursive work.
         */

        /**
         * Make the tree into an empty tree
         */
        void makeEmpty() noexcept {
            // TODO: complete this function
            root.reset();
        }

        /**
         * Insert a new data into the BST while maintaining no duplicate entries
         * @param item
         * @return true if the item can be inserted (no duplicate), false if the tree
         * already contains the same data item.
         */
        bool insert(const E &item) noexcept {
            // TODO: complete this function by invoking a private recursive function
            return insert(item, root);
        }

        /**
         * Remove an item from the tree
         * @param item data to remove
         * @return true is the data is removed, false if the data is not in the tree
         * @throw length_error on an attempt to remove from an empty tree
         */
        bool remove(const E& item) {
            // TODO: complete this function by invoking a private recursive function
            return remove(item,root);
        }

        /**
         * Print the tree using in-order traversal. Separate data item by a single space
         * @param out destination of the print out
         */
        void printTree(ostream &targetStream = cout) const noexcept {
            // TODO: complete this function by invoking a private recursive function
            // Be sure to use "targetStream" (and NOT cout) to print your data
            // For instance the following snippet would print "Hello"
            //   targetStream << "Hello";
            printTree(root, targetStream);
        }

        /**
         * Find the smallest value in the tree
         * @return the smallest value
         * @throw length_error if the tree is empty
         */
        const E findMin() const {
            // TODO: complete this function
            return findMin(root);
        };

        /**
         * Find the largest value in the tree
         * @return the largest value
         * @throw length_error if the tree is empty
         */
        const E findMax() const {
            // TODO: complete this function
            return findMax(root);
        };

        /**
         * Check if the given item is stored in the tree
         * @param val
         * @return true if the item is stored in the tree, false otherwise
         */
        bool contains(const E &val) const noexcept {
            // TODO: complete this function by invoking a private recursive function
            return contains(val, root);
        }

        /**
         * Is the tree empty?
         * @return
         */
        bool isEmpty() const noexcept {
            // TODO: complete this function
            return (root == nullptr);
        }

        /**
         * Return the number of nodes in the tree (Problem 4.31a)
         * @return
         */
        int numberOfNodes() const noexcept {
            // TODO: complete this function by invoking a private recursive function
            return numberOfNodes(root);
        }

        /**
         * Return the number of leaves in the tree (Problem 4.31b)
         * @return
         */
        int numberOfLeaves() const noexcept {
            // TODO: complete this function by invoking a private recursive function
            return numberOfLeaves(root);
        }

        /**
         * Return the number of full nodes (Problem 4.31c). A full node is a node with exactly two children
         * @return
         */
        int numberOfFullNodes() const noexcept {
            // TODO: complete this function by invoking a private recursive function
            return numberOfFullNodes(root);
        }

        /**
         * Remove all the leaves from the tree and keep the data in these leaves into a vector
         * @return a vector of removed items
         */
        vector<E> remove_leaves() noexcept {
            vector<E> prunedLeaves;
            // TODO: complete this function by invoking a private recursive function
            // include the vector (prunedLeaves) about in your function invocation

            return remove_leaves(prunedLeaves,root);
        }

        /**
         * Visit the node in level order (Problem 4.40)
         * @return
         */
        vector<E> levelOrder() const {
            vector<E> out;
            // TODO: complete this function
            if (isEmpty())
                return out;

            vector<Node*> parentList;
            vector<Node*> childList;

            parentList.push_back(root.get());

            while (parentList.size() > 0) {
                for (Node* x : parentList) {
                    Node* temp;
                    if (x->left != nullptr) {
                        temp = (x->left).get();
                        childList.push_back(temp);
                    }
                    if (x->right != nullptr) {
                        temp = (x->right).get();
                        childList.push_back(temp);
                    }
                out.push_back(x->data);
                }
                parentList = move(childList);
            }
            return out;
        }

        static bool hasLeak() {
            return nodeCount != 0;
        }

        static int allocatedNodes() {
            return nodeCount;
        }

    private:
        struct Node;

        // TODO: write your private functions here

        const E findMin(const unique_ptr<Node>& current) const {
            if (isEmpty())
                throw length_error("Tree is empty");
            if (current->left == nullptr)
                return current->data;
            return findMin(current->left);
        }

        const E findMax(const unique_ptr<Node>& current) const {
            if (isEmpty())
                throw length_error("Tree is empty");
            if (current->right == nullptr)
                return current->data;
            return findMax(current->right);
        }

        bool insert(const E &item, unique_ptr<Node>& current) noexcept {
            if (isEmpty()) {
                root = make_unique<Node>();
                root->data = item;
                return true;
            } else {
                if (current == nullptr) {
                    current = make_unique<Node>();
                    current->data = item;
                    return true;
                }
                else if (item > current->data)
                    return insert(item, current->right);
                else if (item < current->data)
                    return insert(item, current->left);
                return false;
            }
        }

        bool remove(const E &item, unique_ptr<Node>& current) {
            if (isEmpty()) {
                throw length_error("Tree is empty.");
            } else {
                if (current == nullptr)
                    return false;
                if (item > current->data)
                    return remove(item, current->right);
                else if (item < current->data)
                    return remove(item, current->left);
                else if (current->right != nullptr && current->left != nullptr){
                    current->data = findMin(current->right);
                    return remove(current->data, current->right);
                }
                else {
                    if (current->right != nullptr) {
                        current.reset(current->right.release());
                    }
                    else if (current->left != nullptr) {
                        current.reset(current->left.release());
                    } else {
                        current.reset();
                    }


                }
                return true;
            }
        }

        void printTree(const unique_ptr<Node>& current, ostream &targetStream = cout) const noexcept {
            if (current->left != nullptr)
                printTree(current->left, targetStream);

            targetStream << current->data + " ";

            if (current->right != nullptr)
                printTree(current->right, targetStream);
        }

        bool contains(const E &val, const unique_ptr<Node>& current) const noexcept {
            if (current == nullptr)
                return false;
            if (val < current->data)
                return contains(val, current->left);
            if (val > current->data)
                return contains(val, current->right);
            return true;
        }

        int numberOfNodes(const unique_ptr<Node>& current) const noexcept {
            if (current == nullptr)
                return 0;
            if (current->right == nullptr && current->left == nullptr)
                return 1;
            return numberOfNodes(current->right) + numberOfNodes(current->left) + 1;
        }

        int numberOfLeaves(const unique_ptr<Node>& current) const noexcept {
            if (current == nullptr)
                return 0;
            if (current->left == nullptr && current->right == nullptr)
                return 1;
            return numberOfLeaves(current->left) + numberOfLeaves(current->right);
        }

        int numberOfFullNodes(const unique_ptr<Node>& current) const noexcept {
            if (isEmpty())
                return 0;
            if (current->left != nullptr && current->right != nullptr)
                return numberOfFullNodes(current->left) + numberOfFullNodes(current->right) + 1;
            else {
                if (current->right != nullptr)
                    return numberOfFullNodes(current->right);
                if (current->left != nullptr)
                    return numberOfFullNodes(current->left);
                return 0;
            }
        }

        vector<E> remove_leaves(vector<E>& prunedLeaves, const unique_ptr<Node>& current) noexcept {
            if (current == nullptr)
                return prunedLeaves;
            if (current->left == nullptr && current->right == nullptr) {
                prunedLeaves.push_back(current->data);
                remove(current->data);
                return prunedLeaves;
            }
            remove_leaves(prunedLeaves,current->left);
            remove_leaves(prunedLeaves,current->right);
            return prunedLeaves;
        }

        static int nodeCount;
        // TODO: Make necessary modification to the Node
        // structure if you decide to implement a threaded tree
        struct Node {
            Node() {
                nodeCount++;
            }

            ~Node() {
                nodeCount--;
            }
            E data;
            unique_ptr<Node> left, right;
        };
        unique_ptr<Node> root;

    };

    template<typename E>
    int BinaryTree<E>::nodeCount = 0;
}
#endif //BINARYTREES_BINARYSEARCHTREE_H
