#pragma once
#include <iostream>

#include "_dequeue.h"
#include "_array.h"

template <typename T, typename K>
struct _map {
    RB_NODE<T, K>* root;
    RB_NODE<T, K>* leaf;

    _map() {
        leaf = new RB_NODE<T, K>(static_cast<T>(0), static_cast<K>(0), nullptr, nullptr, nullptr, BLACK);
        root = leaf;
    }

    ~_map() {
        clear();
    }

    /**
    *** left rotate for node
    **/

    void rotateLeft(RB_NODE<T, K>* node) {
        RB_NODE<T, K> *anchor = node->right;

        // setup node->right link
        node->right = anchor->left;
        if (anchor->left != leaf) anchor->left->parent = node;

        // setup anchor->parent link
        if (anchor != leaf) anchor->parent = node->parent;
        if (node->parent) {
            if (node == node->parent->left)
                node->parent->left = anchor;
            else
                node->parent->right = anchor;
        } else {
            root = anchor;
        }

        // link node and anchor
        anchor->left = node;
        if (node != leaf) node->parent = anchor;
    }

    /**
    *** right rotate for node
    **/

    void rotateRight(RB_NODE<T, K> *node) {
        RB_NODE<T, K> *anchor = node->left;

        // setup node->left link
        node->left = anchor->right;
        if (anchor->right != leaf) anchor->right->parent = node;

        // setup anchor->parent link
        if (anchor != leaf) anchor->parent = node->parent;
        if (node->parent) {
            if (node == node->parent->right)
                node->parent->right = anchor;
            else
                node->parent->left = anchor;
        } else {
            root = anchor;
        }

        // link node and anchor
        anchor->right = node;
        if (node != leaf) node->parent = anchor;
    }

    /**
    *** Maintain the tree balance after inserting the node
    *** Most cases are linked in one function
    **/

