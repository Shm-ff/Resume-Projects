// mymap.h
//
// Mohammed Abdulaziz
//
#pragma once

#include <iostream>
#include <sstream>

using namespace std;

template<typename keyType, typename valueType>
class mymap {
 private:
    struct NODE {
        keyType key;  // used to build BST
        valueType value;  // stored data for the map
        NODE* left;  // links to left child
        NODE* right;  // links to right child
        int nL;  // number of nodes in left subtree
        int nR;  // number of nodes in right subtree
        bool isThreaded;
    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of key/value pairs in the mymap
    //
    //_toStringRecursion:
    //private function to facilitate recursion while updating the string stream object with the node given
    //
    void _toStringRecursion(NODE* node, stringstream &ss) {
        if (node == nullptr) {
            return;
        }
        _toStringRecursion(node->left, ss);
        ss << "key: " << node->key << " value: " << node->value << '\n';
        if (!node->isThreaded) {
            _toStringRecursion(node->right, ss);
        }
    }
    //
    //subtreeLeftMostNode:
    //private function that simply gets the left most node AKA the beginning of whatever node is given to be the root node, which can be any node
    //and it will simply get the left most node of that given node AKA the beginning of the subtree of the node that is given to be the root of the
    // subtree
    //                         ┌───┐
    //                         │   │
    //                    ┌─── │ 7 │ ─────────┐
    //                    │    └───┘          │
    //                    │                   ▼
    //                ┌───▼┐                ┌────┐
    //                │ 3  │                │    │
    //           ┌────┤    ├───┐            │  8 ├──────┐
    //           │    └────┘   │            └────┘      │
    //           ▼             │                        ▼
    //       ┌────┐            │                     ┌──────┐
    //       │    │         ┌──▼─┐                   │   10 │
    //   ┌───┤ 2  │      ┌──┤  5 ├──┐              ┌─┤      ├─┐
    //   │   └────┘      │  └────┘  │              │ └──────┘ │
    //   ▼               ▼          ▼              ▼          │
    //┌───┐            ┌───┐      ┌────┐         ┌───┐     ┌──▼┐
    //│   │            │ 4 │      │    │         │   │     │11 │
    //│ 1 │            │   │      │  6 │         │ 9 │     │   │
    //└───┘            └───┘      └────┘         └───┘     └───┘
    //
    // In this diagram, if I were to input the node 5 then it would return to me 4 because 5 is the root of the subtree and the beginning of this
    // subtree is 4
    // similarly it can be used to get the beginning of root which would get us the leftmost node
    //
    static NODE* subtreeLeftMostNode(NODE* root) {
        NODE* temp = root;
        if (temp == nullptr) {
            return nullptr;
        }
        else {
            while (temp->left != nullptr) {
                temp = temp->left;
            }
        }
        return temp;
    }
    //
    //createNode:
    //private function that simply takes input key and value and creates a node. What is done with it afterwards is for the public functions to decide
    NODE* createNode(keyType key, valueType value) {
        NODE *tempNode = new NODE;
        tempNode->key = key;
        tempNode->value = value;
        tempNode->right = tempNode->left = nullptr;
        tempNode->nL = tempNode->nR = 0;
        tempNode->isThreaded = false;
        return tempNode;
    }

    //
    // iterator:
    // This iterator is used so that mymap will work with a foreach loop.
    //
    struct iterator {
     private:
        NODE* curr;  // points to current in-order node for begin/end

     public:
        iterator(NODE* node) {
            curr = node;
        }

        keyType operator *() {
            return curr -> key;
        }

        bool operator ==(const iterator& rhs) {
            return curr == rhs.curr;
        }

        bool operator !=(const iterator& rhs) {
            return curr != rhs.curr;
        }

        bool isDefault() {
            return !curr;
        }

