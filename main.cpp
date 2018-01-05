#include <iostream>
#include "AVLTree.h"

int main() {
    AVLTree a;
    a.insert(4);
    a.insert(2);
    a.insert(7);
    a.insert(1);
    a.insert(3);
    a.insert(5);
    a.insert(9);
    a.insert(6);
    a.insert(8);
    a.insert(10);
    a.insert(0);
    a.insert(11);
    a.remove(4);
    cout << a;
}