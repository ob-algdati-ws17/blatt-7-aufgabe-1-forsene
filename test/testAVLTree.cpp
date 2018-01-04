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

// insert and search

TEST(AVTree, One_Node) {
    AVLTree b;
    b.insert(12213);
    EXPECT_TRUE(b.search(12213));
    EXPECT_FALSE(b.search(123));
    EXPECT_FALSE(b.search(-123));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(12213));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(12213));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(12213));
}