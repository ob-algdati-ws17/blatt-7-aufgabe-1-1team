#include "testAvlTree.h"
#include <memory>
#include <vector>

using namespace std;

// empty list
TEST (testAvlTree, Empty_Tree) {
    avlTree tree;
    EXPECT_EQ(nullptr, tree.sortTree());
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
    EXPECT_TRUE(compareVectors(vector1, tree.sortTree()));
}

TEST(testAvlTree, InsertTwiceSameValue) {
    avlTree tree;
    tree.insert(3);
    tree.insert(3);
    auto vector1 = new vector <int> {3};
    EXPECT_TRUE(compareVectors(vector1, tree.sortTree()));
}

TEST(testAvlTree, InsertOneCaseOneAndTwo) {
    avlTree tree;
    tree.insert(5);
    tree.insert(6);
    //Einfügen Rechts Fall 2
    auto vector1 = new vector <int>{5,6};
    EXPECT_TRUE(compareVectors(vector1, tree.sortTree()));
    // Einfügen Links Fall 1
    tree.insert(4);
    auto vector2 = new vector <int>{4,5,6};
    EXPECT_TRUE(compareVectors(tree.sortTree(),vector2));
    // Einfügen Links Fall 2
    auto vector3 = new vector <int> {3,4,5,6};
    tree.insert(3);
    EXPECT_TRUE(compareVectors(tree.sortTree(),vector3));
    //Einfügen rechts Fall 1
    vector3->push_back(7);
    tree.insert(7);
    EXPECT_TRUE(compareVectors(tree.sortTree(),vector3));
}

TEST(testAvlTree, RotateRight_RotateLeft) {
    avlTree tree;
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    auto vector1 = new vector <int> {3,4,5};
    EXPECT_TRUE(compareVectors(vector1, tree.sortTree()));
    avlTree tree2;
    tree2.insert(3);
    tree2.insert(4);
    tree2.insert(5);
    auto vector2 = new vector <int> {3,4,5};
    EXPECT_TRUE(compareVectors(vector2, tree.sortTree()));
}

TEST(testAvlTree, RotateLeftRight_RightLeft) {
    avlTree tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(4);
    auto vector1 = new vector <int> {3,4,5};
    EXPECT_TRUE(compareVectors(vector1, tree.sortTree()));
    avlTree tree2;
    tree2.insert(5);
    tree2.insert(7);
    tree2.insert(6);
    auto vector2 = new vector <int> {5,6,7};
    EXPECT_TRUE(compareVectors(vector2, tree2.sortTree()));
}

TEST(testAvlTree, RotateAll) {
    avlTree tree;
    tree.insert(5);
    tree.insert(6);
    tree.insert(13);
    tree.insert(12);
    tree.insert(11);
    tree.insert(10);
    auto vector1 = new vector<int>{5,6,10,11,12,13};
    EXPECT_TRUE(compareVectors(vector1, tree.sortTree()));
}

TEST(testAvlTree, RemoveOneCaseTwo) {
    avlTree tree;
    tree.insert(3);
    tree.insert(4);
    tree.remove(4);
    EXPECT_FALSE(tree.search(4));
    EXPECT_TRUE(compareVectors(tree.sortTree(),new vector <int>{3}));
}

TEST(testAvlTree, RemoveOneCaseOne) {
    avlTree tree;
    tree.insert(5);
    tree.insert(4);
    tree.insert(6);
    tree.remove(4);
    EXPECT_FALSE(tree.search(4));
    auto vector2 = new vector <int> {5,6};
    EXPECT_TRUE(compareVectors(vector2, tree.sortTree()));
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
    tree.insert(5);
    tree.insert(4);
    tree.remove(5);
    EXPECT_FALSE(tree.search(5));
    auto vector1 = new vector <int> {3,4};
    EXPECT_TRUE(compareVectors(vector1, tree.sortTree()));
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
    EXPECT_TRUE(compareVectors(vector1, tree.sortTree()));
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
    EXPECT_TRUE(compareVectors(vector1, tree.sortTree()));
}