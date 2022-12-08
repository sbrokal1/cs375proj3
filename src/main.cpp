#include <iostream>
#include <ctime>
#include <set>
#include <vector>
#include <chrono>
#include <algorithm>
#include "BST.h"
#include "AVLTree.h"
#include <map>
#include <fstream>

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

extern void InsertTest(SearchTree* tree, vector<int> nums);

void genGraphFile(void (*tester)(SearchTree*, vector<int>), string output, int (*numGen)(int prevNum), int limit, bool insertFirst = false){
    ofstream file(output);

    vector<int> nums;

    int lastNum = numGen(0);
    nums.push_back(lastNum);

    for(int n = 1; n<limit;){
        
        SearchTree* bst = new BST();
        SearchTree* avl = new AVLTree();

        if(insertFirst){
            InsertTest(bst,nums);
            InsertTest(avl,nums);
        }

        auto BSTstart = high_resolution_clock::now();
        tester(bst,nums);
        auto BSTstop = high_resolution_clock::now();
        auto BSTduration = duration_cast<microseconds>(BSTstop - BSTstart).count();

        auto AVLstart = high_resolution_clock::now();
        tester(avl,nums);
        auto AVLstop = high_resolution_clock::now();
        auto AVLduration = duration_cast<microseconds>(AVLstop - AVLstart).count();

        file<<"BST "<<n<<" "<<BSTduration<<endl;   
        file<<"AVL "<<n<<" "<<AVLduration<<endl;  

        for(int i = 0; i<(limit/100); i++){
            auto thisNum = numGen(lastNum);
            nums.push_back(thisNum);
            lastNum = numGen(thisNum);
            n+=1;
        } 
        if(n>limit){
            for(int i = 0; i<nums.size()-(limit/100); i++){
                if(bst->find(nums.at(i))==nullptr){
                    cout<<"BST BAD"<<endl;
                }
                if(avl->find(nums.at(i))==nullptr){
                    cout<<"AVL BAD"<<endl;
                }
            }
        }
        // ((AVLTree*)(avl))->printBT();
    }

    
    file.close();
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
    int deleteCount = 0;
    map<int,bool> deleted;

    while(deleteCount<nums.size()/4){
        int i = rand()%nums.size();
        if(deleted.find(i)!=deleted.end()) continue;
        tree->remove(i);
        deleted.emplace(i,true);
        deleteCount++;
    }
}
void FindTest(SearchTree* tree, vector<int> nums){
    for(auto num : nums){
        tree->find(num);
    }
}

int randomGen(int prev){
    return rand();
}
int orderedGen(int prev){
    return prev+10;
}

int main(int argc, char* argv[]){
    srand(time(0));
    
    genGraphFile(InsertTest,"insert_ordered.txt",orderedGen,15000);
    genGraphFile(InsertTest,"insert_random.txt",randomGen,1000000);
    genGraphFile(DeleteTest,"delete_random.txt",randomGen,100000, true);
    genGraphFile(DeleteTest,"delete_ordered.txt",orderedGen,20000, true);
    genGraphFile(FindTest,"find_ordered.txt",orderedGen,10000, true);
    genGraphFile(FindTest,"find_random.txt",randomGen,50000, true);

    return 0;
}