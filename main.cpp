/* Collin Tran
 * ctt200001
 */
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <queue>

#include "Game.h"
#include "Node.h"
#include "BinTree.h"

using namespace std;

//prototypes
Node<Game>* makeNode(string line);
void printTree(string order, Node<Game>* cur);
void addNode(string command, BinTree<Game> &t);
void sortTree(string command, BinTree<Game> &t);
void writeToFile(ofstream &o, Node<Game>* cur);
void editHelper(string command, BinTree<Game> &t);
Node<Game>* editTree(string name, int fieldnum, string value, Node<Game>* cur);
void prepString(string &s);

//fuction deletes whitespace at the end of a line
void prepString(string &s){
    int i = (int)s.size() - 1;
    while(isspace(s.at(i))){
        s.erase(i);
        i--;
    }
}
/* Helper function for the editTree function
 * If the specified command was to edit a value in the tree, the function takes the command
 *      and parses it into a name, field number, and value
 * The function then defines a node pointer using what is returned from the editTree function call
 * If the node is null, that means the game wasn't found in the BST, and the function prints that the game wasn't found
 * Otherwise, the function prints the name of the game that was updated, what value was updated, and the information of the game
 */
void editHelper(string command, BinTree<Game> &t){
    //parses the command into name, fieldnum, and value
    command.erase(0, command.find('\"') + 1);
    string name = command.substr(0, command.find('\"'));
    command.erase(0, command.find('\"') + 2);
    int fieldnum = stoi(command.substr(0, 1));
    command.erase(0, command.find(' ') + 1);
    string value = command;
    //creates node pointer using editTree function call
    Node<Game>* n = editTree(name, fieldnum, value, t.root);
    //if a match wasn't found, print that the game wasn't found
    if(n == nullptr){
        cout << "Game not found" << endl;
    }
    //if the game was found and edited
    else {
        //print that the game was edited
        cout << name << " UPDATED" << endl;
        //if the highscore was changed, print the new value
        if(fieldnum == 1){
            cout << "UPDATE TO high score - VALUE " << value << endl;
        }
        //if the initials were changed, print the new initials
        else if(fieldnum == 2){
            cout << "UPDATE TO initials - VALUE " << value << endl;
        }
        //if the play count was changed, print the new value
        else if(fieldnum == 3){
            cout << "UPDATE TO plays - VALUE " << value << endl;
        }
        //print the information of the game
        cout << *n << endl;
    }
}

/* The function edits a game in the BST based on the information passed from editHelper
 * The function traverses through the BST recursively
 * If the BST is empty, null is returned
 * Otherwise, the function recurs until either the game is or isn't found
 * If the game is found, the function edits the specified value and return cur
 * Otherwise, if the game is on the left side of cur, traverse to left, vice versa if the game is on the right side of cur
 */
Node<Game>* editTree(string name, int fieldnum, string value, Node<Game>* cur){
    //if the root or cur are null, return null
    if(cur == nullptr){
        return nullptr;
    }
    //if the game was found in the BST
    else if(cur->payload.name == name){
        //changes the highscore
        if(fieldnum == 1){
            cur->payload.highscore = stoi(value);
        }
        //changes the initials
        else if(fieldnum == 2){
            cur->payload.initials = value;
        }
        //changes the play count
        else if(fieldnum == 3){
            cur->payload.plays = stoi(value);
        }
        //return the current node
        return cur;
    }
    //if cur is not the node being searched for 
    else{
        //if the game is on the left of cur, traverse left
        if(name < cur->payload.name){
            return editTree(name, fieldnum, value, cur->left);
        }
        //if the game is on the right of cur, traverse right
        else{
            return editTree(name, fieldnum, value, cur->right);
        }
    }
}

/* The function writes the BST to the datafile
 * The function does a breadth-first traversal with the use of a queue
 * The function first pushes the root of the BST to the queue
 * Until the queue is empty, the node at the front of the queue is written to the file
 *      Then, it is popped from the queue
 *      It's children are then pushed to the queue
 */
