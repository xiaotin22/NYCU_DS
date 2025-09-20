#include "113511266_hw2.h"
#include <iostream>
#include <random>
#include <unordered_set>
#include <chrono>
#include <vector>

// SingleList Implementation
SingleList::SingleList() : head(nullptr) {}

SingleList::~SingleList() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void SingleList::list_walk() {
    std::cout << "List: ";
    Node* current = head;
    bool first = true;
    while (current) {
        if (!first) std::cout << ", ";
        std::cout << current->k;
        first = false;
        current = current->next;
    }
    std::cout << std::endl;
}

void SingleList::list_insert(int k) {
    Node* new_node = new Node(k);
    new_node->next = head;
    head = new_node;
    std::cout << "Inserted " << k << std::endl;
}

void SingleList::list_search(int k) {
    Node* current = head;
    while (current) {
        if (current->k == k) {
            std::cout << "Found " << k << std::endl;
            return;
        }
        current = current->next;
    }
    std::cout << "Not found " << k << std::endl;
}

Node* SingleList::find_node(int k) {
    Node* current = head;
    while (current) {
        if (current->k == k) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

Node* SingleList::find_prev_node(Node* target) {
    if (!head || head == target) return nullptr;
    
    Node* current = head;
    while (current->next && current->next != target) {
        current = current->next;
    }
    return current->next == target ? current : nullptr;
}

void SingleList::list_delete(Node* n) {
    if (!n) return;
    
    if (head == n) {
        head = head->next;
        std::cout << "Deleted " << n->k << std::endl;
        delete n;
        return;
    }
    
    Node* prev = find_prev_node(n);
    if (prev) {
        prev->next = n->next;
        std::cout << "Deleted " << n->k << std::endl;
        delete n;
    }
}

void SingleList::list_ins_del(int k) {
    Node* node = find_node(k);
    if (node) {
        list_delete(node);
    } else {
        list_insert(k);
    }
}

void SingleList::list_reverse() {
    Node* prev = nullptr;
    Node* current = head;
    Node* next = nullptr;
    
    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

// XORList Implementation
XORList::XORList() : head(nullptr), tail(nullptr) {}

XORList::~XORList() {
    if (!head) return;
    
    Node* current = head;
    Node* prev = nullptr;
    Node* next = nullptr;
    
    while (current) {
        next = XOR(prev, reinterpret_cast<Node*>(current->npx));
        delete current;
        prev = current;
        current = next;
    }
}

Node* XORList::XOR(Node* a, Node* b) {
    return reinterpret_cast<Node*>(
        reinterpret_cast<uintptr_t>(a) ^ reinterpret_cast<uintptr_t>(b)
    );
}

void XORList::list_walk() {
    std::cout << "List: ";
    if (!head) {
        std::cout << std::endl;
        return;
    }
    
    Node* current = head;
    Node* prev = nullptr;
    Node* next = nullptr;
    bool first = true;
    
    while (current) {
        if (!first) std::cout << ", ";
        std::cout << current->k;
        first = false;
        
        next = XOR(prev, reinterpret_cast<Node*>(current->npx));
        prev = current;
        current = next;
    }
    std::cout << std::endl;
}

void XORList::list_insert(int k) {
    Node* new_node = new Node(k);
    
    if (!head) {
        head = tail = new_node;
    } else {
        new_node->npx = reinterpret_cast<uintptr_t>(head);
        head->npx = reinterpret_cast<uintptr_t>(
            XOR(new_node, reinterpret_cast<Node*>(head->npx))
        );
        head = new_node;
    }
    
    std::cout << "Inserted " << k << std::endl;
}

void XORList::list_search(int k) {
    if (!head) {
        std::cout << "Not found " << k << std::endl;
        return;
    }
    
    Node* current = head;
    Node* prev = nullptr;
    Node* next = nullptr;
    
    while (current) {
        if (current->k == k) {
            std::cout << "Found " << k << std::endl;
            return;
        }
        
        next = XOR(prev, reinterpret_cast<Node*>(current->npx));
        prev = current;
        current = next;
    }
    
    std::cout << "Not found " << k << std::endl;
}

Node* XORList::find_node(int k) {
    if (!head) return nullptr;
    
    Node* current = head;
    Node* prev = nullptr;
    Node* next = nullptr;
    
    while (current) {
        if (current->k == k) {
            return current;
        }
        
        next = XOR(prev, reinterpret_cast<Node*>(current->npx));
        prev = current;
        current = next;
    }
    
    return nullptr;
}

void XORList::list_delete(Node* n) {
    if (!n) return;
    
    if (head == tail && head == n) {
        // Only one node
        head = tail = nullptr;
        std::cout << "Deleted " << n->k << std::endl;
        delete n;
        return;
    }
    
    if (head == n) {
        // Delete head
        Node* new_head = reinterpret_cast<Node*>(head->npx);
        if (new_head) {
            new_head->npx = reinterpret_cast<uintptr_t>(
                XOR(head, reinterpret_cast<Node*>(new_head->npx))
            );
        }
        head = new_head;
        if (!head) tail = nullptr;
        std::cout << "Deleted " << n->k << std::endl;
        delete n;
        return;
    }
    
    if (tail == n) {
        // Delete tail
        Node* new_tail = reinterpret_cast<Node*>(tail->npx);
        if (new_tail) {
            new_tail->npx = reinterpret_cast<uintptr_t>(
                XOR(tail, reinterpret_cast<Node*>(new_tail->npx))
            );
        }
        tail = new_tail;
        if (!tail) head = nullptr;
        std::cout << "Deleted " << n->k << std::endl;
        delete n;
        return;
    }
    
    // Delete middle node - need to traverse to find neighbors
    Node* current = head;
    Node* prev = nullptr;
    Node* next = nullptr;
    
    while (current && current != n) {
        next = XOR(prev, reinterpret_cast<Node*>(current->npx));
        prev = current;
        current = next;
    }
    
    if (current == n) {
        Node* next_node = XOR(prev, reinterpret_cast<Node*>(current->npx));
        
        if (prev) {
            prev->npx = reinterpret_cast<uintptr_t>(
                XOR(XOR(current, reinterpret_cast<Node*>(prev->npx)), next_node)
            );
        }
        
        if (next_node) {
            next_node->npx = reinterpret_cast<uintptr_t>(
                XOR(prev, XOR(current, reinterpret_cast<Node*>(next_node->npx)))
            );
        }
        
        std::cout << "Deleted " << n->k << std::endl;
        delete n;
    }
}

void XORList::list_ins_del(int k) {
    Node* node = find_node(k);
    if (node) {
        list_delete(node);
    } else {
        list_insert(k);
    }
}

void XORList::list_reverse() {
    // Simply swap head and tail for XOR list
    Node* temp = head;
    head = tail;
    tail = temp;
}

// Test Functions
TestResults slist_test() {
    std::cout << "=== SingleList Test ===" << std::endl;
    
    SingleList slist;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);
    
    // 測量 insert 操作時間
    auto start_insert = std::chrono::high_resolution_clock::now();
    std::unordered_set<int> inserted;
    for (int i = 0; i < 200000; ++i) {
        int k;
        do {
            k = dis(gen);
        } while (inserted.count(k));
        inserted.insert(k);
        slist.list_insert(k);
    }
    auto end_insert = std::chrono::high_resolution_clock::now();
    auto insert_time = std::chrono::duration_cast<std::chrono::microseconds>(end_insert - start_insert);
    
    // 測量 insert_delete 操作時間
    auto start_ins_del = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 200000; ++i) {
        int k = dis(gen);
        slist.list_ins_del(k);
    }
    auto end_ins_del = std::chrono::high_resolution_clock::now();
    auto ins_del_time = std::chrono::duration_cast<std::chrono::microseconds>(end_ins_del - start_ins_del);
    
    // 測量 walk 操作時間
    std::cout << "\nCalling list_walk():" << std::endl;
    auto start_walk = std::chrono::high_resolution_clock::now();
    slist.list_walk();
    auto end_walk = std::chrono::high_resolution_clock::now();
    auto walk_time = std::chrono::duration_cast<std::chrono::microseconds>(end_walk - start_walk);
    
    // 測量 reverse 操作時間
    std::cout << "\nCalling list_reverse()..." << std::endl;
    auto start_reverse = std::chrono::high_resolution_clock::now();
    slist.list_reverse();
    auto end_reverse = std::chrono::high_resolution_clock::now();
    auto reverse_time = std::chrono::duration_cast<std::chrono::microseconds>(end_reverse - start_reverse);
    
    std::cout << "\nCalling list_walk() after reverse:" << std::endl;
    auto start_walk2 = std::chrono::high_resolution_clock::now();
    slist.list_walk();
    auto end_walk2 = std::chrono::high_resolution_clock::now();
    auto walk2_time = std::chrono::duration_cast<std::chrono::microseconds>(end_walk2 - start_walk2);
    
    // 返回時間結果
    return {insert_time.count(), ins_del_time.count(), walk_time.count(), 
            reverse_time.count(), walk2_time.count()};
}

TestResults xlist_test() {
    std::cout << "\n=== XORList Test ===" << std::endl;
    
    XORList xlist;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);
    
    // 測量 insert 操作時間
    auto start_insert = std::chrono::high_resolution_clock::now();
    std::unordered_set<int> inserted;
    for (int i = 0; i < 200000; ++i) {
        int k;
        do {
            k = dis(gen);
        } while (inserted.count(k));
        inserted.insert(k);
        xlist.list_insert(k);
    }
    auto end_insert = std::chrono::high_resolution_clock::now();
    auto insert_time = std::chrono::duration_cast<std::chrono::microseconds>(end_insert - start_insert);
    
    // 測量 insert_delete 操作時間
    auto start_ins_del = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 200000; ++i) {
        int k = dis(gen);
        xlist.list_ins_del(k);
    }
    auto end_ins_del = std::chrono::high_resolution_clock::now();
    auto ins_del_time = std::chrono::duration_cast<std::chrono::microseconds>(end_ins_del - start_ins_del);
    
    // 測量 walk 操作時間
    std::cout << "\nCalling list_walk():" << std::endl;
    auto start_walk = std::chrono::high_resolution_clock::now();
    xlist.list_walk();
    auto end_walk = std::chrono::high_resolution_clock::now();
    auto walk_time = std::chrono::duration_cast<std::chrono::microseconds>(end_walk - start_walk);
    
    // 測量 reverse 操作時間
    std::cout << "\nCalling list_reverse()..." << std::endl;
    auto start_reverse = std::chrono::high_resolution_clock::now();
    xlist.list_reverse();
    auto end_reverse = std::chrono::high_resolution_clock::now();
    auto reverse_time = std::chrono::duration_cast<std::chrono::microseconds>(end_reverse - start_reverse);
    
    std::cout << "\nCalling list_walk() after reverse:" << std::endl;
    auto start_walk2 = std::chrono::high_resolution_clock::now();
    xlist.list_walk();
    auto end_walk2 = std::chrono::high_resolution_clock::now();
    auto walk2_time = std::chrono::duration_cast<std::chrono::microseconds>(end_walk2 - start_walk2);
    
    // 返回時間結果
    return {insert_time.count(), ins_del_time.count(), walk_time.count(), 
            reverse_time.count(), walk2_time.count()};
}

