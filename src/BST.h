#ifndef BST_H
#define BST_H
#include <iostream>
#include "SearchTree.h"

class BST : SearchTree {
	private:
		Node* root;
		
	public:
		BST(){
			root = nullptr;
		}
		~BST(){
			destroyRecursive(root);
		}
		
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

		void insert(int data){
			Node* newNode = new Node(data);
			if(root == nullptr){
				root = newNode;
			}else{
				Node* currNode = root; 
				Node* parentNode = nullptr;
				while(currNode != nullptr){
					parentNode = currNode;
					if(data < currNode->key){
						currNode = currNode->left;
					}else{
						currNode = currNode->right;
					}
				}
				newNode->parent = parentNode;
				if(data < parentNode->key){
					parentNode->left = newNode;
				}else{
					parentNode->right = newNode;
				}
			}
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
			Node* currNode = find(key);
			if(currNode != nullptr){
				Node* predecessor = currNode->getPredecessor();
				Node* successor = currNode->getSuccessor();
				if(successor != nullptr){
					if(successor != currNode->right){
						//we know successor is a left child
						successor->parent->left = successor->right; //either nullptr or something smaller than parent
						if(successor->right != nullptr){
							successor->right->parent = successor->parent;
						}
						successor->left = currNode->left; //replace subtrees
						if(currNode->left != nullptr){
							currNode->left->parent = successor;
						}
						successor->right = currNode->right; 
						if(currNode->right != nullptr){
							currNode->right->parent = successor;
						}
					}else{
						//successor is the right child of currNode with no left children
						successor->left = currNode->left; //replace left subtree
						if(currNode->left != nullptr){
							currNode->left->parent = successor;
						}
					}

					if(currNode->parent != nullptr){
						if(currNode->parent->left == currNode){
							currNode->parent->left = successor;
						}else{
							currNode->parent->right = successor;
						}
					}else{
						root = successor;
					}
					successor->parent = currNode->parent;
					
				}else if(predecessor != nullptr){
					if(predecessor != currNode->left){
						//we know predecessor is a right child
						predecessor->parent->right = predecessor->left; //either nullptr or something smaller than parent
						if(predecessor->left != nullptr){
							predecessor->left->parent = predecessor->parent;
						}
						predecessor->left = currNode->left; //replace subtrees
						if(currNode->left != nullptr){
							currNode->left->parent = predecessor;
						}
						predecessor->right = currNode->right; 
						if(currNode->right != nullptr){
							currNode->right->parent = predecessor;
						}
					}else{
						//we know predecessor is the left child with no right children
						predecessor->right = currNode->right; //replace right subtree
						if(currNode->right != nullptr){
							currNode->right->parent = predecessor;
						}
					}

					if(currNode->parent != nullptr){
						if(currNode->parent->left == currNode){
							currNode->parent->left = predecessor;
						}else{
							currNode->parent->right = predecessor;
						}
					}else{
						root = predecessor;
					}
					predecessor->parent = currNode->parent;

				}else{
					if(currNode->parent != nullptr){
						if(currNode->parent->left == currNode){
							currNode->parent->left = nullptr;
						}else{
							currNode->parent->right = nullptr;
						}
					}else{
						root = nullptr;
					}
				}
				if(currNode != nullptr){
					delete currNode;
				}
				//delete currNode; 
				//return true;
			}
			//std::cout << "Key does not exist." << std::endl;
			//return false;
		}
};

#endif 