    void insert_fix(RB_NODE<T, K> *node) {
        // check some properties
        while (node != root && node->parent->color == RED) {
            // found a defect
            if (node->parent == node->parent->parent->left) {
                RB_NODE<T, K> *uncle = node->parent->parent->right;
                if (uncle->color == RED) {
                    // UNCLE = RED case
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    // UNCLE = BLACK case
                    if (node == node->parent->right) {
                        // make node a left child
                        node = node->parent;
                        rotateLeft(node);
                    }

                    // recolor then rotate
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rotateRight(node->parent->parent);
                }
            } else {
                // other direction for the code before
                RB_NODE<T, K> *uncle = node->parent->parent->left;
                if (uncle->color == RED) {
                    // UNCLE = RED case
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    // UNCLE = BLACK case
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotateRight(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rotateLeft(node->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    /**
    *** the node insertion code
    **/

    void insert(const T& _data, const K& _key) {
        RB_NODE<T, K> *current;
        RB_NODE<T, K> *parent;
        RB_NODE<T, K> *node;

        current = root;
        parent = nullptr;
        while (current != leaf) {
            if (_key == current->key) throw std::runtime_error("Cannot have 2 identical keys");

            parent = current;

            if (_key < current->key) current = current->left;
            else current = current->right;
        }

        node = new RB_NODE<T, K>(_data, _key, leaf, leaf, parent, RED);

        // insertion part
        if(parent) {
            if(_key < parent->key)
                parent->left = node;
            else
                parent->right = node;
        } else {
            root = node;
        }

        insert_fix(node);
    }

    /**
    *** Maintain the tree balance after removing the node
    *** Most cases are linked in one function
    **/

    void remove_fix(RB_NODE<T, K> *node) {

        while (node != root && node->color == BLACK) {
            if (node == node->parent->left) {
                RB_NODE<T, K> *brother = node->parent->right;
                if (brother->color == RED) {
                    brother->color = BLACK;
                    node->parent->color = RED;
                    rotateLeft (node->parent);
                    brother = node->parent->right;
                }
                if (brother->left->color == brother->right->color == BLACK) {
                    brother->color = RED;
                    node = node->parent;
                } else {
                    if (brother->right->color == BLACK) {
                        brother->left->color = BLACK;
                        brother->color = RED;
                        rotateRight (brother);
                        brother = node->parent->right;
                    }
                    brother->color = node->parent->color;
                    node->parent->color = BLACK;
                    brother->right->color = BLACK;
                    rotateLeft (node->parent);
                    node = root;
                }
            } else {
                RB_NODE<T, K> *brother = node->parent->left;
                if (brother->color == RED) {
                    brother->color = BLACK;
                    node->parent->color = RED;
                    rotateRight (node->parent);
                    brother = node->parent->left;
                }
                if (brother->right->color == brother->left->color == BLACK) {
                    brother->color = RED;
                    node = node->parent;
                } else {
                    if (brother->left->color == BLACK) {
                        brother->right->color = BLACK;
                        brother->color = RED;
                        rotateLeft (brother);
                        brother = node->parent->left;
                    }
                    brother->color = node->parent->color;
                    node->parent->color = BLACK;
                    brother->left->color = BLACK;
                    rotateRight (node->parent);
                    node = root;
                }
            }
        }
        node->color = BLACK;
    }

    void remove(const K& _key) {
        erase(find(_key));
    }


    /// delete the node from the tree

    void erase(RB_NODE<T, K> *for_delete) {
        RB_NODE<T, K> *node, *child;

        if (for_delete == nullptr || for_delete == leaf) throw std::runtime_error("Node for delete doesn't exist");

        if (for_delete->left == leaf || for_delete->right == leaf) {
            // child has a leaf
            child = for_delete;
        } else {
            // find the needed node
            child = for_delete->right;
            while (child->left != leaf) child = child->left;
        }

        // node is the only child's of ex-child
        if (child->left != leaf)
            node = child->left;
        else
            node = child->right;

        // remove the child from the parent chain
        node->parent = child->parent;
        if (child->parent != nullptr) {
            if (child == child->parent->left)
                child->parent->left = node;
            else
                child->parent->right = node;

        } else
            root = node;

        if (child != for_delete) {
            for_delete->key = child->key;
            for_delete->data = child->data;
        }

        if (child->color == BLACK)
            remove_fix(node);

        delete child;
    }

    /// find needed Node

    RB_NODE<T, K> *find(const K& _key) {
        RB_NODE<T, K> *current = root;
        while(current != leaf) {
            if (_key == current->key)
                return current;

            if (_key < current->key) current = current->left;
            else current = current->right;

        }
        throw std::runtime_error("Can't find the node");
//        return nullptr;
    }

    // BFS-BASED OUTPUT
    void print() {
        if (root == nullptr) return;
        _deque<T, K> deque_list;
        deque_list.push_back(root);


        while (!deque_list.is_empty()) {
            RB_NODE<T, K>* current = deque_list.pop_front();

            if (current == leaf) std::cout << "NIL ";
            else {
                std::cout << "[" << current->key << "] : " << current->data << " ";
                if (current->color == BLACK) std::cout << "b ";
                else std::cout << "r ";
            }

            if (current->left != nullptr) deque_list.push_back(current->left);
            if (current->right != nullptr) deque_list.push_back(current->right);
        }
    }

    void clear() {
        delete_map(root);
        delete leaf;
        leaf = nullptr;
        root = nullptr;
    }

    // BFS-based getting
    _array<K> get_keys() {
        if (root == nullptr) throw std::runtime_error("No values in the tree");
        _array<K> keys;
        _deque<T, K> deque_list;
        deque_list.push_back(root);

        while (!deque_list.is_empty()) {
            RB_NODE<T, K>* current = deque_list.pop_front();

            if (current != leaf)
                keys.insert(current->key);

            if (current->left != nullptr && current->left != leaf) deque_list.push_back(current->left);
            if (current->right != nullptr && current->right != leaf) deque_list.push_back(current->right);
        }
        return keys;
    }


    // BFS-based getting
    _array<T> get_values() {
        if (root == nullptr) throw std::runtime_error("No values in the tree");
        _array<T> values;
        _deque<T, K> deque_list;
        deque_list.push_back(root);

        while (!deque_list.is_empty()) {
            RB_NODE<T, K>* current = deque_list.pop_front();

            if (current != leaf)
                values.insert(current->data);

            if (current->left != nullptr && current->left != leaf) deque_list.push_back(current->left);
            if (current->right != nullptr && current->right != leaf) deque_list.push_back(current->right);
        }
        return values;
    }


private:
    void delete_map(RB_NODE<T, K>* for_delete) {
        if (for_delete != nullptr && for_delete != leaf) {
            if (for_delete->left != nullptr && for_delete->left != leaf)
                delete_map(for_delete->left);
            for_delete->left = nullptr;

            if (for_delete->right != nullptr && for_delete->right != leaf)
                delete_map(for_delete->right);
            for_delete->right = nullptr;

            delete for_delete;
        }
    }
};