int main() {
    TestResults slist_results = slist_test();
    TestResults xlist_results = xlist_test();
    
    // 統一顯示所有時間結果
    std::cout << "\n=== Performance Results Comparison ===" << std::endl;
    
    std::cout << "\n=== SingleList Performance Results ===" << std::endl;
    std::cout << "Insert operations time: " << slist_results.insert_time << " μs" << std::endl;
    std::cout << "Insert-delete operations time: " << slist_results.ins_del_time << " μs" << std::endl;
    std::cout << "Walk operation time: " << slist_results.walk_time << " μs" << std::endl;
    std::cout << "Reverse operation time: " << slist_results.reverse_time << " μs" << std::endl;
    std::cout << "Walk after reverse time: " << slist_results.walk2_time << " μs" << std::endl;
    
    std::cout << "\n=== XORList Performance Results ===" << std::endl;
    std::cout << "Insert operations time: " << xlist_results.insert_time << " μs" << std::endl;
    std::cout << "Insert-delete operations time: " << xlist_results.ins_del_time << " μs" << std::endl;
    std::cout << "Walk operation time: " << xlist_results.walk_time << " μs" << std::endl;
    std::cout << "Reverse operation time: " << xlist_results.reverse_time << " μs" << std::endl;
    std::cout << "Walk after reverse time: " << xlist_results.walk2_time << " μs" << std::endl;
    
    return 0;
}