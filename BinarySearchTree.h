//
// Created by Ahsan Jalil on 11/30/17.
//

#ifndef DSAPROJ_BINARYSEARCHTREE_H
#define DSAPROJ_BINARYSEARCHTREE_H

#include "Graph.h"
using namespace std;

template<class DT>
class Node {
private:
    Vertex<DT>* data;
    Node<DT>* leftChild;
    Node<DT>* rightChild;
public:
    explicit Node(Vertex<DT>* data_ = NULL){
        data = data_;
        leftChild = NULL;
        rightChild = NULL;
    }
    void setleftChild(Node<DT>* Child) {
        leftChild = Child;
    }
    void setrightChild(Node<DT>* Child) {
        rightChild = Child;
    }
    void setData(Vertex<DT>*  data_) {
        data = data_;
    }
    Node<DT>* getleftChild() {
        return leftChild;
    }
    Node<DT>* getrightChild() {
        return rightChild;
    }
    Vertex<DT>* getData() {
        return data;
    }
    bool isLeaf() {
        if (leftChild == NULL && rightChild == NULL)
            return true;
        return false;
    }
    bool hasOneChild() {
        return (leftChild == NULL || rightChild == NULL);
    }
    bool hasTwoChild() {
        return (leftChild != NULL && rightChild != NULL);
    }
};



