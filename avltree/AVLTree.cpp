#include "AVLTree.h"
#include <functional>

/********************************************************************
 * Search
 *******************************************************************/

bool AVLTree::search(const int value) const {
    if (root == nullptr) {
        return false;
    }
    return root->search(value);
}

bool AVLTree::Node::search(const int value) const {
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

void AVLTree::insert(const int value) {
    if (root == nullptr) {
        root = new Node(nullptr, value);
    } else {
        root->insert(value);
    }
}

void AVLTree::Node::insert(const int value) {
    if (key > value) {
        if (left != nullptr) {
            left->insert(value);
        }
        left = new Node(this, value);
        if (balance == 1) {
            balance = 0;
        }
        if (balance == 0) {
            balance = -1;
            upin(this);
        }
    } else if (key == value) {
        return;
    } else {
        if (right != nullptr) {
            right->insert(value);
        }
        right = new Node(this, value);
        if (balance == -1) {
            balance = 0;
        }
        if (balance == 0) {
            balance = 1;
            upin(this);
        }
    }
}

void AVLTree::upin(AVLTree::Node *p) {
    if(p != nullptr && p->prev != nullptr) {
        if (p->balance = -1) {
            //grew left
            if (p->prev->balance == 1) {
                p->prev->balance = 0;
            } else if (p->prev->balance == 0) {
                p->prev->balance = -1;
                upin(p->prev);
            } else {
                if (p->balance = -1) {
                    rotateRight(p->prev);
                } else {
                    rotateLeft(p);
                    rotateRight(p->prev);
                }
            }
        } else {
            // grew right
            if (p->prev->balance == 1) {
                p->prev->balance = 0;
            } else if (p->prev->balance == 0) {
                p->prev->balance = -1;
                upin(p->prev);
            } else {
                if (p->balance = -1) {
                    rotateLeft(p->prev);
                } else {
                    rotateRight(p);
                    rotateLeft(p->prev);
                }
            }
        }
    }
}

/********************************************************************
 * Rotations
 *******************************************************************/

void AVLTree::rotateRight(AVLTree::Node *p) {
    auto tmpLeft = p->left;
    auto tmpPrev = p->prev;

    p->left = p->left->right;
    if (p->left != nullptr) p->left->prev = p;
    p->prev = tmpLeft;

    tmpLeft->right = p;
    tmpLeft->prev = tmpPrev;
    if (tmpPrev != nullptr) {
        if(tmpPrev->left == p) {
            tmpPrev->left = tmpLeft;
        } else {
            tmpPrev->right = tmpLeft;
        }
    }

    tmpLeft->balance += 1;
    p->balance += 1;
}

void AVLTree::rotateLeft(AVLTree::Node *p) {
    auto tmpRight = p->left;
    auto tmpPrev = p->prev;

    p->right = p->right->left;
    if (p->right != nullptr) p->right->prev = p;
    p->prev = tmpRight;

    tmpRight->left = p;
    tmpRight->prev = tmpPrev;
    if (tmpPrev != nullptr) {
        if(tmpPrev->left == p) {
            tmpPrev->left = tmpRight;
        } else {
            tmpPrev->right = tmpRight;
        }
    }

    tmpRight->balance -= 1;
    p->balance -= 1;
}

/********************************************************************
 * Traversal
 *******************************************************************/

vector<int> *AVLTree::preorder() const {
    if (root == nullptr)
        return nullptr;
    return root->preorder();
}

vector<int> *AVLTree::Node::preorder() const {
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

vector<int> *AVLTree::inorder() const {
    if (root == nullptr)
        return nullptr;
    return root->inorder();
}

vector<int> *AVLTree::Node::inorder() const {
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

vector<int> *AVLTree::postorder() const {
    if (root == nullptr)
        return nullptr;
    return root->postorder();
}

vector<int> *AVLTree::Node::postorder() const {
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

/********************************************************************
 * operator<<
 *******************************************************************/
std::ostream &operator<<(std::ostream &os, const AVLTree &tree) {
    function<void(std::ostream &, const int, const AVLTree::Node *, const string)> printToOs
            = [&](std::ostream &os, const int value, const AVLTree::Node *node, const string l) {

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

/********************************************************************
 * Node constructors destructors
 *******************************************************************/

AVLTree::Node::Node(Node *p, const int k) : key(k) {
    prev = p;
}

AVLTree::Node::Node(Node *p, const int k, Node *l, Node *r) : key(k) {
    prev = p;
    left = l;
    right = r;
}

AVLTree::Node::~Node() {
    delete left;
    delete right;
}

/********************************************************************
 * Tree destructor
 *******************************************************************/

AVLTree::~AVLTree() {
    delete root;
}




