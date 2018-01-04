#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

#include <iostream>
#include <vector>

using namespace std;

class AVLTree {

private:

    struct Node {
        Node *prev = nullptr;
        int key;
        Node *left = nullptr;
        Node *right = nullptr;
        int balance = 0;
        Node(Node *prev, const int key);
        Node(Node *prev, const int, Node *left, Node *right);
        ~Node();
        bool search(const int) const;
        void insert(const int);
        vector<int> *preorder() const;  // (Hauptreihenfolge)
        vector<int> *inorder() const;   // (Symmetrische Reihenfolge)
        vector<int> *postorder() const; // (Nebenreihenfolge)
    };

    Node *root = nullptr;

    static void upin(Node *p);

    static void rotateRight(Node *p);

    static void rotateLeft(Node *p);

public:

    ~AVLTree();

    bool search(const int) const;

    void insert(const int);

    void remove(const int);

    vector<int> *preorder() const;  // (Hauptreihenfolge)
    vector<int> *inorder() const;   // (Symmetrische Reihenfolge)
    vector<int> *postorder() const; // (Nebenreihenfolge)

    friend ostream &operator<<(ostream &, const AVLTree &);

};

#endif //AVLTREE_AVLTREE_H