template<class DT>
class BinarySearchTree{
private:
    Node<DT>* root;
public:
    BinarySearchTree() {
        root = NULL;
    }
    bool Insert(Vertex<DT>* data) {
        Node<DT>* temp = new Node<DT>(data);
        //if the tree does not exist the first insertion is done on the root
        if (root == NULL) {
            root = temp;
            return true;
        }
        else {
            Node<DT>* childFlag = root;
            Node<DT>* parentFlag = NULL;
            while (1) {
                parentFlag = childFlag;
                //if the data to be inserted is less then the parent then the node moves towards the left
                if (data->get_valF() < parentFlag->getData()->get_valF()) {
                    childFlag = childFlag->getleftChild();
                    //when parentFlag->getleftChild==NULL the new node is inserted there
                    if (childFlag == NULL) {
                        parentFlag->setleftChild(temp);
                        return true;
                    }
                }
                    //else if the data to be inserted is greater then the parent then the node moves towards the right
                else if (data->get_valF() > parentFlag->getData()->get_valF()) {
                    childFlag = childFlag->getrightChild();
                    //when parentFlag->getrightChild==NULL the new node is inserted there
                    if (childFlag == NULL) {
                        parentFlag->setrightChild(temp);
                        return true;
                    }
                }
                    //not works when data==parent->getData()
                else {
                    break;
                }
            }
        }
        return false;
    }
    Vertex<DT>* Search(Vertex<DT>* data) {
        Node<DT>* flag = root;
        while (flag != NULL) {
            //if the data is found, it is returned
            if (flag->getData()->get_valF() == data->get_valF()) {
                return flag->getData();
            }
                //if the data is smaller then the search is transferred to the left sub-tree
            else if (flag->getData()->get_valF() > data->get_valF()) {
                flag = flag->getleftChild();
            }
                //if the data is greater then the search is transferred to the right sub-tree
            else if (flag->getData()->get_valF() < data->get_valF()) {
                flag = flag->getrightChild();
            }
        }
        return NULL;
    }
    bool Delete(Vertex<DT>* data) {
        Node<DT>* childFlag = root;
        Node<DT>* parentFlag = NULL;
        //in this while loop the node to be deleted and its parent is located in the tree
        while (1) {
            if (childFlag->getData()->get_valF() == data->get_valF()) {
                break;
            }
            parentFlag = childFlag;
            if (childFlag->getData()->get_valF() > data->get_valF()) {
                childFlag = childFlag->getleftChild();
            }
            else if (childFlag->getData()->get_valF() < data->get_valF()) {
                childFlag = childFlag->getrightChild();
            }
            if (childFlag == NULL) {
                return false;
            }
        }
        //if the node to be deleted has two child
        if (childFlag->hasTwoChild()) {
            //finds the largest node in the left sub-tree -> temp and its parent -> temp0
            Node<DT>* temp = childFlag->getleftChild();
            Node<DT>* temp0 = NULL;
            while (!temp->isLeaf()) {
                temp0 = temp;
                temp = temp->getrightChild();
            }
            //if the node to be deleted is the root node then temp is made the new root and the rightchild of temp0 is set to NULL
            if (childFlag == root && temp0 != NULL) {
                temp->setleftChild(root->getleftChild());
                temp->setrightChild(root->getrightChild());
                temp0->setrightChild(NULL);
                root = temp;
                return true;
            }
                //if node to be deleted is not root node
            else {
                // the new allocation of root is done first
                if (temp0 != NULL) {
                    temp->setleftChild(childFlag->getleftChild());
                    temp->setrightChild(childFlag->getrightChild());
                    temp0->setleftChild(NULL);
                }
                else {
                    temp->setleftChild(childFlag->getleftChild());
                }
                //deletion of the previous root is done afterwards
                if (childFlag == parentFlag->getleftChild()) {
                    delete parentFlag->getleftChild();
                    parentFlag->setleftChild(temp);
                    return true;
                }
                else if (childFlag == parentFlag->getrightChild()) {
                    delete parentFlag->getrightChild();
                    parentFlag->setrightChild(temp);
                    return true;
                }
            }
            return false;
        }
            //if the node to be deleted has one child
        else if (childFlag->hasOneChild()) {
            //if node to be deleted is root node
            if (childFlag == root) {
                //if root has only right child
                if (root->getleftChild() == NULL) {
                    //the right child is made the new root
                    Node<DT>* temp = childFlag->getrightChild();
                    delete childFlag;
                    childFlag = NULL;
                    root = temp;
                    return true;
                }
                    //if root has only left child
                else if (root->getrightChild() == NULL) {
                    //the left child is made the new root
                    Node<DT>* temp = childFlag->getleftChild();
                    delete childFlag;
                    childFlag = NULL;
                    root = temp;
                    return true;
                }
            }
                //if the node to be deleted is a left child
            else if (childFlag == parentFlag->getleftChild()) {
                //if left child of node to be deleted does not exist
                if (childFlag->getleftChild() == NULL) {
                    //the right child of node to be deleted becomes the left child
                    //of the parent of node to be deleted
                    Node<DT>* temp = childFlag->getrightChild();
                    delete childFlag;
                    parentFlag->setleftChild(temp);
                    return true;
                }
                    //if the right child of node to be deleted does not exist
                else if (childFlag->getrightChild() == NULL) {
                    //the left child of node to be deleted becomes the left child
                    //of the parent of node to be deleted
                    Node<DT>* temp = childFlag->getleftChild();
                    delete childFlag;
                    parentFlag->setleftChild(temp);
                    return true;
                }
            }
                //if the node to be deleted is a right child
            else if (childFlag == parentFlag->getrightChild()) {
                //if right child of node to be deleted does not exist
                if (childFlag->getrightChild() == NULL) {
                    //the left child of node to be deleted becomes the right child
                    //of the parent of node to be deleted
                    Node<DT>* temp = childFlag->getleftChild();
                    delete childFlag;
                    parentFlag->setrightChild(temp);
                    return true;
                }
                    //if left child of node to be deleted does not exist
                else if (childFlag->getleftChild() == NULL) {
                    //the right child of node to be deleted becomes the right child
                    //of the parent of node to be deleted
                    Node<DT>* temp = childFlag->getrightChild();
                    delete childFlag;
                    parentFlag->setrightChild(temp);
                    return true;
                }
            }
        }
            //if the node to be deleted is a leaf node
        else if (childFlag->isLeaf()) {
            //if the node to be deleted is the root node
            if (childFlag == root) {
                //root is deleted hence the tree does not exist
                delete root;
                root = NULL;
                return true;
            }
                //simple node deletion depending upon where it is wrt the parent node
            else if (childFlag == parentFlag->getleftChild()) {
                delete childFlag;
                parentFlag->setleftChild(NULL);
                return true;
            }
            else if (childFlag == parentFlag->getrightChild()) {
                delete childFlag;
                parentFlag->setrightChild(NULL);
                return true;
            }
        }
        return false;
    }
    bool isEmpty() {
        return root == NULL;
    }
    ~BinarySearchTree() {
        delTree();
    }
};

#endif //DSAPROJ_BINARYSEARCHTREE_H
