//
// Created by Harshith Sankar Narne on 8/3/25.
//

#ifndef PAIRINGHEAP_H
#define PAIRINGHEAP_H



#include <string>
#include <vector>
#include <iostream>
#include "Task.h"



struct Node
{
    Task task;
    Node* left;
    Node* sibling;
    Node(int ID, int priority, std::string name) : task(ID, priority, std::move(name)), left(nullptr), sibling(nullptr) {}

};

class PairingHeap {
//More complicated
    //insert, extract, search
    //Most important function is merge and extract
    //Merge is complicated and needs to be implemented correctly
private:
    Node* root = nullptr;
    void insertHelper(int ID, int priority, std::string name);
    Node* mergeHelper(Node* one, Node* two);
    Task extractMaxHelper();



public:

    Node* assignroot(Node* node)
    {
        root = node;
        return root;
    }

    void insert(int ID, int priority, std::string name)
    {
        insertHelper(ID, priority, name);
    }

    Node* merge(Node* one, Node* two)
    {
        Node* finaltree = mergeHelper(one, two);
        return finaltree;
    }


    Task extractMax()
    {
        Task maximum_priority = extractMaxHelper();
        return maximum_priority;
    }


    Task peek()
    {
        if (root == nullptr)
        {
            return Task(0,0, "");
        }
        return root->task;
    }


    void clear()
    {
        deleteEntireHeap(root);
        root = nullptr;
    }

    void deleteEntireHeap(Node* node)
    {
        if (node == nullptr)
        {
            return;
        }
        deleteEntireHeap(node->left);
        deleteEntireHeap(node->sibling);
        delete node;
    }


    ~PairingHeap()
    {
        deleteEntireHeap(root);
    }


    Node* getroot()
    {
        return root;
    }


};



#endif //PAIRINGHEAP_H
