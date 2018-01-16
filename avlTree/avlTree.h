#ifndef AVLTREE_H
#define AVLTREE_H

#endif //AVLTREE_H

#include <iostream>
#include <string>
#include <vector>

class avlTree {
private:
    struct Node {
        int key;
        Node *left = nullptr;
        Node *right = nullptr;
        Node *parent = nullptr;

        int balance = 0;

        Node(int k, Node* p) : key(k), parent(p){}
        Node(const int k, Node *p, Node *l, Node *r, int b) : key(k), parent(p), left(l), right(r), balance(b) {}

        ~Node();

        bool hasChild() const;
    };

    Node *root = nullptr;

    Node* getSymmetricFollower(Node* node);

    void upIn(Node* start);
    void upOut(Node* start);
    void rotateLeft(Node* rotateThis);
    void rotateRight(Node* rotateThis);
    int getHeight(Node* p);

    // Is tree in order?
    std::vector<int> *sortTree(Node *node, std::vector<int> *tree) const;

public :

    ~avlTree();

    void insert(const int value);
    void remove(const int value);
    void remove(const int value, Node* node);
    bool search(const int value) const;
    bool search(const int value, Node* node) const;

    std::vector<int> *sortTree() const;   // (symmetric order)

};