void writeToFile(ofstream &o, Node<Game>* cur){
    //create queue and push root 
    queue<Node<Game>*> q;
    if(cur){
        q.push(cur);
        //while the queue isn't empty, write the node at the front to the file
        while(q.empty() == false){
            Node<Game>* n = q.front();
            Game g = q.front()->payload;
            o << g.name << ", ";
            o << g.highscore << ", ";
            o << g.initials << ", ";
            o << g.plays << ", $";
            o << fixed << setprecision(2) << g.plays * 0.25 << endl;
            //pop the node at the front from the queue
            q.pop();
            //push the node's children to the queue, if they exist
            if(n->left != nullptr){
                q.push(n->left);
            }
            if(n->right != nullptr){
                q.push(n->right);
            }
        }
    }
}

/* Helper function for sorting
 * The function first gets the specified order of sorting from the command
 * If the order is ascending, the function displays that the BST will be displayed
 *      in ascending order and calls the printTree function
 * If the order is descending, the function displays that the BST will be displayed 
 *      in descending order and calls the printTree function
 */
void sortTree(string command, BinTree<Game> &t){
    //parsing the specified order
    string order = command.substr(command.find(' ') + 1, 3);
    
    //if the order is ascending, print the tree in ascending order
    if(order == "asc"){
        cout << "RECORDS SORTED ASCENDING" << endl;
        printTree(order, t.root);
    }
    //if the order is descending, print the tree in descending order
    else if(order == "des"){
        cout << "RECORDS SORTED DESCENDING" << endl;
        printTree(order, t.root);
    }
    
}

/* The function adds a node to the BST is specified so by the command file
 * Note that this function is only for adding via command
 * The function creates a node out of the information in the command line
 * The node is then inserted into the tree
 * The function then displays that the record was added
 * The information of the node's game is then displayed
 */
void addNode(string command, BinTree<Game> &t){
    //erases the number and first quotation from the command line
    command.erase(0, command.find(' ') + 2);
    //creates node out of command info
    Node<Game>* n = makeNode(command);
    //inserts node into tree
    t.insert(n);
    //prints information
    cout << "RECORD ADDED" << endl;
    cout << "Name: " << n->payload.name << endl;
    cout << *n << endl;
}

/* The function prints the information of all games in the BST
 * Traversal is done recursively
 * Traversal is done inorder
 * 
 * For ascending:
 * The function traverses the left side of the left subtree, printing the smallest values first
 * It then traverses the right side of the left subtree, printing those values
 * It then traverses the left side of the right subtree, printing those values
 * It then traverses the right side of the right subtree, printing those values
 * 
 * The process is done in reverse for descending order
 * All of a game's attributes are printed on a single line
 * The function prints in ascending or descending order
 * 
 */
void printTree(string order, Node<Game>* cur){
    //the order specified is ascending
    if(order == "asc"){
        //if the current node isn't null
        if(cur){
            //traverse to the left child of the current node
            printTree(order, cur->left);
            //prints the current node's payload info on one line
            cout << cur->payload.name << ", ";
            cout << cur->payload.highscore << ", ";
            cout << cur->payload.initials << ", ";
            cout << cur->payload.plays << ", $";
            cout << fixed << setprecision(2) << cur->payload.plays * 0.25 << endl;
            //traverse to the right child of the current node
            printTree(order, cur->right);
        }
    }
    //the order specified is descending
    else if(order == "des"){
        //the current node isn't null
        if(cur){
            //traverse to the right child of the current node
            printTree(order, cur->right);
            //prints the current node's payload info on one line
            cout << cur->payload.name << ", ";
            cout << cur->payload.highscore << ", ";
            cout << cur->payload.initials << ", ";
            cout << cur->payload.plays << ", $";
            cout << fixed << setprecision(2) << cur->payload.plays * 0.25 << endl;
            //traverse to the left child of the current node
            printTree(order, cur->left);
        }
    }
}


