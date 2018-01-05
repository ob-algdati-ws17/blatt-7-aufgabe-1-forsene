#include <iostream>
#include "AVLTree.h"

int main() {
    AVLTree a;
    a.insert(5);
    a.insert(7);
    a.insert(2);
    a.insert(6);
    a.insert(3);
    a.insert(1);
    a.insert(4);
    a.remove(7);

    cout << a;
}