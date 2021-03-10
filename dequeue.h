#pragma once
#include"_node.h"

template <typename T, typename K>
struct _deque_node{
    RB_NODE<T, K>* node;
    _deque_node<T, K>* next;

    _deque_node(RB_NODE<T, K>* _node = nullptr, _deque_node<T, K>* _next = nullptr) : node(_node), next(_next) {}
};


template <typename T, typename K>
struct _deque {
    _deque_node<T, K>* head = nullptr;

    void push_back(RB_NODE<T, K>* _node) {
        if (head == nullptr) {
            head = new _deque_node<T, K>(_node);
        } else {
            _deque_node<T, K>* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = new _deque_node<T, K>(_node);
        }
    }

    void push_front(RB_NODE<T, K>* _node) {
        if (head == nullptr) {
            head = new _deque_node<T, K>(_node);
        } else {
            _deque_node<T, K>* new_head = new _deque_node<T, K>(_node, head);
            head = new_head;
        }

    }

    RB_NODE<T, K>* pop_front() {
        if (head == nullptr) throw std::runtime_error("Cannot pop already empty dequeue");
        _deque_node<T, K>* old_head = head;
        head = head->next;
        RB_NODE<T, K>* for_return = old_head->node;

        delete old_head;
        return for_return;
    }

    RB_NODE<T, K>* pop_back() {
        _deque_node<T, K>* current = head;
        RB_NODE<T, K>* for_return;
        if (current->next == nullptr) {
            for_return = current->node;
            delete current;
            head = nullptr;
            return for_return;
        }

        while (current->next->next) {
            current = current->next;
        }
        for_return = current->next->node;
        delete current->next;
        current->next = nullptr;
        return for_return;
    }


    bool is_empty() {
        return head == nullptr;
    }
};

