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

TEST(AVLTreeTest, RemoveRoot) {
    AVLTree a;
    a.insert(5);
    EXPECT_TRUE(a.search(5));
    a.remove(5);
    EXPECT_FALSE(a.search(5));
    EXPECT_EQ(nullptr, a.preorder());
    EXPECT_EQ(nullptr, a.inorder());
    EXPECT_EQ(nullptr, a.postorder());
}

TEST(AVLTreeTest, RemoveSomeTwoLeavesNodes) {
    AVLTree a;
    a.insert(15);
    a.insert(10);
    a.insert(20);
    a.insert(8);
    a.insert(13);
    a.insert(17);
    a.insert(23);
    a.insert(25);
    EXPECT_TRUE(a.search(15));
    EXPECT_TRUE(a.search(10));
    EXPECT_TRUE(a.search(20));
    EXPECT_TRUE(a.search(8));
    EXPECT_TRUE(a.search(13));
    EXPECT_TRUE(a.search(17));
    EXPECT_TRUE(a.search(23));
    EXPECT_TRUE(a.search(25));
    a.remove(25);
    EXPECT_FALSE(a.search(25));
    a.remove(23);
    EXPECT_FALSE(a.search(23));
    a.remove(17);
    EXPECT_FALSE(a.search(17));
    a.remove(13);
    EXPECT_FALSE(a.search(13));
    a.remove(8);
    EXPECT_FALSE(a.search(8));
    a.remove(10);
    EXPECT_FALSE(a.search(10));
    a.remove(20);
    EXPECT_FALSE(a.search(20));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(15));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(15));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(15));
}

TEST(AVLTreeTest, RemoveLeavesNodeRotateRightOnRoot) {
    AVLTree a;
    a.insert(4);
    a.insert(5);
    a.insert(2);
    a.insert(3);
    a.insert(1);
    EXPECT_TRUE(a.search(1));
    EXPECT_TRUE(a.search(2));
    EXPECT_TRUE(a.search(3));
    EXPECT_TRUE(a.search(4));
    EXPECT_TRUE(a.search(5));
    a.remove(5);
    EXPECT_FALSE(a.search(5));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(2,1,4,3));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(1,2,3,4));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(1,3,4,2));
}

TEST(AVLTreeTest, RemoveLeavesNodeRotateLeftOnRoot) {
    AVLTree a;
    a.insert(2);
    a.insert(1);
    a.insert(4);
    a.insert(3);
    a.insert(5);
    EXPECT_TRUE(a.search(1));
    EXPECT_TRUE(a.search(2));
    EXPECT_TRUE(a.search(3));
    EXPECT_TRUE(a.search(4));
    EXPECT_TRUE(a.search(5));
    a.remove(1);
    EXPECT_FALSE(a.search(1));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(4,2,3,5));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(2,3,4,5));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(3,2,5,4));
}

TEST(AVLTreeTest, RemoveLeavesNodeRotateRightLeftOnRoot) {
    AVLTree a;
    a.insert(2);
    a.insert(1);
    a.insert(4);
    a.insert(3);
    EXPECT_TRUE(a.search(1));
    EXPECT_TRUE(a.search(2));
    EXPECT_TRUE(a.search(3));
    EXPECT_TRUE(a.search(4));
    a.remove(1);
    EXPECT_FALSE(a.search(1));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(3,2,4));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(2,3,4));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(2,4,3));
}

TEST(AVLTreeTest, RemoveLeavesNodeRotateLeftRightOnRoot) {
    AVLTree a;
    a.insert(3);
    a.insert(4);
    a.insert(1);
    a.insert(2);
    EXPECT_TRUE(a.search(1));
    EXPECT_TRUE(a.search(2));
    EXPECT_TRUE(a.search(3));
    EXPECT_TRUE(a.search(4));
    a.remove(4);
    EXPECT_FALSE(a.search(4));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(2,1,3));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(1,2,3));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(1,3,2));
}

