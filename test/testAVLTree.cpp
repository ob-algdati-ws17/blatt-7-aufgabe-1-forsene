#include "testAVLTree.h"
#include <memory>

using namespace std;

// empty tree

TEST(AVLTreeTest, Empty_Tree) {
    AVLTree b;
    EXPECT_EQ(nullptr, b.preorder());
    EXPECT_EQ(nullptr, b.inorder());
    EXPECT_EQ(nullptr, b.postorder());
}

// search, insert, remove

TEST(AVLTreeTest, InsertIntoEmpty) {
    AVLTree a;
    a.insert(5);
    EXPECT_TRUE(a.search(5));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(5));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(5));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(5));
}

TEST(AVLTreeTest, InsertSomeNodes) {
    AVLTree a;
    a.insert(5);
    a.insert(4);
    a.insert(6);
    a.insert(3);
    EXPECT_TRUE(a.search(5));
    EXPECT_TRUE(a.search(4));
    EXPECT_TRUE(a.search(6));
    EXPECT_TRUE(a.search(3));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(5,4,3,6));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(3,4,5,6));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(3,4,6,5));
}

TEST(AVLTreeTest, InsertSomeNodes2) {
    AVLTree a;
    a.insert(2);
    a.insert(3);
    a.insert(1);
    a.insert(4);
    EXPECT_TRUE(a.search(2));
    EXPECT_TRUE(a.search(3));
    EXPECT_TRUE(a.search(1));
    EXPECT_TRUE(a.search(4));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(2,1,3,4));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(1,2,3,4));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(1,4,3,2));
}

TEST(AVLTreeTest, InsertSomeNodes3) {
    AVLTree a;
    a.insert(15);
    a.insert(10);
    a.insert(20);
    a.insert(7);
    a.insert(13);
    a.insert(17);
    a.insert(21);
    a.insert(16);

    EXPECT_TRUE(a.search(15));
    EXPECT_TRUE(a.search(10));
    EXPECT_TRUE(a.search(20));
    EXPECT_TRUE(a.search(7));
    EXPECT_TRUE(a.search(13));
    EXPECT_TRUE(a.search(17));
    EXPECT_TRUE(a.search(21));
    EXPECT_TRUE(a.search(16));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(15,10,7,13,20,17,16,21));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(7,10,13,15,16,17,20,21));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(7,13,10,16,17,21,20,15));
}
 // rotation test
TEST(AVLTreeTest, InsertRotationRightOnRoot) {
    AVLTree a;
    a.insert(3);
    a.insert(2);
    a.insert(1);
    EXPECT_TRUE(a.search(3));
    EXPECT_TRUE(a.search(2));
    EXPECT_TRUE(a.search(1));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(2,1,3));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(1,2,3));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(1,3,2));
}

TEST(AVLTreeTest, InsertRotationRightNotRoot) {
    AVLTree a;
    a.insert(4);
    a.insert(2);
    a.insert(9);
    a.insert(1);
    a.insert(3);
    a.insert(7);
    a.insert(10);
    a.insert(6);
    a.insert(8);
    a.insert(5);
    EXPECT_TRUE(a.search(1));
    EXPECT_TRUE(a.search(2));
    EXPECT_TRUE(a.search(3));
    EXPECT_TRUE(a.search(4));
    EXPECT_TRUE(a.search(5));
    EXPECT_TRUE(a.search(6));
    EXPECT_TRUE(a.search(7));
    EXPECT_TRUE(a.search(8));
    EXPECT_TRUE(a.search(9));
    EXPECT_TRUE(a.search(10));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(4,2,1,3,7,6,5,9,8,10));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(1,2,3,4,5,6,7,8,9,10));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(1,3,2,5,6,8,10,9,7,4));
}

TEST(AVLTreeTest, InsertRotationLeftOnRoot) {
    AVLTree a;
    a.insert(1);
    a.insert(2);
    a.insert(3);
    EXPECT_TRUE(a.search(1));
    EXPECT_TRUE(a.search(2));
    EXPECT_TRUE(a.search(3));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(2,1,3));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(1,2,3));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(1,3,2));
}

