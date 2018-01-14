#include "testAvlTree.h"
#include <memory>
#include <vector>

using namespace std;

// empty list
TEST (testAvlTree, Empty_Tree) {
    avlTree tree;
    EXPECT_EQ(nullptr, tree.inorder());
}

TEST (testAvlTree, Insert_Two) {
    avlTree tree;
    tree.insert(7);
    tree.insert(4);
    EXPECT_TRUE(tree.search(7));
    EXPECT_TRUE(tree.search(4));
}

TEST(testAvlTree, InOrder) {
    avlTree tree;
    tree.insert(3);
    tree.insert(2);
    tree.insert(4);
    auto vector1 = new vector<int>{2,3,4};
    EXPECT_TRUE(compareVectors(vector1, tree.inorder()));
}

TEST(testAvlTree, InsertTwiceSameValue) {
    avlTree tree;
    tree.insert(3);
    tree.insert(3);
    auto vector1 = new vector <int> {3};
    EXPECT_TRUE(compareVectors(vector1,tree.inorder()));
}

TEST(testAvlTree, InsertOneCaseOneAndTwo) {
    avlTree tree;
    tree.insert(5);
    tree.insert(6);
    //Einfügen Rechts Fall 2
    auto vector1 = new vector <int>{5,6};
    EXPECT_TRUE(compareVectors(vector1, tree.inorder()));
    // Einfügen Links Fall 1
    tree.insert(4);
    auto vector2 = new vector <int>{4,5,6};
    EXPECT_TRUE(compareVectors(tree.inorder(),vector2));
    // Einfügen Links Fall 2
    auto vector3 = new vector <int> {3,4,5,6};
    tree.insert(3);
    EXPECT_TRUE(compareVectors(tree.inorder(),vector3));
    //Einfügen rechts Fall 1
    vector3->push_back(7);
    tree.insert(7);
    EXPECT_TRUE(compareVectors(tree.inorder(),vector3));
}

TEST(testAvlTree, RotateRight_RotateLeft) {
    avlTree tree;
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    auto vector1 = new vector <int> {3,4,5};
    EXPECT_TRUE(compareVectors(vector1,tree.inorder()));
    avlTree tree2;
    tree2.insert(3);
    tree2.insert(4);
    tree2.insert(5);
    auto vector2 = new vector <int> {3,4,5};
    EXPECT_TRUE(compareVectors(vector2,tree.inorder()));
}

TEST(testAvlTree, RotateLeftRight_RightLeft) {
    avlTree tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(4);
    auto vector1 = new vector <int> {3,4,5};
    EXPECT_TRUE(compareVectors(vector1,tree.inorder()));
    avlTree tree2;
    tree2.insert(5);
    tree2.insert(7);
    tree2.insert(6);
    auto vector2 = new vector <int> {5,6,7};
    EXPECT_TRUE(compareVectors(vector2,tree2.inorder()));
}

TEST(testAvlTree, RemoveOneCaseTwo) {
    avlTree tree;
    tree.insert(3);
    tree.insert(4);
    tree.remove(4);
    EXPECT_FALSE(tree.search(4));
    EXPECT_TRUE(compareVectors(tree.inorder(),new vector <int>{3}));
}

TEST(testAvlTree, RemoveOneCaseOne) {
    avlTree tree;
    tree.insert(5);
    tree.insert(4);
    tree.insert(6);
    tree.remove(4);
    EXPECT_FALSE(tree.search(4));
    auto vector2 = new vector <int> {5,6};
    EXPECT_TRUE(compareVectors(vector2,tree.inorder()));
}

TEST(testAvlTree, RemoveRoot) {
    avlTree tree;
    tree.insert(3);
    tree.remove(3);
    EXPECT_FALSE(tree.search(3));
}

TEST(testAvlTree, RemoveWithNodes) {
    avlTree tree;
    tree.insert(3);
    tree.insert(2);
    tree.insert(4);
    tree.remove(2);
    EXPECT_FALSE(tree.search(2));
    auto vector1 = new vector <int> {3,4};
    EXPECT_TRUE(compareVectors(vector1,tree.inorder()));
}


TEST(testAvlTree, RemoveBothLeaves) {
    avlTree tree;
    tree.insert(3);
    tree.insert(2);
    tree.insert(9);
    tree.insert(4);
    tree.insert(1);
    tree.insert(10);
    tree.remove(4);
    EXPECT_FALSE(tree.search(4));
    auto vector1 = new vector <int> {1,2,3,9,10};
    EXPECT_TRUE(compareVectors(vector1,tree.inorder()));
}

TEST(testAvlTree, RemoveOneLeaf) {
    avlTree tree;
    tree.insert(5);
    tree.insert(4);
    tree.insert(8);
    tree.insert(6);
    tree.insert(1);
    tree.insert(9);
    tree.remove(4);
    EXPECT_FALSE(tree.search(4));
    auto vector1 = new vector<int> {1,5,6,8,9};
    EXPECT_TRUE(compareVectors(vector1,tree.inorder()));
}