TEST(AVLTreeTest, RemoveLeavesNodeRotateRightNotRoot) {
    AVLTree a;
    a.insert(6);
    a.insert(4);
    a.insert(8);
    a.insert(2);
    a.insert(5);
    a.insert(7);
    a.insert(9);
    a.insert(1);
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
    a.remove(5);
    EXPECT_FALSE(a.search(5));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(6,2,1,4,3,8,7,9));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(1,2,3,4,6,7,8,9));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(1,3,4,2,7,9,8,6));
}

TEST(AVLTreeTest, RemoveLeavesNodeRotateLeftNotRoot) {
    AVLTree a;
    a.insert(6);
    a.insert(2);
    a.insert(8);
    a.insert(1);
    a.insert(4);
    a.insert(7);
    a.insert(9);
    a.insert(3);
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
    a.remove(1);
    EXPECT_FALSE(a.search(1));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(6,4,2,3,5,8,7,9));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(2,3,4,5,6,7,8,9));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(3,2,5,4,7,9,8,6));
}

TEST(AVLTreeTest, RemoveLeavesNodeRotateRightLeftNotRoot) {
    AVLTree a;
    a.insert(5);
    a.insert(2);
    a.insert(7);
    a.insert(1);
    a.insert(4);
    a.insert(6);
    a.insert(8);
    a.insert(3);
    EXPECT_TRUE(a.search(1));
    EXPECT_TRUE(a.search(2));
    EXPECT_TRUE(a.search(3));
    EXPECT_TRUE(a.search(4));
    EXPECT_TRUE(a.search(5));
    EXPECT_TRUE(a.search(6));
    EXPECT_TRUE(a.search(7));
    EXPECT_TRUE(a.search(8));
    a.remove(1);
    EXPECT_FALSE(a.search(1));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(5,3,2,4,7,6,8));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(2,3,4,5,6,7,8));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(2,4,3,6,8,7,5));
}

TEST(AVLTreeTest, RemoveLeavesNodeRotateLeftRightNotRoot) {
    AVLTree a;
    a.insert(5);
    a.insert(3);
    a.insert(7);
    a.insert(4);
    a.insert(1);
    a.insert(8);
    a.insert(6);
    a.insert(2);
    EXPECT_TRUE(a.search(1));
    EXPECT_TRUE(a.search(2));
    EXPECT_TRUE(a.search(3));
    EXPECT_TRUE(a.search(4));
    EXPECT_TRUE(a.search(5));
    EXPECT_TRUE(a.search(6));
    EXPECT_TRUE(a.search(7));
    EXPECT_TRUE(a.search(8));
    a.remove(4);
    EXPECT_FALSE(a.search(4));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(5,2,1,3,7,6,8));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(1,2,3,5,6,7,8));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(1,3,2,6,8,7,5));
}

// up to this point, upin and upout have been tested excessively and completely
// since the other two kinds of remove are also based on upout, a small sample
// of test will be sufficient for them

TEST(AVLTreeTest, RemoveRootOneLeaf) {
    AVLTree a;
    a.insert(5);
    a.insert(6);
    EXPECT_TRUE(a.search(5));
    EXPECT_TRUE(a.search(6));
    a.remove(5);
    EXPECT_FALSE(a.search(5));
    EXPECT_TRUE(a.search(6));
    a.insert(5);
    a.remove(6);
    EXPECT_FALSE(a.search(6));
    EXPECT_TRUE(a.search(5));

    EXPECT_THAT(*a.preorder(), testing::ElementsAre(5));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(5));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(5));
}

