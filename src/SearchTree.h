#pragma once
#include <chrono>

using namespace std;

class SearchTree {
    private:
        chrono::_V2::system_clock::time_point start;
    public:
		/* Node class */
		class Node{
			public:
				Node(int data){
					left = nullptr;
					right = nullptr;
					parent = nullptr;
					key = data;
				}
				
				Node* left;		// node left child 
				Node* right;	// right child
				Node* parent;	// parent
				int key;		// key/data

				Node* getSuccessor(){
					Node* currNode = this->right;
					Node* prevNode = nullptr;
					while(currNode != nullptr){
						prevNode = currNode;
						currNode = currNode->left;
					}
					return prevNode;
				}

				Node* getPredecessor(){
					Node* currNode = this->left;
					Node* prevNode = nullptr;
					while(currNode != nullptr){
						prevNode = currNode;
						currNode = currNode->right;
					}
					return prevNode;
				}
		};

        /* Functions that must be implemented in Search Tree implementations */
        void insert(int data);
        Node* find(int key);
        void remove(int key);


        /* Timer functions */
        void startTimer(){
            start = std::chrono::high_resolution_clock::now();
        }
        /**
         * @return The time in microseconds that have elapsed since the timer was started.
        */
        long stopTimer(){
            auto end = std::chrono::high_resolution_clock::now();
            return chrono::duration_cast<chrono::microseconds>(end-start).count();
        }
};