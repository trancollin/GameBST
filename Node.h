/* Collin Tran
 * ctt200001
 */
#ifndef NODE_H
#define NODE_H

#include <string>
#include <iostream>

//the class is templated
template<typename T>
class Node {
    public:
        //default constructor
        Node(){
            left = nullptr;
            right = nullptr;
        }
        //overloaded constructor: sets payload to argument object
        Node(T p){
            left = nullptr;
            right = nullptr;
            payload = p;
        }
        //checks for a match
        bool operator==(std::string term);
        //checks if one node is less than another
        bool operator<(Node<T> n);
        //checks if one node is greater than another
        bool operator>(Node<T> n);
        //checks if a specified term is left of node
        bool operator<(std::string term);
        //checks if a specified term is right of node
        bool operator>(std::string term);
        //checks if this node is exactly the same as a specified node
        bool equal(Node<T> n);
        //prints node information
        friend std::ostream& operator<<(std::ostream &out, const Node<T> &p){
            out << p.payload;
            return out;
        }
        
        //node variables
        Node<T>* left;
        Node<T>* right;
        T payload;
};
//checks if this node is exactly the same as a specified node
template<typename T>
bool Node<T>::equal(Node<T> n){
    if(payload.equal(n.payload)){
        return true;
    }
    else {
        return false;
    }
}

//checks if a specified term is left of node
template<typename T>
bool Node<T>::operator<(std::string term){
    if(payload < term){
        return true;
    }
    else {
        return false;
    }
}
//checks if a specified term is right of node
template<typename T>
bool Node<T>::operator>(std::string term){
    if(payload > term){
        return true;
    }
    else {
        return false;
    }
}

//The function checks for a match for the string within the node
template<typename T>
bool Node<T>::operator==(std::string term){
    if(payload == term){
        return true;
    }
    else {
        return false;
    }
}

/* The function checks to see if a node's payload is less than another's
 * The comparison is actually made in the object's class
 * If this payload is less than p's payload, return true
 * Otherwise, return false
 */
template<typename T>
bool Node<T>::operator<(Node<T> n) {
    //if this payload is less than p's, return true
    if(payload < n.payload) {
        return true;
    }
    //else, return false
    else {
        return false;
    }
}
/* The function checks to see if a node's payload is greater than another's
 * The comparison is actually made in the object's class
 * If this payload is greater than p's payload, return true
 * Otherwise, return false
 */
template<typename T>
bool Node<T>::operator>(Node<T> n) {
    //if this payload is greater than p's, return true
    if(payload > n.payload) {
        return true;
    }
    //else, return false
    else {
        return false;
    }
}

#endif