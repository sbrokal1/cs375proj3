#include <iostream>
#include <ctime>
#include <set>
#include <vector>
#include <chrono>
#include "BST.h"
#include "AVLTree.h"

using namespace std::chrono;

void insertsOnly(vector<int> randNums) {
    BST bst;
    AVLTree avltree;
    auto BSTstart = high_resolution_clock::now();
    for (int i = 0; i < randNums.size(); i++) {
        bst.insert(randNums.at(i));
    }
    auto BSTstop = high_resolution_clock::now();
    auto BSTduration = duration_cast<microseconds>(BSTstop - BSTstart);
    cout << "BST took " << (float)BSTduration.count() / 1000.00 << " ms" << endl;

    auto AVLstart = high_resolution_clock::now();
    for (int i = 0; i < randNums.size(); i++) {
        avltree.insert(randNums.at(i));
    }
    auto AVLstop = high_resolution_clock::now();
    auto AVLduration = duration_cast<microseconds>(AVLstop - AVLstart);
    cout << "AVL Tree took " << (float)AVLduration.count() / 1000.00 << " ms" << endl;
    cout << "The AVL tree was " << (float)BSTduration.count() / (float)AVLduration.count() << " times faster than the BST for just inserts." << endl << endl;
}

void insertsAndFinds(vector<int> randNums) {
    BST bst;
    AVLTree avltree;
    auto BSTstart = high_resolution_clock::now();
    for (int i = 0; i < randNums.size(); i++) {
        bst.insert(randNums.at(i));
        if (i % 10 == 7) { bst.find(randNums.at(i-3)); }
    }
    auto BSTstop = high_resolution_clock::now();
    auto BSTduration = duration_cast<microseconds>(BSTstop - BSTstart);
    cout << "BST took " << (float)BSTduration.count() / 1000.00 << " ms" << endl;

    auto AVLstart = high_resolution_clock::now();
    for (int i = 0; i < randNums.size(); i++) {
        avltree.insert(randNums.at(i));
        if (i % 10 == 7) { avltree.find(randNums.at(i-3)); }
    }
    auto AVLstop = high_resolution_clock::now();
    auto AVLduration = duration_cast<microseconds>(AVLstop - AVLstart);
    cout << "AVL took " << (float)AVLduration.count() / 1000.00 << " ms" << endl;
    cout << "The AVL tree was " << (float)BSTduration.count() / (float)AVLduration.count() << " times faster than the BST for inserts and finds." << endl << endl;
}

void insertsAndRemoves(vector<int> randNums) {
    BST bst;
    AVLTree avltree;
    auto BSTstart = high_resolution_clock::now();
    for (int i = 0; i < randNums.size(); i++) {
        bst.insert(randNums.at(i));
        if (i % 10 == 7) { bst.remove(randNums.at(i-3)); }
    }
    auto BSTstop = high_resolution_clock::now();
    auto BSTduration = duration_cast<microseconds>(BSTstop - BSTstart);
    cout << "BST took " << (float)BSTduration.count() / 1000.00 << " ms" << endl;

    auto AVLstart = high_resolution_clock::now();
    for (int i = 0; i < randNums.size(); i++) {
        avltree.insert(randNums.at(i));
        if (i % 10 == 7) { avltree.remove(randNums.at(i-3)); }
    }
    auto AVLstop = high_resolution_clock::now();
    auto AVLduration = duration_cast<microseconds>(AVLstop - AVLstart);
    cout << "AVL took " << (float)AVLduration.count() / 1000.00 << " ms" << endl;
    cout << "The AVL tree was " << (float)BSTduration.count() / (float)AVLduration.count() << " times faster than the BST for inserts and removes." << endl << endl;
}

void insertsFindsAndRemoves(vector<int> randNums) {
    BST bst;
    AVLTree avltree;
    auto BSTstart = high_resolution_clock::now();
    for (int i = 0; i < randNums.size(); i++) {
        bst.insert(randNums.at(i));
        if (i % 9 == 4) { bst.find(randNums.at(i-3)); }
        if (i % 9 == 7) { bst.remove(randNums.at(i-5)); }
    }
    auto BSTstop = high_resolution_clock::now();
    auto BSTduration = duration_cast<microseconds>(BSTstop - BSTstart);
    cout << "BST took " << (float)BSTduration.count() / 1000.00 << " ms" << endl;

    auto AVLstart = high_resolution_clock::now();
    for (int i = 0; i < randNums.size(); i++) {
        avltree.insert(randNums.at(i));
        if (i % 9 == 4) { avltree.find(randNums.at(i-3)); }
        if (i % 9 == 7) { avltree.remove(randNums.at(i-5)); }
    }
    auto AVLstop = high_resolution_clock::now();
    auto AVLduration = duration_cast<microseconds>(AVLstop - AVLstart);
    cout << "AVL took " << (float)AVLduration.count() / 1000.00 << " ms" << endl;
    cout << "The AVL tree was " << (float)BSTduration.count() / (float)AVLduration.count() << " times faster than the BST for inserts, finds, and removes." << endl << endl;
}

int main(int argc, char* argv[]){
    srand(time(0));
    set<int> randNumsSet;
    vector<int> randNums;
    vector<int> inOrder;
    BST bst;
    AVLTree avltree;
    int numberOfRandoms = 20000;

    for (auto i = 0; i < numberOfRandoms; i++) {
        randNumsSet.insert((rand() % 1000000) + 1);
        inOrder.push_back(i);
    }
    std::copy(randNumsSet.begin(), randNumsSet.end(), std::back_inserter(randNums));

    
    insertsOnly(randNums);
    insertsAndFinds(randNums);
    insertsAndRemoves(randNums);
    insertsFindsAndRemoves(randNums);
    
    /*
    insertsOnly(inOrder);
    insertsAndFinds(inOrder);
    insertsAndRemoves(inOrder);
    insertsFindsAndRemoves(inOrder);
    */

    return 0;
}