Node<Game>* makeNode(string line) {
    //making nodes out of database file input
    if(line.find('\"') == string::npos){
        //creates name, and deletes name from line
        string name = line.substr(0, line.find(','));
        line.erase(0, line.find(',')+ 2);
        //creates highscore and deletes highscore from line
        int highscore = stoi(line.substr(0, line.find(',')));
        line.erase(0, line.find(',')+ 2);
        //creates initials and deletes initials from line
        string initials = line.substr(0, line.find(','));
        line.erase(0, line.find(',')+ 2);
        //creates plays and deletes plays from line
        int plays = stoi(line.substr(0, line.find(',')));
        //creates game using variables
        Game g(name, highscore, initials, plays);
        //creates templated node and returns it
        Node<Game>* n = new Node<Game>(g);
        return n;
    }
    //making nodes of out command file input
    else {
        //creates name, and deletes name from line
        string name = line.substr(0, line.find('\"'));
        line.erase(0, line.find('\"') + 2);
        //creates highscore and deletes highscore from line
        int highscore = stoi(line.substr(0, line.find(' ')));
        line.erase(0, line.find(' ') + 1);
        //creates initials and deletes initials from line
        string initials = line.substr(0, line.find(' '));
        line.erase(0, line.find(' ') + 1);
        //creates plays and deletes plays from line
        int plays = stoi(line.substr(0, line.find(' ')));
        //creates gmae using variables
        Game g(name, highscore, initials, plays);
        //creates templated node and returns it
        Node<Game>* n = new Node<Game>(g);
        return n;
    }
}

int main()
{
    //variables
    BinTree<Game> tree;
    ifstream inFS;
    ofstream outFS;
    string gameinfo = "";
    string command = "";
    string filename = "";
    
    //opens the database file
    cin >> filename;
    inFS.open(filename);
    //runs if the database file is open
    if(inFS.is_open()){
        //while there are still lines in the database file that aren't whitespace
        while(getline(inFS, gameinfo) && !isspace(gameinfo.at(0))){
            //creates new node and adds it to BST
            prepString(gameinfo);
            Node<Game>* n = makeNode(gameinfo);
            tree.insert(n);
        }
    }
    //closes database file
    inFS.close();
    
    //open data file
    outFS.open("cidercade.dat");
    //opens command file
    cin >> filename;
    inFS.open(filename);
    if(inFS.is_open() && outFS.is_open()){
        //the loop runs until there are no more commands in the file
        //after every command, two blank lines are written to the data file
        while(getline(inFS, command) && !isspace(command.at(0))){
            prepString(command);
            //if the command is to add a game to the BST, add it to the tree
            if(command.substr(0, 1) == "1"){
                addNode(command, tree);
                outFS << '\n' << endl;
            }
            //if the command is search, search the tree for all matches of term
            else if(command.substr(0, 1) == "2"){
                //deletes number from command and fills vector with game's with matching names
                command.erase(0, command.find(' ') + 1);
                vector<Node<Game>*> v = tree.search(command);
                //if there are no games in the vector, print that the name wasn't found
                if((int)v.size() == 0){
                    cout << command << " NOT FOUND\n" << endl;
                    outFS << '\n' << endl;
                }
                //if there are games in the vector, print that the name was found and print the games
                else{
                    for(int i = 0; i < (int)v.size(); i++){
                        cout << v.at(i)->payload.name << " FOUND" << endl;
                        cout << *v.at(i) << endl;
                    }   
                    outFS << '\n' << endl;
                }
            }
            //if the command is edit, edit a value of the specified node
            else if(command.substr(0, 1) == "3"){
                editHelper(command, tree);
                outFS << '\n' << endl;
            }
            //if the command is delete, delete a specified node
            else if(command.substr(0, 1) == "4"){
                command.erase(0, command.find(' ') + 1);
                Node<Game>* n = tree.deleteNode(command, tree.root, nullptr);
                if(n == nullptr){
                    cout << "Match not found" << endl;
                }
                else {
                    cout << "RECORD DELETED" << endl;
                    cout << "Name: " << n->payload.name << endl;
                    cout << *n << endl;
                    outFS << '\n' << endl;
                    delete n;
                }
            }
            //if the command is sort, display the BST in ascending or descending order by name
            else if(command.substr(0, 1) == "5"){
                command.erase(0, command.find(' ') + 1);
                sortTree(command, tree);
                cout << endl;
                outFS << '\n' << endl;
            }
        }
    }
    //close the command file
    inFS.close();
    //write the final database to the file
    writeToFile(outFS, tree.root);
    //close the data file
    outFS.close();
    return 0;
}
