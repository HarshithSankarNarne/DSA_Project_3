//
// Created by Harshith Sankar Narne on 8/4/25.
//

#include <iostream>
using namespace std;
#include "PairingHeap.cpp"

#include "MaxHeap.cpp"


//First test the Pairing Heap
//Test to see if the insert is working
//Test to see if the merge is working

void PairingInsertchecker()
{
    PairingHeap heap;

    heap.insert(60, 5, "A");
    heap.insert(60, 10, "B");
    heap.insert(60, 15, "C");
    heap.insert(60, 20, "D");
    heap.insert(60, 20, "E");
    heap.insert(60, 50, "F");

    while (heap.getroot() != nullptr)
    {
        Task extract = heap.extractMax();
        cout << extract.name << " " << extract.priority << endl;

    }
}

void PairingMergeTester() {
    //Test merge between two different heaps
    cout << "Merge Test 1" << endl;
    PairingHeap heap1;
    PairingHeap heap2;


    heap1.insert(60, 5, "A");
    heap2.insert(60, 10, "B");
    heap1.insert(60, 15, "C");
    heap2.insert(60, 20, "D");
    heap1.insert(60, 20, "E");
    heap2.insert(60, 50, "F");

    Node* root1 = heap1.getroot();
    Node* root2 = heap2.getroot();

    PairingHeap merged;

    Node* mergedroot = merged.merge(root1, root2);
    merged.assignroot(mergedroot);





    while (merged.getroot() != nullptr)
    {
        Task extract = merged.extractMax();
        cout << extract.name << " " << extract.priority << endl;

    }


    //Insert and see if it merges properly with extractmax
    cout << "Merge test 2" << endl;
    cout << "" << endl;

    PairingHeap heap3;
    heap3.insert(60, 10, "A");
    heap3.insert(60, 20, "B");
    heap3.insert(60, 30, "C");
    heap3.insert(60, 40, "D");

    while (heap3.getroot() != nullptr)
    {
        Task extract = heap3.extractMax();
        cout << extract.name << " " << extract.priority << endl;
    }


    //Merge 3 differnet heaps together and see if the output is correct with extractMax
    cout << "Merge test 3" << endl;
    cout << "" << endl;
    PairingHeap heap4;
    PairingHeap heap5;
    PairingHeap heap6;
    heap4.insert(60, 10, "A");
    heap5.insert(60, 20, "B");
    heap6.insert(60, 30, "C");
    heap4.insert(60, 40, "D");
    heap5.insert(60, 50, "E");
    heap6.insert(60, 60, "F");

    Node* root3 = heap4.getroot();
    Node* root4 = heap5.getroot();
    Node* root5 = heap6.getroot();

    PairingHeap merged2;

    Node* merger2 = merged2.merge(root3, root4);
    Node* mergerroot3 = merged2.merge(merger2, root5);

    merged2.assignroot(mergerroot3);
    while (merged2.getroot() != nullptr)
    {
        Task extract = merged2.extractMax();
        cout << extract.name << " " << extract.priority << endl;

    }
}

int main()
{
    //Check insert of Pairing Heap
    PairingInsertchecker(); //Insert of Pairing Heap works

    PairingMergeTester(); //This works

    //The Pairing heap works as intended

}














