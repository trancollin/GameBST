/* Collin Tran
 * ctt200001
 */
#ifndef BINTREE_H
#define BINTREE_H

#include <string>
#include <iostream>
#include <vector>

#include "Node.h"

//the class is templated for the use of templated nodes
template<typename T>
class BinTree {
    public:
        //default constructor
        BinTree() {
            root = nullptr;
        }
        //overloaded constructor: sets root to a specified node
        BinTree(Node<T>* r) {
            root = r;
        }
        //helper function for insert
        void insert(Node<T>* n);
        //inserts node in BST
        void insert(Node<T>* n, Node<T>* cur, Node<T>* par);
        //searches for specified term in BST
        std::vector<Node<T>*> search(std::string term);
        void findTerm(std::string term, Node<T>* cur, std::vector<Node<T>*> &v);
        //deletes a specified node from the BST
        Node<T>* deleteNode(std::string term, Node<T>* cur, Node<T>* par);
        Node<T>* deleteSucNode(Node<T>* n, Node<T>* cur, Node<T>* par);
        //finds the leftmost node of the right subtree
        Node<T>* findSuccessor(Node<T>* suc);
        //class variables
        Node<T>* root;
};

/* The function deletes the successor node from the BST
 * The logic is the same as deleteNode, but modified for the use of a node instead of a term
 * The condition for the node having two children has also been removed, since the sucessor node can't have two children
 */
template<typename T>
Node<T>* BinTree<T>::deleteSucNode(Node<T>* n, Node<T>* cur, Node<T>* par){
    //if cur is null return null
    if(cur == nullptr){
        return nullptr;
    }
    //if cur matches n
    else if((*cur).equal(*n)){
        //if current is a leaf node
        if(cur->left == nullptr && cur->right == nullptr){
            //if the node to be removed is root, set root to null
            if(par == nullptr){
                root = nullptr;
            }
            //if cur is the left child of par, set par->left to null
            else if(par->left == cur){
                par->left = nullptr;
            }
            //if cur is the right child of par, set par->right to null
            else{
                par->right = nullptr;
            }
        }
        //if current has only one left child
        else if(cur->right == nullptr){
            //if cur is the root, promote cur's left child
            if(par == nullptr){
                root = cur->left;
            }
            //if cur is the left child, promote cur's left child
            else if(par->left == cur){
                par->left = cur->left;
            }
            //if cur is the right child, promote cur's left child
            else{
                par->right = cur->left;
            }
        }
        //if current has only one right child
        else if(cur->left == nullptr){
            //if cur is the root, promote cur's right child
            if(par == nullptr){
                root = cur->right;
            }
            //if cur is the left child, promote cur's right child
            else if(par->left == cur){
                par->left = cur->right;
            }
            //if cur is the right child, promote cur's right child
            else {
                par->right = cur->right;
            }
        }
        //return cur
        return cur;
    }
    //if a match isn't found, and cur isn't null
    else if(cur != nullptr){
        //if n is to the left of cur, traverse left
        if(*cur > *n){
            return deleteSucNode(n, cur->left, cur);
        }  
        //otherwise, traverse right
        else {
            return deleteSucNode(n, cur->right, cur);
        }
    }
    //if no match is found, return null
    else {
        return nullptr;
    }
}

/* The function finds the successor node when a node with two children is being removed
 * The successor node is the leftmost node of the right subtree of the node being removed
 * The function traverses left until it reaches the bottom of the BST
 * Suc is then returned
 */
template<typename T>
Node<T>* BinTree<T>::findSuccessor(Node<T>* suc){
    //when the successor node is reached, return suc
    if(suc->left == nullptr){
        return suc;
    }
    //if the successor hasn't been reached, traverse left
    else {
        return findSuccessor(suc->left);
    }
}

/* The function removes a node with a specified name from the BST
 * The function executes different commands depending on if a node has 0, 1, or 2 children
 * The node that has been removed is returned at the end of the function
 */
