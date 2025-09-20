#ifndef HW2_H
#define HW2_H

#include <iostream>
#include <cstdint>

// Unified Node class for both singly and XOR linked lists
class Node {
public:
    int k;  // unique key
    Node* next;  // for singly linked list
    uintptr_t npx;  // XOR of next and previous node addresses (for XOR linked list)
    
    Node(int key) : k(key), next(nullptr), npx(0) {}
    ~Node() = default;
};

// Singly Linked List class
class SingleList {
private:
    Node* head;
    
public:
    SingleList();
    ~SingleList();
    
    void list_walk();
    void list_prepend(Node* x);
    void list_insert(Node* x, Node* y);
    void list_search(int k);
    void list_delete(Node* n);
    void list_ins_del(int k);
    void list_reverse();
    
    // Helper methods
    Node* find_node(int k);
    Node* find_prev_node(Node* target);
};

// XOR Linked List class
class XORList {
private:
    Node* head;
    Node* tail;
    
    // Helper function to XOR two addresses
    Node* XOR(Node* a, Node* b);
    
public:
    XORList();
    ~XORList();
    
    void list_walk();
    void list_prepend(Node* x);
    void list_insert(Node* x, Node* y);
    void list_search(int k);
    void list_delete(Node* n);
    void list_ins_del(int k);
    void list_reverse();
    
    // Helper methods
    Node* find_node(int k);
};

// Test result structure
struct TestResults {
    long long insert_time;
    long long ins_del_time;
    long long walk_time;
    long long reverse_time;
    long long walk2_time;
};

// Test functions
TestResults slist_test();
TestResults xlist_test();

#endif // HW2_H