TEST(AVLTreeTest, InsertRotationLeftNotRoot) {
    AVLTree a;
    a.insert(7);
    a.insert(9);
    a.insert(2);
    a.insert(10);
    a.insert(8);
    a.insert(4);
    a.insert(1);
    a.insert(5);
    a.insert(3);
    a.insert(6);
    EXPECT_TRUE(a.search(1));
    EXPECT_TRUE(a.search(2));
    EXPECT_TRUE(a.search(3));
    EXPECT_TRUE(a.search(4));
    EXPECT_TRUE(a.search(5));
    EXPECT_TRUE(a.search(6));
    EXPECT_TRUE(a.search(7));
    EXPECT_TRUE(a.search(8));
    EXPECT_TRUE(a.search(9));
    EXPECT_TRUE(a.search(10));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(7,4,2,1,3,5,6,9,8,10));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(1,2,3,4,5,6,7,8,9,10));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(1,3,2,6,5,4,8,10,9,7));
}

TEST(AVLTreeTest, InsertRotationLeftRightOnRoot) {
    AVLTree a;
    a.insert(4);
    a.insert(3);
    a.insert(5);
    a.insert(1);
    a.insert(2);
    EXPECT_TRUE(a.search(1));
    EXPECT_TRUE(a.search(2));
    EXPECT_TRUE(a.search(3));
    EXPECT_TRUE(a.search(4));
    EXPECT_TRUE(a.search(5));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(4,2,1,3,5));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(1,2,3,4,5));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(1,3,2,5,4));
}

TEST(AVLTreeTest, InsertRotationLeftRightNotRoot) {
    AVLTree a;
    a.insert(7);
    a.insert(5);
    a.insert(9);
    a.insert(2);
    a.insert(6);
    a.insert(8);
    a.insert(10);
    a.insert(1);
    a.insert(4);
    a.insert(3);
    EXPECT_TRUE(a.search(1));
    EXPECT_TRUE(a.search(2));
    EXPECT_TRUE(a.search(3));
    EXPECT_TRUE(a.search(4));
    EXPECT_TRUE(a.search(5));
    EXPECT_TRUE(a.search(6));
    EXPECT_TRUE(a.search(7));
    EXPECT_TRUE(a.search(8));
    EXPECT_TRUE(a.search(9));
    EXPECT_TRUE(a.search(10));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(7,4,2,1,3,5,6,9,8,10));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(1,2,3,4,5,6,7,8,9,10));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(1,3,2,6,5,4,8,10,9,7));
}

TEST(AVLTreeTest, InsertRotationRightLeftOnRoot) {
    AVLTree a;
    a.insert(2);
    a.insert(1);
    a.insert(3);
    a.insert(5);
    a.insert(4);
    EXPECT_TRUE(a.search(1));
    EXPECT_TRUE(a.search(2));
    EXPECT_TRUE(a.search(3));
    EXPECT_TRUE(a.search(4));
    EXPECT_TRUE(a.search(5));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(2,1,4,3,5));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(1,2,3,4,5));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(1,3,5,4,2));
}

TEST(AVLTreeTest, InsertRotationRightLeftNotRoot) {
    AVLTree a;
    a.insert(4);
    a.insert(6);
    a.insert(2);
    a.insert(9);
    a.insert(5);
    a.insert(3);
    a.insert(1);
    a.insert(10);
    a.insert(7);
    a.insert(8);
    EXPECT_TRUE(a.search(1));
    EXPECT_TRUE(a.search(2));
    EXPECT_TRUE(a.search(3));
    EXPECT_TRUE(a.search(4));
    EXPECT_TRUE(a.search(5));
    EXPECT_TRUE(a.search(6));
    EXPECT_TRUE(a.search(7));
    EXPECT_TRUE(a.search(8));
    EXPECT_TRUE(a.search(9));
    EXPECT_TRUE(a.search(10));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(4,2,1,3,7,6,5,9,8,10));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(1,2,3,4,5,6,7,8,9,10));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(1,3,2,5,6,8,10,9,7,4));
}