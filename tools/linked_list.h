#include <iostream>
#include <vector>

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct node {
    int value;
    struct node *p_next_node;
    struct node *p_prev_node;
};

class LinkedList {
    private:
        struct node *p_begin = NULL;
        struct node *p_end = NULL;

    public:
        LinkedList() {};
        ~LinkedList() {
            while (p_begin != nullptr) {
                struct node *p_to_delete = p_begin;
                p_begin = p_begin->p_next_node;
                delete p_to_delete;
            }
        };

        bool empty() {
            return p_begin == NULL;
        };

        struct node * get_first() {
            return p_begin;
        }

        void add(int v) {
            struct node *p_node = new struct node;
            p_node->value = v;
            p_node->p_next_node = NULL;
            p_node->p_prev_node = p_end;

            if (p_begin == NULL) p_begin = p_node;
            else if (p_end != NULL) p_end->p_next_node = p_node;

            p_end = p_node;
        };

        bool remove(int v) {
            struct node *p_node = p_begin;
            while (p_node != NULL && p_node->value != v)
                p_node = p_node->p_next_node;

            if (p_node == NULL) return false;

            if (p_node == p_begin && p_node == p_end) {
                p_begin = NULL;
                p_end = NULL;
            }
            else if (p_node == p_begin) {
                (p_node->p_next_node)->p_prev_node = NULL;
                p_begin = p_node->p_next_node;
            }
            else if (p_node == p_end) {
                (p_node->p_prev_node)->p_next_node = NULL;
                p_end = p_node->p_prev_node;
            }
            else {
                (p_node->p_prev_node)->p_next_node = p_node->p_next_node;
                (p_node->p_next_node)->p_prev_node = p_node->p_prev_node;
            }
            delete p_node;
            return true;
        };

        void print() {
            struct node *p_current = p_begin;
            while (p_current != NULL) {
                std::cout << p_current->value << ", ";
                p_current = p_current->p_next_node;
            }
            std::cout << std::endl;
        };
};

#endif