template<typename T>
Node<T>* BinTree<T>::deleteNode(std::string term, Node<T>* cur, Node<T>* par){
    //if root is null return null
    if(cur == nullptr){
        return nullptr;
    }
    //if a match is found
    else if(*cur == term){
        //if current is a leaf node
        if(cur->left == nullptr && cur->right == nullptr){
            //if the node to be removed is root, set root to null
            if(par == nullptr){
                root = nullptr;
            }
            //if cur is the left child of par, set par->left to null
            else if(par->left == cur){
                par->left = nullptr;
            }
            //if cur is the right child of par, set par->right to null
            else{
                par->right = nullptr;
            }
        }
        //if current has only one left child
        else if(cur->right == nullptr){
            //if cur is the root
            if(par == nullptr){
                root = cur->left;
            }
            //if cur is the left child, promote cur's left child
            else if(par->left == cur){
                par->left = cur->left;
            }
            //if cur is the right child, promote cur's left child
            else{
                par->right = cur->left;
            }
        }
        //if current has only one right child
        else if(cur->left == nullptr){
            //if cur is the root, set the root to null
            if(par == nullptr){
                root = cur->right;
            }
            //if cur is the left child, promote cur's right child
            else if(par->left == cur){
                par->left = cur->right;
            }
            //if cur is the right child, promote cur's right child
            else {
                par->right = cur->right;
            }
        }
        //if current has two children
        else{
            //create a place holder node and copy cur's data to it
            Node<T>* hold = new Node<T>;
            hold->payload = cur->payload;
            //find the successor node of the one being removed
            Node<T>* suc = findSuccessor(cur->right);
            T p = suc->payload;
            //delete the successor node from the BST
            deleteSucNode(suc, cur->right, cur);
            delete suc;
            //replace cur's data with the successor's data
            cur->payload = p;
            //return the placeholder node
            return hold;
        }
        //return cur
        return cur;
    }
    //if a match isn't found, and cur isn't null
    else if(cur != nullptr){
        //if the term is to the left of cur, traverse left
        if(*cur > term){
            return deleteNode(term, cur->left, cur);
        }
        //if the term is to the right of cur, traverse right
        else {
            return deleteNode(term, cur->right, cur);
        }
    }
    //if a match isn't found and cur is null, return null
    else {
        return nullptr;
    }
}

/* The function searches for a term within the BST 
 * The function traverses the BST recursively
 * The function does a inorder traversal in order to find the nodes
 * If a node matches the search term, it is pushed to the vector
 */
template<typename T>
void BinTree<T>::findTerm(std::string term, Node<T>* cur, std::vector<Node<T>*> &v){
    //if current isn't null
    if(cur){
        //traverse to the left of cur
        findTerm(term, cur->left, v);
        //add cur to the vector if it matches the search term
        if(*cur == term){
            v.push_back(cur);
        }
        //traverse to the right of cur
        findTerm(term, cur->right, v);
    }
}
/* Helper function for searching
 * Passes a vector to findTerm, which is then filled
 * Returns the vector 
 */
template<typename T>
std::vector<Node<T>*> BinTree<T>::search(std::string term){
    std::vector<Node<T>*> v;
    findTerm(term, root, v);
    return v;
}


/* The function adds a new node to the BST
 * The function traverses through the BST recursively
 * If the BST's root is null, root is set to n
 * Base case: if cur is null, if n's payload is less than par's, par->left is set to n
 *      Otherwise, par->right is set to n
 * Recursive case: if n's payload is less than cur's, call insert(n, cur->left, cur)
 *      Otherwise, call insert(n, cur->right, cur)
 */
template<typename T>
void BinTree<T>::insert(Node<T>* n, Node<T>* cur, Node<T>* par){
    if(root == nullptr) {
        root = n;
    }
    else if(cur == nullptr){
        if(*n < *par){
            par->left = n;
        }
        else {
            par->right = n;
        }
    }
    else {
        if(*n < *cur) {
            insert(n, cur->left, cur);
        }
        else {
            insert(n, cur->right, cur);
        }
    }
}

/* Helper function that is called in main for inserting a new node
 * Calls insert with the argument node
 * Node* cur is initially the root of the BST
 * Node* par is initally null
 */
template<typename T>
void BinTree<T>::insert(Node<T>* n){
    insert(n, root, nullptr);
}

#endif