#ifndef ARRAYLIST_TESTLIST_H
#define ARRAYLIST_TESTLIST_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "avlTree/avlTree.h"

bool compareVectors(std::vector<int>* v1, std::vector<int>* v2){
    bool solution = true;
    if(v1->size() != v2->size()) return false;
    for(unsigned int i = 0; i < v1->size(); i++){
        if(v1->at(i) != v2->at(i)){
            solution = false;
            break;
        }
    }
    return solution;
}


class avlTreeTest : public ::testing::Test {
};

#endif //AVLTREE_AVLTREE_H