        //
        // operator++:
        //
        // This function should advance curr to the next in-order node.
        // O(logN)
        //
        // Goes to the right unless it is not threaded in which case it will be treated as a subtree and will get the leftmost node which will be
        // the next valid node
        iterator operator++() {

            if (curr->isThreaded) {
                curr = curr->right;
            }
            else {
                curr = subtreeLeftMostNode(curr->right);
            }
            return iterator(curr);
        }
    };

 public:
    //
    // default constructor:
    //
    // Creates an empty mymap.
    // Time complexity: O(1)
    //
    mymap() {

        //simple empty tree
        root = nullptr;
        size = 0;

    }

    //
    // copy constructor:
    //
    // Constructs a new mymap which is a copy of the "other" mymap.
    // Sets all member variables appropriately.
    // Time complexity: O(nlogn), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    mymap(const mymap& other) {

        //sets current tree as empty and populates itself with the contents of the tree it is trying to copy
        root = nullptr;
        size = 0;
        NODE* temp = subtreeLeftMostNode(other.root);
        while (temp != nullptr){
            put(temp->key, temp->value);
            if ( temp->isThreaded) {
                temp = temp->right;
            }
            else {
                temp = subtreeLeftMostNode(temp->right);
            }
        } // end of while loop which will be completed onces all nodes are copied over


    }

