//
// Created by Harshith Sankar Narne on 8/3/25.
//

#ifndef PAIRINGHEAP_H
#define PAIRINGHEAP_H



#include <string>
#include <vector>
#include <iostream>


#include <"Task.h">



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


public:
    void printNode(Node* node, int level = 0) {
        if (node == nullptr) return;
        for (int i = 0; i < level; ++i) std::cout << "  ";
        std::cout << "ID: " << node->task.ID << ", Prio: " << node->task.priority << "\n";
        printNode(node->left, level + 1);
        printNode(node->sibling, level);
    }

    void insert(int ID, int priority, std::string name)
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

    Node* merge(Node* one, Node* two)
    {
        Node* parent = nullptr;
        if (one == nullptr)
        {
            return two;
        } else if (two == nullptr)
        {
            return one;
        }


        //Compare the priority of the two nodes
        if (one->task.priority > two->task.priority)
        {
            parent = one;
            if (parent->left == nullptr)
            {
                parent->left = two;
                two->sibling = nullptr;
            } else
            {
                Node* temp = parent->left;
                parent->left = two;
                two->sibling = temp;
            }

        } else if (one->task.priority < two->task.priority)
        {
            parent = two;
            if (parent->left == nullptr)
            {
                one->sibling = nullptr;
                parent->left = one;
            } else
            {
                Node* temp = parent->left;
                parent->left = one;
                one->sibling = temp;
            }
        } else
        {
            parent = one;
            if (parent->left == nullptr)
            {
                parent->left = two;
                two->sibling = nullptr;

            } else
            {
                Node* temp = parent->left;
                parent->left = two;
                two->sibling = temp;
            }
        }
        return parent;
    }


    Task extractMax()
    {

        if (root == nullptr)
        {
            //cout << "Empty Heap" << endl;
            return Task(0,0,"");
        }

        Node* max = root;

        std::vector<Node*> list;


        max->sibling = nullptr;

        Node* child = nullptr;

        if (root->left != nullptr)
        {
            child = root->left;
        }

        while (child != nullptr)
        {
            Node* sibly = child->sibling;
            child->sibling = nullptr;
            list.push_back(child);
            child = sibly;
        }


        std::vector<Node*> merged;

        Node* last = nullptr;


        if (list.size() == 0)
        {
            last = nullptr;
        }
        else if (list.size() == 1)
        {
            last = list[0];
        }
        else if (list.size() % 2 == 0)
        {
            //Left to right
            for (int i = 0; i < list.size(); i+= 2)
            {

                merged.push_back(merge(list[i], list[i+1]));
            }
            //Right to left
            int size = merged.size() - 1;
            last = merged.back();
            for (int j = size - 1; j >= 0; j--)
            {
                last = merge(merged[j], last);
            }
        } else //if (list.size() % 2 != 0)
        {
            for (int i = 0; i < list.size() - 1; i+= 2)
            {
                merged.push_back(merge(list[i], list[i+1]));
            }
            merged.push_back(list.back());
            int size = merged.size() - 1;
            last = merged.back();
            for (int j = size - 1; j >= 0; j--)
            {
                last = merge(merged[j], last);
            }
        }





        Task maxExtract = max->task;
        root = last;
        delete max;
        return maxExtract;
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
        clear(node->left);
        clear(node->sibling);
        delete node;
    }




    ~PairingHeap()
    {
        clear();
    }


    Node* getroot()
    {
        return root;
    }


};



#endif //PAIRINGHEAP_H
