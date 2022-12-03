#ifndef AVLTREE_H
#define AVLTREE_H

using namespace std;
#include <string>
#include <iostream>
#include "SearchTree.h"

class AVLTree : public SearchTree{
    private:
        Node* root;
        void destroyRecursive(Node* node){
			if(node != nullptr){
				if(node->left != nullptr){
					destroyRecursive(node->left);
				}
				if(node->right != nullptr){
					destroyRecursive(node->right);
				}
				delete node;
			}
		}
        
        int getHeight(Node* node){
            if(node!=nullptr) return node->height;
            return -1;
        }

        int getBF(Node* node){
            if(node==nullptr) return 0;
            return getHeight(node->left)-getHeight(node->right);
        }
        Node* leftRotate(Node* t){
            Node* u = t->right;
            t->right = u->left;
            u->left = t;
            t->height = (getBF(t)>0 ? getHeight(t->left) : getHeight(t->right))+1;
            if(getHeight(t->right)>t->height){
                u->height = getHeight(t->right)+1;
            }else{
                u->height = t->height+1;
            }
            return u;
        }

         Node* RLRotate(Node* t)
        {
            t->right = rightRotate(t->right);
            return leftRotate(t);
        }

        Node* LRRotate(Node* t)
        {
            t->left = leftRotate(t->left);
            return rightRotate(t);
        }

        Node* rightRotate(Node* t){
            Node* u = t->left;
            t->left = u->right;
            u->right = t;
            t->height = (getBF(t)>0 ? getHeight(t->left) : getHeight(t->right))+1;
            if(getHeight(u->left)>t->height){
                u->height = getHeight(u->left)+1;
            }else{
                u->height = t->height+1;
            }
            return u;
        }


        Node* insert(int x, Node* t){
            if(t==nullptr){
                t = new Node(x);
            }else if(x<t->key){
                t->left = insert(x,t->left);
                if(getBF(t) == 2)
                {
                    if(x < t->left->key)
                        t = rightRotate(t);
                    else
                        t = LRRotate(t);
                }
            }else if(x>t->key){
                t->right = insert(x,t->right);
                if(-getBF(t) == 2)
                {
                    if(x > t->right->key)
                        t = leftRotate(t);
                    else
                        t = RLRotate(t);
                }
            }
            t->height = (getBF(t)>0 ? getHeight(t->left) : getHeight(t->right))+1;
            return t;
        }

        Node* findMin(Node* t)
    {
        if(t == nullptr)
            return nullptr;
        else if(t->left == nullptr)
            return t;
        else
            return findMin(t->left);
    }

        Node* remove(int x, Node* t)
        {
            Node* temp;
            // Element not found
            if(t == nullptr)
                return nullptr;

            // Searching for element
            else if(x < t->key)
                t->left = remove(x, t->left);
            else if(x > t->key)
                t->right = remove(x, t->right);

            // Element found
            // With 2 children
            else if(t->left && t->right)
            {
                temp = findMin(t->right);
                t->key = temp->key;
                t->right = remove(t->key, t->right);
            }
            // With one or zero child
            else
            {
                temp = t;
                if(t->left == nullptr)
                    t = t->right;
                else if(t->right == nullptr)
                    t = t->left;
                delete temp;
            }
            if(t == nullptr)
                return t;
            
            t->height = (getHeight(t->left)>getHeight(t->right) ? getHeight(t->left) : getHeight(t->right))+1;
            // printBT();
            // cout<<"t: "<<t->key<<endl;
            // If node is unbalanced
            // If left node is deleted, right case
            if(getHeight(t->left) - getHeight(t->right) == 2)
            {
                // right right case
                if(getHeight(t->left->left) - getHeight(t->left->right) == 1){
                   
                    return rightRotate(t);
                }
                // right left case
                else{

                    
                    return LRRotate(t);
                }
            }
            // If right node is deleted, left case
            else if(getHeight(t->right) - getHeight(t->left) == 2)
            {
                // left left case
                if(getHeight(t->right->right) - getHeight(t->right->left) == 1){
                    
                    return leftRotate(t);

                }
                // left right case
                else{
                    
                    return RLRotate(t);
                }
            }
            return t;
        }


        Node* find(int key, Node* t){
            if(t==nullptr) return nullptr;
            if(t->key==key) return t;

            auto lsearch = find(key,t->left);
            auto rsearch = find(key,t->right);
            if(lsearch!=nullptr) return lsearch;
            if(rsearch!=nullptr) return rsearch;
            return nullptr;
        }

    public:
        AVLTree(){
            root = nullptr;
        }
        ~AVLTree(){
			destroyRecursive(root);
		}

        void insert(int data){
            root = insert(data,root);
        }
        

        Node* find(int key){
            Node* currNode = root; 
			while(currNode != nullptr){
				if(key < currNode->key){
					currNode = currNode->left;
				}else if(key > currNode->key){
					currNode = currNode->right;
				}else{ //currNode->key == key
					return currNode;
				}
			}
			return currNode;
        }

        void remove(int key){
            root = remove(key,root);
        }
        
        void printBT(const std::string& prefix, Node* node, bool isLeft)
        {
            if( node != nullptr )
            {
                std::cout << prefix;

                std::cout << (isLeft ? "├──" : "└──" );

                // print the value of the node
                std::cout << node->key<<"::"<<node->height << std::endl;
                // std::cout << getBF(node) << std::endl;

                // enter the next tree level - left and right branch
                printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
                printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
            }
        }

        void printBT()
        {
            printBT("", root, false);    
        }
		
		
};


#endif