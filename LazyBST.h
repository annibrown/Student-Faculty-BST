// Annika Brown
// 2428684
// annbrown@chapman.edu
// CPSC350
// PA5
// Self-Balancing Binary Search Tree

#ifndef LAZY_BST_H
#define LAZY_BST_H

#include "TreeNode.h"
#include <math.h>
#include <iostream>

template <typename T>
class LazyBST{
    public:
        LazyBST();
        virtual ~LazyBST();
        bool iterContains(T d); 
        bool contains(T d); // recursive version that uses recContainsHelper
        void printInOrder(); // least to greatest 
        void printTreePostOrder(); // left tree then right tree then root 
        void insert(T d, bool balancing);
        int size(); 
        T max(); // right most child
        T min(); // left most child 
        T median(); // will only work if tree is balanced 
        void remove (T d, bool balancing); 
        bool unbalanced();
        void balance();
        T* balanceArr;
        T* leftArr;
        T* rightArr;
        T get(T d);
        void outputInOrder(std::ostream &out);
        void outputIOHelper(TreeNode<T>* n, std::ostream &out);
    
    private: 
        TreeNode<T>* m_root;
        int m_size;
        bool recContainsHelper(TreeNode<T>* n, T d); 
        void printIOHelper(TreeNode<T>* n);
        void printTreePostOrderHelper(TreeNode<T>* subTreeRoot);
        void insertHelper(TreeNode<T>*& subTreeRoot, T& d);
        T getMaxHelper(TreeNode<T>* n);
        T getMinHelper(TreeNode<T>* n);
        void findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent);
        TreeNode<T>* getSuccessor (TreeNode<T>* rightChild);
        T* splitLeft(T arr[], int size, int median);
        T* splitRight(T arr[], int size, int median);
        void balanceHelper(T arr[], int size);
        int arrMedian;
        std::string output = "";
};

   template <typename T>
        LazyBST<T>::LazyBST(){
        m_root = NULL;
        m_size = 0;
    }

    template <typename T>
    LazyBST<T>::~LazyBST(){
        // TO DO: free up all memory 
    }


    // how do we find whether or not a tree contains a key?
        // navigate through the tree until we find it 
        // well it's not linear and each node has a left and right child potentially so... 

        // let's say we are at the root and we assume the root is not null
        // how do we know if the tree contains "d"?
        // let's try iteratively 
    template <typename T>
    bool LazyBST<T>::iterContains(T d){
        if (m_root == NULL){ // tree is empty
            return false; 
        }
        if (m_root -> data == d){ // root is the key d
            return true;
        }

        // look for d 
        bool found = false; 
        TreeNode<T>* current = m_root;
        while (!found){
            // check if d is greater than current go right 
            if (d > current -> m_data){
                current = current -> m_right;
            } else { // if d is less than/ == current go left 
                current = current -> m_left;
            } 
            // check if current node is NULL -> we've reached a leaf and d was not found
            if (current == NULL){
                found =  false; 
                break;
            }

            // check if the current node's data is d -> we found d 
            if (current -> m_data == d){
                found = true;
            }
        }
        return found;
    }

    // RECURSIVE CONTAINS
    template <typename T>
    bool LazyBST<T>::contains(T d){
        return recContainsHelper(m_root, d);
    }

    // RECURSIVE CONTAINS HELPER
    template <typename T>
    bool LazyBST<T>::recContainsHelper( TreeNode<T>* n, T d){
        if (n == NULL){ // if it is null then d is not in tree 
            return false;
        } 
        if (n -> m_data == d) { // if it is not null, is it here? 
            return true;
        }
        if (d > n -> m_data){ // it's not null but it's also not here, check if it is > or <
            return recContainsHelper( n -> m_right, d);
        } else {
            return recContainsHelper( n -> m_left, d);
        }
    }

    template <typename T>
    void LazyBST<T>::printInOrder(){
        printIOHelper(m_root);
    }

    template <typename T>
    void LazyBST<T>::printIOHelper(TreeNode<T>* n){
        if (n != NULL){ // is the node null? 
            printIOHelper(n -> m_left); // if not then print the left thing 
            std::cout << n -> m_data << std::endl; // then print the key of the curr node 
            printIOHelper(n -> m_right); // then print the right thing 
        } 
    }


    template <typename T>
    void LazyBST<T>::printTreePostOrder(){
        printTreePostOrderHelper(m_root);
    }

    template <typename T>
    void LazyBST<T>::printTreePostOrderHelper(TreeNode<T>* subTreeRoot){
        if(subTreeRoot != NULL){
            printTreePostOrderHelper(subTreeRoot->m_left);
            printTreePostOrderHelper(subTreeRoot->m_right);
            std::cout << subTreeRoot->m_data << std::endl;
        }
    }

    // INSERT RECURSIVETY 
    template <typename T>
    void LazyBST<T>::insert(T d, bool balancing){
        if (contains(d)) {
            std::cout << "This already exists" << std::endl;
            return;
        }
        insertHelper(m_root, d);

        ++m_size;
        if (unbalanced() && (balancing == false)) {
            balance();
        }
    }
    // INSERT HELPER SO WE DO NOT HAVE TO PASS IN ROOT 
    // pass in by reference so that you don't have to manually mess with pointers (r & l children)
    template <typename T>
    void LazyBST<T>::insertHelper(TreeNode<T>*& subTreeRoot, T& d){
        if(subTreeRoot == NULL){
            subTreeRoot =  new TreeNode<T>(d); // insert here  & stop recursive call 

        } else if(d > subTreeRoot->m_data){
            subTreeRoot->height_right++;
            insertHelper(subTreeRoot->m_right, d);

        } else{
            subTreeRoot->height_left++;
            insertHelper(subTreeRoot->m_left, d);
        }
    }

    // HELPER METHODS 

    // GET SIZE 
    template <typename T>
    int LazyBST<T>::size(){
       return m_size;
    }

    
    // GET MAX 
    template <typename T>
    T LazyBST<T>::max(){
       return getMaxHelper(m_root);
    }

    template <typename T>
    T LazyBST<T>::getMaxHelper(TreeNode<T>* n){
       if(n -> m_right == NULL){
        return n -> m_data;
       } else {
            return getMaxHelper(n -> m_right);
       }
       
    }

    // GET MIN 
    template <typename T>
    T LazyBST<T>::min(){
       return getMinHelper(m_root);
    }

    template <typename T>
    T LazyBST<T>::getMinHelper(TreeNode<T>* n){
       if(n -> m_left == NULL){
            return n -> m_data;
       } else {
            return getMinHelper(n -> m_left);
       }
       
    }


    // GET MEDIAN - ONLY WORKS IF TREE IS BALANCED! 
    template <typename T>
    T LazyBST<T>::median(){
        //check if empty we assume it is a non-empty tree
        return m_root->m_data;
    }

    // HELPER METHODS 
    template <typename T>
    void LazyBST<T>::findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent){
        // FIND THE NODE WE WANT TO DELETE AND ITS PARENT NODE 
        parent = target; 
        while (target != NULL && target -> m_data != key){ // while target still has children and it is not our actual target
            parent = target; 
            if (key < target -> m_data){ // if the key is less than the current target node, keep going left
                target -> height_left--;
                target = target -> m_left; 
            } else {
                target -> height_right--;
                target = target -> m_right;
            }
        }
        if (key < parent -> m_data){
            parent -> height_left--;
        } else {
            parent -> height_right--;
        }
    }

    template <typename T>
    TreeNode<T>* LazyBST<T>::getSuccessor (TreeNode<T>* rightChild){
        while (rightChild -> m_left != NULL){ // If the node coming in (rightChild) doesn't have a left child then this is our successor and we're done, else:
            rightChild = rightChild -> m_left;
        }
        return rightChild; // not really (necessarily) a right child, this is the successor! 
    }

    template <typename T>
    void LazyBST<T>::remove(T d, bool balancing){
        // check if tree is empty 
        // we assume the tree is non-empty 
        TreeNode<T>* target = NULL; 
        TreeNode<T>* parent = NULL; 
        target = m_root;

        // find the target 
        findTarget(d, target, parent); // no need save under any variables, target and parent are redefined bc we passed them in by reference  

        // target value was not found - it does not exist in our tree
        if (target == NULL){
            return;
        }

        // SCENARIO 1: TARGET IS A LEAF (INCLUDING ROOT)
        if (target -> m_left == NULL && target -> m_right == NULL){
            if (target == m_root){
                m_root = NULL;
            } else { // if it's a leaf but not the root 
                // check if target is its parent's left or right child 
                if (target == parent -> m_left){ // if target is a left child
                    parent -> m_left = NULL;
                } else { // target is a right child 
                    parent -> m_right = NULL;
                }
            }
            delete target;
						-- m_size;
        } 

        // SCENARIO 3: TARGET HAS TWO CHILDREN 
        else if (target -> m_left != NULL && target -> m_right != NULL){  // both children pointers are not null
            TreeNode<T>* suc = getSuccessor(target -> m_right);
            T value = suc -> m_data;
            remove(value, false); // goes in the BST remove method and removes the node w/ d = value
            target -> m_data = value;
        } 

        // SCENARIO 2: TARGET HAS 1 CHILD 
        else { 
            TreeNode<T>* child;
            // check whether target has a left or right child 
            if (target -> m_left != NULL){ // target has a left child 
                child = target -> m_left;
            } else{                        // target has a right child 
                child = target -> m_right;
            }

            if (target == m_root){
                m_root = child;
            } else {
                if (target == parent -> m_left){ // our target is a left child 
                    parent -> m_left = child; // make the parent's left child the target's child 
                } else {                       // our target is a right child 
                    parent -> m_right = child; // make the parent's right child the target's child 
                }
            }
						target -> m_left = NULL;
						target -> m_right = NULL;

            delete target;
						-- m_size;
        }
        //  --m_size; // TAKE AWAY FROM HERE
        if (balancing == false) {
            if (!(m_root == NULL)) {
                if (unbalanced()) {
                    balance();
                }
            }
        }
        return;
    }

    // checks if tree is unbalanced 
    // if left and right height of root are different by more than a factor of 1.5
    // @return bool, if tree is unbalanced
    template <typename T>
    bool LazyBST<T>::unbalanced(){
        if (((m_root -> height_left)*1.5 < m_root -> height_right) || ((m_root -> height_right)*1.5 < m_root -> height_left)) {
            return true;
        } else {
            return false;
        }
    }

    // balances the tree
    template <typename T>
    void LazyBST<T>::balance(){
        // Each of the N values in the LB-BST is placed in an array of size N in ascending order
        balanceArr = new T[size()];
        for (int i = 0; i < size(); i++) {
            balanceArr[i] = min();
            remove(min(), true);
        }
        balanceHelper(balanceArr, size());
    }

    // balance helper method
    // @param T arr[], array of Ts
    // @param size, size of array
    template <typename T>
    void LazyBST<T>::balanceHelper(T arr[], int size) {
        if (size < 3) {
            for (int i = 0; i < size; i++) {
                insert(arr[i], true);
            }
        } else {
            arrMedian = size / 2;
            insert(arr[arrMedian], true);
            balanceHelper(splitLeft(arr, size, arrMedian), arrMedian);
            balanceHelper(splitRight(arr, size, arrMedian), size-arrMedian);
        }
    }

    // returns the left half of the input array
    template <typename T>
    T* LazyBST<T>::splitLeft(T arr[], int size, int median) {
        leftArr = new T[median];
        for (int i = 0; i < median; i++) {
            leftArr[i] = arr[i];
        }
        return leftArr;
    }

    // returns the right half of the input array
    template <typename T>
    T* LazyBST<T>::splitRight(T arr[], int size, int median) {
        rightArr = new T[size-median];
        for (int i = median+1; i < size; i++) {
            rightArr[i] = arr[i];
        }
        return rightArr;
    }

    // returns the item from tree that equals the input
    template <typename T>
    T LazyBST<T>::get(T d){
        if (m_root -> m_data == d){ // root is the key d
            return m_root -> m_data;
        }
        // look for d 
        bool found = false; 
        TreeNode<T>* current = m_root;
        while (!found){
            // check if d is greater than current go right 
            if (d > current -> m_data){
                current = current -> m_right;
            } else { // if d is less than/ == current go left 
                current = current -> m_left;
            } 
            // check if the current node's data is d -> we found d 
            if (current -> m_data == d){
                found = true;
                return current -> m_data;
            }
        }
    }

    // outputs items in tree in ascending order
    template <typename T>
    void LazyBST<T>::outputInOrder(std::ostream &out) {
        outputIOHelper(m_root, out);
    }
        
    // outputInOrder helper method
    template <typename T>
    void LazyBST<T>::outputIOHelper(TreeNode<T>* n, ostream &out) {
        if (n != NULL){ // is the node null? 
            outputIOHelper(n -> m_left, out); // if not then print the left thing 
            out << n -> m_data  << std::endl; // then print the key of the curr node
            outputIOHelper(n -> m_right, out); // then print the right thing 
        } 
    }

#endif
