#ifndef AVLTREE_H
#define AVLTREE_H

using namespace std;
#include <string>
#include <iostream>
#include "SearchTree.h"

class AVLTree : SearchTree{
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
            int c = 0;
            if(node!=nullptr){
                auto hl = getHeight(node->left);
                auto hr = getHeight(node->right);
                c = max(hl,hr)+1;
            }
            return c;
        }

        int getBF(Node* node){
            if(node==nullptr) return 0;
            return getHeight(node->left)-getHeight(node->right);
        }
        void leftRotate(Node* node){
            auto x = node;
            auto a = node->left;
            auto y = x->right;
            auto b = y->left;
            auto Y = y->right;
            auto p = node->parent;
            
            y->left = nullptr;
            x->right = b;
            y->parent = nullptr;
            if(b!=nullptr){
                b->parent = x;
            }


            if(p==nullptr) {
                root = y;
                y->parent = nullptr;
            }
            else if(x==p->right) {
                p->right = y;
                y->parent = nullptr;
                y->parent = p;
            }
            else {
                p->left = y;
                x->parent = nullptr;
                y->parent = p;
            }

            y->left = x;
            x->parent = y;
        }

        void rightRotate(Node* node){
            auto y = node;
            auto a = node->right;
            auto x = y->left;
            auto b = x->right;
            auto Y = x->left;
            auto p = node->parent;
            
            x->right = nullptr;
            y->left = b;
            x->parent = nullptr;
            if(b!=nullptr){
                b->parent = y;
            }


            if(p==nullptr) {
                root = x;
                x->parent = nullptr;
            }
            else if(y==p->right) {
                p->right = x;
                y->parent = nullptr;
                x->parent = p;
            }
            else {
                p->left = x;
                y->parent = nullptr;
                x->parent = p;
            }

            x->right = y;
            y->parent = x;
        }
    public:
        AVLTree(){
            root = nullptr;
        }
        ~AVLTree(){
			destroyRecursive(root);
		}

        void insert(int data){
            if(root==nullptr){
                root = new Node(data);
                return;
            }
            auto p = root;
            for(;;){
                if(data<p->key){
                    // Move down left
                    if(p->left!=nullptr){
                        p = p->left;
                    }else{
                        break;
                    }
                }else{
                    // Move down right
                    if(p->right!=nullptr){
                        p = p->right;
                    }else{
                        break;
                    }
                }
            }
            if(data<p->key){
                // Insert left
                p->left = new Node(data);
                p->left->parent = p;
                
            }else{
                // Insert right
                p->right = new Node(data);
                p->right->parent = p;
            }

            p=p->parent;
            int bf = getBF(p);
            if(bf>1){
                if(data<p->left->key){
                    rightRotate(p);
                }else{
                    leftRotate(p->left);
                    rightRotate(p);
                }
            }else if(bf < -1){
                if(data>p->right->key){
                    leftRotate(p);
                }else{
                    rightRotate(p->right);
                    leftRotate(p);
                }
            }
            

        }
        Node* find(int key){
            auto p = root;
            while(p!=nullptr && p->key!=key){
                if(key<p->key){
                    p = p->left;
                }else{
                    p = p->right;
                }
            }
            return p;
        }

        void remove(int key){
            auto node = find(key);
            remove(node);
        }
        void remove(Node* node){
            
            auto p = node->parent;
            
            auto isLeft = p ? node==p->left : 0;
            if(node->left==nullptr && node->right==nullptr){ // No children
                if(p==nullptr){
                    root=nullptr;
                    return;
                }
                if(isLeft) p->left = nullptr;
                else p->right = nullptr;
            }else{
                if(node->left!=nullptr && node->right!=nullptr){ // Two children
                    auto succ = node->getSuccessor();
                    node->key = succ->key;
                    remove(succ);
                    if(p==nullptr) return;
                    
                }else{ // One child
                    auto child = node->left==nullptr ? node->right : node->left;
                    if(p==nullptr){
                        root = child;
                        child->parent = nullptr;
                        return;
                    }
                    if(node==p->right) p->right = child;
                    if(node==p->left) p->left = child;
                    child->parent = p;
                }
            }
            

            node = isLeft ? p->left : p->right;


            
            auto bf = getBF(node);
            
            if(bf>1){
                if(getBF(node->left)>=0){
                    rightRotate(node);
                }else{
                    leftRotate(node->left);
                    rightRotate(node);
                }
            }else if(bf<-1){
                if(getBF(node->right)<=0){
                    leftRotate(node);
                }else{
                    rightRotate(node->right);
                    leftRotate(node);
                }
            }



        }

        void printBT(const std::string& prefix, Node* node, bool isLeft)
        {
            if( node != nullptr )
            {
                std::cout << prefix;

                std::cout << (isLeft ? "├──" : "└──" );

                // print the value of the node
                std::cout << node->key << std::endl;
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