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
        vector<int> *preorder() const;  // (Hauptreihenfolge)
        vector<int> *inorder() const;   // (Symmetrische Reihenfolge)
        vector<int> *postorder() const; // (Nebenreihenfolge)
    };

    Node *root = nullptr;

    bool search(const int, Node *) const;
    void insert(const int, Node *);
    void remove(const int, Node *);
    void upin(Node *);
    void upout(Node *);
    void removeTwoLeaves(Node *);
    void removeOneLeaf(Node *, bool);
    void removeLeafless(Node *);
    void rotateRight(Node *);
    void rotateLeft(Node *);

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