TEST(AVLTreeTest, RemoveOneLeafRoation) {
    AVLTree a;
    a.insert(11);
    a.insert(8);
    a.insert(15);
    a.insert(4);
    a.insert(10);
    a.insert(13);
    a.insert(16);
    a.insert(2);
    a.insert(6);
    a.insert(9);
    a.insert(12);
    a.insert(14);
    a.insert(17);
    a.insert(18);
    a.insert(1);
    a.insert(3);
    a.insert(5);
    a.insert(7);
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
    EXPECT_TRUE(a.search(11));
    EXPECT_TRUE(a.search(12));
    EXPECT_TRUE(a.search(13));
    EXPECT_TRUE(a.search(14));
    EXPECT_TRUE(a.search(15));
    EXPECT_TRUE(a.search(17));
    EXPECT_TRUE(a.search(16));
    EXPECT_TRUE(a.search(18));
    a.remove(10);
    EXPECT_FALSE(a.search(10));
    std::vector<int> v({11,4,2,1,3,8,6,5,7,9,15,13,12,14,17,16,18});
    EXPECT_EQ(*a.preorder(), v);
    std::vector<int> w({1,2,3,4,5,6,7,8,9,11,12,13,14,15,16,17,18});
    EXPECT_THAT(*a.inorder(), w);
    std::vector<int> x({1,3,2,5,7,6,9,8,4,12,14,13,16,18,17,15,11});
    EXPECT_THAT(*a.postorder(), x);
}

TEST(AVLTreeTest, RemoveRootNoLeaves) {
    AVLTree a;
    a.insert(5);
    a.insert(6);
    a.insert(4);

    EXPECT_TRUE(a.search(4));
    EXPECT_TRUE(a.search(5));
    EXPECT_TRUE(a.search(6));
    a.remove(5);
    EXPECT_TRUE(a.search(4));
    EXPECT_FALSE(a.search(5));
    EXPECT_TRUE(a.search(6));

    EXPECT_THAT(*a.preorder(), testing::ElementsAre(6,4));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(4,6));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(4,6));
}

TEST(AVLTreeTest, RemoveNodeNoLeaves) {
    AVLTree a;
    a.insert(5);
    a.insert(2);
    a.insert(7);
    a.insert(1);
    a.insert(4);
    a.insert(6);
    a.insert(10);
    a.insert(3);
    a.insert(8);
    a.insert(11);
    EXPECT_TRUE(a.search(1));
    EXPECT_TRUE(a.search(2));
    EXPECT_TRUE(a.search(3));
    EXPECT_TRUE(a.search(4));
    EXPECT_TRUE(a.search(5));
    EXPECT_TRUE(a.search(6));
    EXPECT_TRUE(a.search(7));
    EXPECT_TRUE(a.search(8));
    EXPECT_TRUE(a.search(10));
    EXPECT_TRUE(a.search(11));
    a.remove(7);
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(5,2,1,4,3,8,6,10,11));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(1,2,3,4,5,6,8,10,11));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(1,3,4,2,6,11,10,8,5));
}

TEST(AVLTreeTest, RemoveNodeNoLeavesDoubleRotation) {
    AVLTree a;

    a.insert(3);
    a.insert(1);
    a.insert(6);
    a.insert(0);
    a.insert(2);
    a.insert(4);
    a.insert(9);
    a.insert(-1);
    a.insert(5);
    a.insert(7);
    a.insert(10);
    a.insert(8);
    EXPECT_TRUE(a.search(-1));
    EXPECT_TRUE(a.search(0));
    EXPECT_TRUE(a.search(1));
    EXPECT_TRUE(a.search(2));
    EXPECT_TRUE(a.search(3));
    EXPECT_TRUE(a.search(4));
    EXPECT_TRUE(a.search(5));
    EXPECT_TRUE(a.search(6));
    EXPECT_TRUE(a.search(7));
    EXPECT_TRUE(a.search(8));
    EXPECT_TRUE(a.search(10));
    a.remove(3);
    EXPECT_FALSE(a.search(3));
    std::vector<int> v({4,1,0,-1,2,7,6,5,9,8,10});
    EXPECT_EQ(*a.preorder(), v);
    std::vector<int> w({-1,0,1,2,4,5,6,7,8,9,10});
    EXPECT_THAT(*a.inorder(), w);
    std::vector<int> x({-1,0,2,1,5,6,8,10,9,7,4});
    EXPECT_THAT(*a.postorder(), x);
}