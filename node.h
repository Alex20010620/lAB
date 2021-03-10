#pragma once

enum Color { BLACK, RED };

template <typename T, typename K>
struct RB_NODE {
    T data;
    K key;
    RB_NODE<T, K> *left;
    RB_NODE<T, K> *right;
    RB_NODE<T, K> *parent;
    Color color;

    RB_NODE(const T& _data, const K& _key, RB_NODE<T, K>* _left, RB_NODE<T, K>* _right,
            RB_NODE<T, K>* _parent = nullptr, Color _color = BLACK) {
        key = _key;
        data = _data;
        left = _left;
        right = _right;
        parent = _parent;
        color = _color;
    }
};