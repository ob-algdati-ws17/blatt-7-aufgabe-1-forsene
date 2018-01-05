#include <iostream>
#include "AVLTree.h"

int main() {
    AVLTree a;
    a.insert(3);
    a.insert(5);
    a.insert(1);
    a.insert(4);
    a.remove(1);
    //a.insert(1);
    //a.insert(4);
    //a.insert(3);
    //a.insert(5);
    //a.insert(8);
    //a.insert(1);
    //a.insert(5);
    cout << a;
}