//
// Created by Harshith Sankar Narne on 8/3/25.
//

#include "PairingHeap.h"



void PairingHeap::insertHelper(int ID, int priority, std::string name)
{
    Node* newNode = new Node(ID, priority, name);
    if (root == nullptr)
    {
        root = newNode;
    } else
    {
        root = merge(root, newNode);
    }
}


void PairingHeap::mergeHelper(Node* one, Node* two)
{

}





