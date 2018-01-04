#include <iostream>
#include "AVLTree.h"

int main() {
    AVLTree a;
    a.insert(15);
    a.insert(25);
    a.insert(35);
    cout << a;
}