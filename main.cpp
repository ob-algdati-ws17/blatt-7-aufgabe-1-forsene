#include <iostream>
#include "AVLTree.h"

int main() {
    AVLTree a;
    a.insert(10);
    a.insert(5);
    a.insert(15);
    a.insert(2);
    a.insert(7);
    a.insert(12);
    a.insert(17);
    a.insert(1);
    //a.insert(0);
    cout << a;
}