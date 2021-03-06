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
    if(n == nullptr) {
        return false;
    }
    if (n->key > value) {
        return search(value, n->left);
    } else if (n->key == value) {
        return true;
    } else {
        return search(value, n->right);
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
            // Update balance
            n->balance--;
            if (n->balance == -1) upin(n);
        }
    } else if (n->key == value) {
        return;
    } else {
        if (n->right != nullptr) {
            insert(value, n->right);
        } else {
            n->right = new Node(n, value);
            // Update balance
            n->balance++;
            if (n->balance == 1) upin(n);
        }
    }
}

/********************************************************************
 * Remove
 *******************************************************************/

void AVLTree::remove(const int value) {
    if (root != nullptr) {
        remove(value, root);
    }
}

void AVLTree::remove(const int value, AVLTree::Node *n) {
    if (n->key > value) {
        if (n->left != nullptr) {
            remove(value, n->left);
        }
        return;
    } else if (n->key == value) {
        if (n->left == nullptr && n->right == nullptr) {
            removeTwoLeaves(n);
        } else if (n->left == nullptr) {
            removeOneLeaf(n, false);
        } else if (n->right == nullptr) {
            removeOneLeaf(n, true);
        } else {
            removeLeafless(n);
        }
    } else {
        if (right != nullptr) {
            remove(value, n->right);
        }
    }
}

void AVLTree::removeTwoLeaves(AVLTree::Node *n) {
    // remove and update previous balance
    if(n->prev != nullptr) {
        if(n == n->prev->left) {
            n->prev->left = nullptr;
            n->prev->balance++;
        } else {
            n->prev->right = nullptr;
            n->prev->balance--;
        }


        // if abs(balance) != 1, further action is necessary
        if(n->prev->balance == 0) {
            upout(n->prev);
        } else if(n->prev->balance == -2) {
            //left tree height was 2
            auto tmpPrev = n->prev;
            if(tmpPrev->left->left == nullptr) {
                rotateLeft(tmpPrev->left);
                rotateRight(tmpPrev);
            } else {
                rotateRight(tmpPrev);
            }
            if(tmpPrev->balance == 0) {
                upout(tmpPrev);
            }
        } else if(n->prev->balance == 2) {
            //right tree height was 2
            auto tmpPrev = n->prev;
            if (tmpPrev->right->right == nullptr) {
                rotateRight(tmpPrev->right);
                rotateLeft(tmpPrev);
            } else {
                rotateLeft(tmpPrev);
            }
            if (tmpPrev->balance == 0) {
                upout(tmpPrev);
            }
        }
    } else {
        root = nullptr;
    }

    delete n;
}

void AVLTree::removeOneLeaf(AVLTree::Node *n, bool leftSide) {

    if (n->prev != nullptr) {
        // grab key from the only child
        n->key = leftSide ? n->left->key : n->right->key;
        n->balance = 0;
    } else {
        if(leftSide) {
            root = n->left;
        } else {
            root = n->right;
        }
    }

    upout(n);

    n->left = nullptr;
    n->right = nullptr;
    // delete child
    delete (leftSide? n->left : n->right);
}

void AVLTree::removeLeafless(AVLTree::Node *n) {
    auto fol = n->right;
    while (fol->left != nullptr) {
        fol = fol->left;
    }
    // grab key from symmetric follower
    n->key = fol->key;
    // remove the follower
    remove(fol->key, fol);
}

/********************************************************************
 * Rebalance Methods
 *******************************************************************/



void AVLTree::upin(AVLTree::Node *n) {
    if(n!= nullptr && n->prev != nullptr) {
        // upin stops at root
        auto tmpPrev = n->prev;
        if (n == tmpPrev->left) {
            //grew left
            tmpPrev->balance--;
            if(tmpPrev->balance == -1) upin(tmpPrev);
            // balance one level higher
            if(tmpPrev->balance == -2) {
                // rotation required
                if (n->balance == -1) {
                    rotateRight(tmpPrev);
                } else {
                    rotateLeft(n);
                    rotateRight(tmpPrev);
                }
            }
        } else if (n==tmpPrev->right){
            // grew right, analogical to left
            tmpPrev->balance++;
            if(tmpPrev->balance == 1) upin(tmpPrev);
            if(tmpPrev->balance == 2) {
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

void AVLTree::upout(AVLTree::Node *n) {
    if(n != nullptr && n->prev != nullptr) {
        auto tmpPrev = n->prev;
        if(n == tmpPrev->left) {
            // removed from left tree
            if(tmpPrev->balance == -1) {
                tmpPrev->balance++;
                upout(tmpPrev);
                // height of this subtree changed
            } else if(tmpPrev->balance == 0) {
                tmpPrev->balance++;
            } else {
                // new balance would be +2, so rotations are needed
                if(tmpPrev->right->balance == -1) {
                    rotateRight(tmpPrev->right);
                    rotateLeft(tmpPrev);
                    upout(tmpPrev->prev);
                } else if(tmpPrev->right->balance == 0){
                    rotateLeft(tmpPrev);
                } else {
                    rotateLeft(tmpPrev);
                    upout(tmpPrev->prev);
                }
            }
        } else if(n == tmpPrev->right) {
            // removed from right tree, analogical to left
            if(tmpPrev->balance == 1) {
                tmpPrev->balance--;
                upout(tmpPrev);
            } else if(tmpPrev->balance == 0) {
                tmpPrev->balance--;
            } else {
                if(tmpPrev->left->balance == 1) {
                    rotateLeft(tmpPrev->left);
                    rotateRight(tmpPrev);
                    upout(tmpPrev->prev);
                } else if(tmpPrev->left->balance == 0){
                    rotateRight(tmpPrev);
                } else {
                    rotateRight(tmpPrev);
                    upout(tmpPrev->prev);
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
    // swap head to its right
    n->left = n->left->right;
    if (n->left != nullptr) n->left->prev = n;
    n->prev = tmpLeft;
    // swap heads left to head
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
    //adjust balances
    tmpLeft->balance++;
    n->balance++;
}

void AVLTree::rotateLeft(AVLTree:: Node *n) {
    // analogical to left
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

    tmpRight->balance--;
    n->balance--;
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












