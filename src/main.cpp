#include <iostream>
#include <ctime>
#include <set>
#include <vector>
#include <chrono>
#include <algorithm>
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
        // cout<<"insert"<<endl;
        avltree.insert(randNums.at(i));
        if (i % 10 == 7) { 
            // cout<<"removing "<<"("<<i<<","<<randNums.at(i)<<")"<<endl;
            if(i==17){
                // avltree.printBT();
            }
            // cout<<"remove "<<i<<"="<<randNums.at(i-3)<<" seen: "<<(avltree.find(randNums.at(i-3))!=nullptr)<<endl;
            avltree.remove(randNums.at(i-3)); }
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

vector<int> getUniques(vector<int> vec)
{
    vector<int> uniques;
    for (int num : vec)
    {
        if (std::find(uniques.begin(), uniques.end(), num) == uniques.end()) {
            uniques.push_back(num);
        }
    }

    return uniques;
}


void printTest(void (*tester)(SearchTree*, vector<int>), int n, string testname, bool ordered){
    // Generate numbers
    cout<<testname<<endl;
    vector<int> nums;
    for(int i = 0; i<n; i++){
        nums.push_back(ordered ? i : rand());
    }
    set<int> unique_nums(nums.begin(),nums.end());
    nums.assign(unique_nums.begin(),unique_nums.end());
    SearchTree* bst = new BST();
    SearchTree* avl = new AVLTree();
    // Run tester function, while timing.
    auto BSTstart = high_resolution_clock::now();
    tester(bst,nums);
    auto BSTstop = high_resolution_clock::now();
    auto BSTduration = duration_cast<microseconds>(BSTstop - BSTstart);
    cout << "BST took " << (float)BSTduration.count() / 1000.00 << " ms" << endl;

    auto AVLstart = high_resolution_clock::now();
    tester(avl,nums);
    auto AVLstop = high_resolution_clock::now();
    auto AVLduration = duration_cast<microseconds>(AVLstop - AVLstart);
    cout << "AVL took " << (float)AVLduration.count() / 1000.00 << " ms" << endl;
    // Print results
    cout << "The AVL tree was " << (float)BSTduration.count() / (float)AVLduration.count() << " times faster than the BST." << endl << endl;
}

void InsertTest(SearchTree* tree, vector<int> nums){
    for(auto num : nums){
        tree->insert(num);
    }
}
void DeleteTest(SearchTree* tree, vector<int> nums){
    int i = 0;
    for(auto num : nums){
        tree->insert(num);
        if(i%10==7){
            tree->remove(nums.at(i-3));
        }
        i++;
    }
}
void FindTest(SearchTree* tree, vector<int> nums){
    int i = 0;
    for(auto num : nums){
        tree->insert(num);
        if(i%10==7){
            tree->find(nums.at(i-3));
        }
        i++;
    }
}
void FindDeleteTest(SearchTree* tree, vector<int> nums){
    int i = 0;
    for(auto num : nums){
        tree->insert(num);
        if(i%10==7){
            tree->find(nums.at(i-3));
        }
        if(i%13==7){
            tree->find(nums.at(i-4));
        }
        i++;
    }
}

int main(int argc, char* argv[]){
    srand(time(0));//1670036600
    // cout<<"seed "<<seed<<endl;

    printTest(InsertTest,5000,"Insert 5000 items (random):",false);
    printTest(InsertTest,5000,"Insert 5000 items (ordered):",true);
    printTest(FindTest,5000,"Insert 5000 items then find (random):",false);
    printTest(FindTest,5000,"Insert 5000 items then find (ordered):",true);
    printTest(DeleteTest,5000,"Insert 5000 items then delete (random):",false);
    printTest(DeleteTest,5000,"Insert 5000 items then delete (ordered):",true);
    printTest(FindDeleteTest,5000,"Insert 5000 items then delete (random):",false);
    printTest(FindDeleteTest,5000,"Insert 5000 items then delete (ordered):",true);
    
    printTest(InsertTest,10000,"Insert 10000 items (random):",false);
    printTest(InsertTest,10000,"Insert 10000 items (ordered):",true);
    printTest(FindTest,10000,"Insert 10000 items then find (random):",false);
    printTest(FindTest,10000,"Insert 10000 items then find (ordered):",true);
    printTest(DeleteTest,10000,"Insert 10000 items then delete (random):",false);
    printTest(DeleteTest,10000,"Insert 10000 items then delete (ordered):",true);
    printTest(FindDeleteTest,10000,"Insert 10000 items then delete (random):",false);
    printTest(FindDeleteTest,10000,"Insert 10000 items then delete (ordered):",true);
    
    printTest(InsertTest,20000,"Insert 20000 items (random):",false);
    printTest(InsertTest,20000,"Insert 20000 items (ordered):",true);
    printTest(FindTest,20000,"Insert 20000 items then find (random):",false);
    printTest(FindTest,20000,"Insert 20000 items then find (ordered):",true);
    printTest(DeleteTest,20000,"Insert 20000 items then delete (random):",false);
    printTest(DeleteTest,20000,"Insert 20000 items then delete (ordered):",true);
    printTest(FindDeleteTest,20000,"Insert 20000 items then delete (random):",false);
    printTest(FindDeleteTest,20000,"Insert 20000 items then delete (ordered):",true);
    
    printTest(InsertTest,50000,"Insert 50000 items (random):",false);
    printTest(InsertTest,50000,"Insert 50000 items (ordered):",true);
    printTest(FindTest,50000,"Insert 50000 items then find (random):",false);
    printTest(FindTest,50000,"Insert 50000 items then find (ordered):",true);
    printTest(DeleteTest,50000,"Insert 50000 items then delete (random):",false);
    printTest(DeleteTest,50000,"Insert 50000 items then delete (ordered):",true);
    printTest(FindDeleteTest,50000,"Insert 50000 items then delete (random):",false);
    printTest(FindDeleteTest,50000,"Insert 50000 items then delete (ordered):",true);
    

    

    return 0;
}