    //
    // operator=:
    //
    // Clears "this" mymap and then makes a copy of the "other" mymap.
    // Sets all member variables appropriately.
    // Time complexity: O(nlogn), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    mymap& operator=(const mymap& other) {
        clear(); // very similar to copy constructor except this function will first clear its tree before populating it with the contents of the other tree
        root = nullptr;
        size = 0;
        NODE* temp = subtreeLeftMostNode(other.root);
        while (temp != nullptr){
            put(temp->key, temp->value);
            if ( temp->isThreaded) {
                temp = temp->right;
            }
            else {
                temp = subtreeLeftMostNode(temp->right);
            }
        }
        return *this;
    }

    // clear:
    //
    // Frees the memory associated with the mymap; can be used for testing.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    void clear() {
        NODE* temp = subtreeLeftMostNode(root);
        NODE* nextNode = nullptr; // uses a next node pointer in order to confirm which  node it is moving to and to mark the node that it is moving from as a node that needs to be deleted
        while(temp != nullptr) {
            if (temp->isThreaded) {
                nextNode = temp->right;
            }
            else {
                nextNode = subtreeLeftMostNode(temp->right);
            }
            delete temp;
            temp = nextNode;
        } // end of while loop which should have cleared all nodes and final touches are to make the tree empty by marking the root as null and its size as 0
        root = nullptr;
        size = 0;
    }

    //
    // destructor:
    //
    // Frees the memory associated with the mymap.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    ~mymap() {


        clear(); // empties tree


    }

    //
    // put:
    //
    // Inserts the key/value into the threaded, self-balancing BST based on
    // the key.
    // Time complexity: O(logn + mlogm), where n is total number of nodes in the
    // threaded, self-balancing BST and m is the number of nodes in the
    // sub-tree that needs to be re-balanced.
    // Space complexity: O(1)
    //
    void put(keyType key, valueType value) {

        NODE* temp = createNode(key, value); // simply create node
        size++;
        if (root == nullptr) {
            root = temp; // if empty tree then new node will be first node
            return;
        }

        NODE *base = root;
        NODE *parent = nullptr; // use parent node to keep track of where to thread
        while (1) {
            parent = base;
            if (key  == base->key) {
                base->value = temp->value; // if key is already present update value
                delete temp;
                size--;
                break;
            }
            if (key < base->key) {
                base = base->left; // move node to left if key is less than the node's key it is copying into
                if (base == nullptr) {
                    parent->left = temp; // if current node that just got moved is a nullptr then update parent node and update new node to be the parent's left child node
                    temp->right = parent;
                    temp->isThreaded = true; //make the nade that is just added a threaded node and thread to parent
                    break;
                }

            }
            else {
                if (base->isThreaded == false) {
                    base = base->right; // move node to right if key is not less than or is not equal to current key
                    if (base == nullptr) {
                        parent->right = temp; //  if current node moves to the right and is not threaded and is a nullptr AKA rigth most node, then add node and exit
                        break;
                    }
                }
                else {
                    NODE* extra = base->right; // otherwise create new temp node which will simply hold the current node at the right
                    base->isThreaded = false;  // afterwards, it updates the current threading bool  and adds the new node to the right
                    base->right = temp;
                    temp->right = extra; // sets the new node's threaded node to the previous node's thread
                    temp->isThreaded = true; // updates new node's isThreaded bool value
                    break;
                }
            }

        }

    }

    //
    // contains:
    // Returns true if the key is in mymap, return false if not.
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    bool contains(keyType key) {

        NODE* check = root;
        while (check != nullptr) {
            if (check->key == key) {
                return true;   // simply traverses tree and returns true if tree contains any node with matching key, otherwise returns false
            }
            else if ( check->key > key) {
                check = check->left;
            }
            else if (check->key < key) {
                if (check->isThreaded) {
                    check = nullptr;
                }
                else {
                    check = check->right;
                }

            } // end while loop
        }
        return false;
    }

    //
    // get:
    //
    // Returns the value for the given key; if the key is not found, the
    // default value, valueType(), is returned (but not added to mymap).
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    valueType get(keyType key) {

        NODE* check = root;
        while (check != nullptr) {
            if (check->key == key) {
                return check->value; // same thing as contains function however this time returns value at matching key otherwise returns default value for given valuetype
            }
            else if ( check->key > key) {
                check = check->left;
            }
            else {
                if (check->isThreaded) {
                    check = nullptr;
                }
                else {
                    check = check->right;
                }
            }
        }
        return valueType();

    }

    //
    // operator[]:
    //
    // Returns the value for the given key; if the key is not found,
    // the default value, valueType(), is returned (and the resulting new
    // key/value pair is inserted into the map).
    // Time complexity: O(logn + mlogm), where n is total number of nodes in the
    // threaded, self-balancing BST and m is the number of nodes in the
    // sub-trees that need to be re-balanced.
    // Space complexity: O(1)
    //
    valueType operator[](keyType key) {


        NODE* check = root;
        while (check != nullptr) {
            if (check->key == key) {
                return check->value; // almost exactly the same as the gets function
            }
            else if ( check->key > key) {
                check = check->left;
            }
            else {
                if (check->isThreaded) {
                    check = nullptr;
                }
                else {
                    check = check->right;
                }
            }
        }
        put(key, valueType()); // this time creates the key if it is not found and returns default valuetype as specified
        return valueType();

    }

    //
    // Size:
    //
    // Returns the # of key/value pairs in the mymap, 0 if empty.
    // O(1)
    //
    int Size() {

        return size; // simply outputs current size
    }

    //
    // begin:
    //
    // returns an iterator to the first in order NODE.
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    iterator begin() {
        NODE* start = root;
        if (start == nullptr) {
            return iterator(nullptr);
        }
        else {
            while (start->left != nullptr) {
                start = start->left; // simply goes to the farthest left node on the current tree
            }
        }
        return iterator(start);
    }

    //
    // end:
    //
    // returns an iterator to the last in order NODE.
    // this function is given to you.
    //
    // Time Complexity: O(1)
    //
    iterator end() {
        return iterator(nullptr);
    }



    //
    // toString:
    //
    // Returns a string of the entire mymap, in order.
    // Format for 8/80, 15/150, 20/200:
    // "key: 8 value: 80\nkey: 15 value: 150\nkey: 20 value: 200\n
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    string toString() {
        NODE* check = root;
        stringstream ss;
        _toStringRecursion(check, ss); // calls recursion function which goes through left and right nodes
        return ss.str(); // returns end result of recursion from the string stream which holds the entire tree's data
    }

};