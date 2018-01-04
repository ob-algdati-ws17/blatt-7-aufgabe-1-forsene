#include "AVLTree.h"
#include <functional>

/********************************************************************
 * Search
 *******************************************************************/

bool AVLTree::search(const int value) const {
    if (root == nullptr) {
        return false;
    }
    return search(value, root);
}

bool AVLTree::search(const int value, AVLTree::Node *n) const {
    if (n->key > value) {
        if (n->left != nullptr) {
            return search(value, n->left);
        }
        return false;
    } else if (n->key == value) {
        return true;
    } else {
        if (right != nullptr) {
            return search(value, n->right);
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
        insert(value, root);
    }
}

void AVLTree::insert(const int value, AVLTree::Node *n) {
    if (n->key > value) {
        if (n->left != nullptr) {
            insert(value, n->left);
        } else {
            n->left = new Node(n, value);
            n->balance -= 1;
        }
        if (n->balance == -1) upin(n);
    } else if (n->key == value) {
        return;
    } else {
        if (n->right != nullptr) {
            insert(value, n->right);
        } else {
            n->right = new Node(n, value);
            n->balance += 1;
            if (n->balance == 1) upin(n);
        }
    }
}

void AVLTree::upin(AVLTree::Node *n) {
    if(n!= nullptr && n->prev != nullptr) {
        auto tmpPrev = n->prev;
        if (n == tmpPrev->left) {
            //grew left
            if (tmpPrev->balance == 1) {
                tmpPrev->balance = 0;
            } else if (n->prev->balance == 0) {
                tmpPrev->balance = -1;
                upin(tmpPrev);
            } else {
                if (n->balance == -1) {
                    rotateRight(tmpPrev);
                } else {
                    rotateLeft(n);
                    rotateRight(tmpPrev);
                }
            }
        } else {
            // grew right
            if (tmpPrev->balance == -1) {
                tmpPrev->balance = 0;
            } else if (n->prev->balance == 0) {
                tmpPrev->balance = 1;
                upin(tmpPrev);
            } else {
                if (n->balance == 1) {
                    rotateLeft(tmpPrev);
                } else {
                    rotateRight(n);
                    rotateLeft(tmpPrev);
                }
            }
        }
    }
}

/********************************************************************
 * Rotations
 *******************************************************************/

void AVLTree::rotateRight(AVLTree:: Node *n) {
    auto tmpLeft = n->left;
    auto tmpPrev = n->prev;

    n->left = n->left->right;
    if (n->left != nullptr) n->left->prev = n;
    n->prev = tmpLeft;

    tmpLeft->right = n;
    tmpLeft->prev = tmpPrev;
    if (tmpPrev != nullptr) {
        if(tmpPrev->left == n) {
            tmpPrev->left = tmpLeft;
        } else {
            tmpPrev->right = tmpLeft;
        }
    } else {
        root = tmpLeft;
    }

    tmpLeft->balance += 1;
    n->balance += 1;
}

void AVLTree::rotateLeft(AVLTree:: Node *n) {
    auto tmpRight = n->right;
    auto tmpPrev = n->prev;

    n->right = n->right->left;
    if (n->right != nullptr) n->right->prev = n;
    n->prev = tmpRight;

    tmpRight->left = n;
    tmpRight->prev = tmpPrev;
    if (tmpPrev != nullptr) {
        if(tmpPrev->left == n) {
            tmpPrev->left = tmpRight;
        } else {
            tmpPrev->right = tmpRight;
        }
    } else {
        root = tmpRight;
    }

    tmpRight->balance -= 1;
    n->balance -= 1;
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





