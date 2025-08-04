//
// Created by Harshith Sankar Narne on 8/3/25.
//

#ifndef PAIRINGHEAP_H
#define PAIRINGHEAP_H



class PairingHeap {
//More complicated
    //insert, extract, search
    //Most important function is merge and extract
    //Merge is complicated and needs to be implemented correctly
private:
    Node* root = nullptr;

    void insert(Node* node, int ID, int priority, string name)
    {
        if (root == nullptr)
        {
            root = new Node(ID, priority, name);
        } else
        {
            merge(root, node);
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
                two->sibling = nullptr;
                two->sibling = temp;
            }

        } else if (one->task.priority < two->task.priority)
        {
            parent = two;
            if (parent->left == nullptr)
            {
                parent->left = one;
                one->sibling = nullptr;
            } else
            {
                Node* temp = parent->left;
                one->sibling = nullptr;
                parent->left = one;
                one->sibling = temp;
            }
        } else if (one->task.priority == two->task.priority)
        {
            parent = one;
            if (parent->left == nullptr)
            {
                parent->left = two;
                two->sibling = nullptr;
            } else
            {
                Node* temp = parent->left;
                two->sibling = nullptr;
                parent->left = two;
                two->sibling = temp;
            }
        }
        return parent;
    }


    Node* extractMax()
    {
        //Remove the root
        //Store all of its children
        //Merge the children use two pass method
        //Left to right then right to left
        Node* max = root;

        Node* lefty = root;

        vector<Node*> list;

        if (lefty->left != nullptr)
        {
            lefty = lefty->left;
            list.push_back(lefty);
        }

        Node* temp = lefty;

        while (temp->sibling != nullptr)
        {
            list.push_back(temp->sibling);

            temp = temp->sibling;
        }

        vector<Node*> merged;

        if (list.size() % 2 == 0)
        {
            //Left to right
            for (int i = 0; i < list.size(); i+= 2)
            {
                merged.push_back(merge(list[i], list[i+1]));
            }
            //Right to left
            int size = merged.size() - 1;
            Node* last = list[size];
            for (int j = size; j > 0; j--)
            {
                last = merge(merged[j-1], last);
            }
        } else if (list.size() % 2 != 0)
        {
            for (int i = 0; i < list.size() - 1; i+= 2)
            {
                merged.push_back(merge(list[i], list[i+1]));
            }
            int size = merged.size() - 1;
            Node* last = list[size];
            for (int j = size - 2; j >= 0; j--)
            {
                last = merge(merged[j-1], last);
            }
        }

        root = last;
        return max;
        delete max;
    }








};



#endif //PAIRINGHEAP_H
