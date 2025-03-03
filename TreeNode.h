// Annika Brown
// 2428684
// annbrown@chapman.edu
// CPSC350
// PA5
// treeNode class for BST

#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <cstdlib>
#include <iostream>
using namespace std;

template <typename T>
class TreeNode{
public:
    TreeNode(T d);
    virtual ~TreeNode();
    T getData();

    template <typename S>
    friend class LazyBST;

private:
    T m_data;
    TreeNode<T>* m_left;
    TreeNode<T>* m_right;
    int height_left;
    int height_right;
};

template <typename T>
TreeNode<T>::TreeNode(T d){
  m_data = d;
  m_left = NULL;
  m_right = NULL;
  height_left = 0;
  height_right = 0;
}

template <typename T>
TreeNode<T>::~TreeNode(){
  if(m_left != NULL){
    delete m_left;
  }
  if(m_right != NULL){
    delete m_right;
  }
}

template <typename T>
T TreeNode<T>::getData(){
  return m_data;
}

#endif
