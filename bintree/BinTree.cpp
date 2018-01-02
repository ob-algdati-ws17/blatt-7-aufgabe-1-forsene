#include "BinTree.h"
#include <functional>

using namespace ::std;

/********************************************************************
 * Search
 *******************************************************************/

bool BinTree::search(const int value) const {
    if (root == nullptr) {
        return false;
    }
    return root->search(value);
}

bool BinTree::Node::search(const int value) const {
    if (key > value) {
        if (left != nullptr) {
            return left->search(value);
        }
        return false;
    } else if (key == value) {
        return true;
    } else {
        if (right != nullptr) {
            return right->search(value);
        }
        return false;
    }
}

/********************************************************************
 * Insert
 *******************************************************************/

void BinTree::insert(const int value) {
    if (root == nullptr) {
        root = new Node(value);
    } else {
        root->insert(value);
    }
}

void BinTree::Node::insert(const int value) {
    auto *n = new Node(value);
    if (key > value) {
        if (left != nullptr) {
            left->insert(value);
        }
        left = n;
    } else if (key == value) {
        return;
    } else {
        if (right != nullptr) {
            right->insert(value);
        }
        right = n;
    }
}

/********************************************************************
 * Remove
 *******************************************************************/

void BinTree::remove(const int value) {
    if (root == nullptr) {
        return;
    } else if (root->key == value) {
        if (root->left == nullptr) {
            root = root->right;
        } else if (root->right == nullptr) {
            root = root->left;
        } else {
            //todo
        }
    } else {
        root->remove(value);
    }
}


BinTree::Node *BinTree::Node::remove(const int value) {
    if (key > value) {
        if (left != nullptr) {
            left = left->remove(value);
        }
        return this;
    } else if (key == value) {
        if (left == nullptr && right == nullptr) {
            delete this;
            return nullptr;
        } else {
            //todo
            return nullptr;
        }
    } else {
        if (right != nullptr) {
            right = right->remove(value);
        }
        return this;
    }
}

/********************************************************************
 * Traversal
 *******************************************************************/

vector<int> *BinTree::preorder() const {
    if (root == nullptr)
        return nullptr;
    return root->preorder();
}

vector<int> *BinTree::Node::preorder() const {
    auto vec = new vector<int>();
    // Wurzel in vec
    vec->push_back(key);
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->preorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->preorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    return vec;
}

vector<int> *BinTree::inorder() const {
    if (root == nullptr)
        return nullptr;
    return root->inorder();
}

vector<int> *BinTree::Node::inorder() const {
    auto vec = new vector<int>();
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->inorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // Wurzel in vec
    vec->push_back(key);
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->inorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    return vec;
}

vector<int> *BinTree::postorder() const {
    if (root == nullptr)
        return nullptr;
    return root->postorder();
}

vector<int> *BinTree::Node::postorder() const {
    auto vec = new vector<int>();
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->postorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->postorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    // Wurzel in vec
    vec->push_back(key);
    return vec;
}

BinTree::Node::Node(const int k) : key(k) {
}

BinTree::Node::Node(const int k, BinTree::Node *l, BinTree::Node *r) : key(k) {
    left = l;
    right = r;
}

BinTree::Node::~Node() {
    delete left;
    delete right;
}


/********************************************************************
 * operator<<
 *******************************************************************/
std::ostream &operator<<(std::ostream &os, const BinTree &tree) {
    function<void(std::ostream &, const int, const BinTree::Node *, const string)> printToOs
            = [&](std::ostream &os, const int value, const BinTree::Node *node, const string l) {

                static int nullcount = 0;

                if (node == nullptr) {
                    os << "    null" << nullcount << "[shape=point];" << endl;
                    os << "    " << value << " -> null" << nullcount
                       << " [label=\"" << l << "\"];" << endl;
                    nullcount++;
                } else {
                    os << "    " << value << " -> " << node->key
                       << " [label=\"" << l << "\"];" << endl;

                    printToOs(os, node->key, node->left, "l");
                    printToOs(os, node->key, node->right, "r");
                }
            };
    os << "digraph tree {" << endl;
    if (tree.root == nullptr) {
        os << "    null " << "[shape=point];" << endl;
    } else {
        printToOs(os, tree.root->key, tree.root->left, "l");
        printToOs(os, tree.root->key, tree.root->right, "r");
    }
    os << "}" << endl;
    return os;
}

BinTree::~BinTree() {
    delete root;
}
