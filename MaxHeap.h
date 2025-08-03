//
// Created by Harshith Sankar Narne on 8/3/25.
//

#ifndef MAXHEAP_H
#define MAXHEAP_H



class MaxHeap {
    //Array-based implementation
    //insert, extract, find, benchmark using chrono
    //Priority is at the top
    //Large number on top
private:
    int size; //getting passed in by Parham in Main.cpp
    //We need to create an array
    vector<Task> heap;

public:
    //Insert
    //heapify up
    //extractmax
    //find
    void insertHeap(Task* task)
    {
        if (arr.size() == 0)
        {
            heap.push_back(task);
        }
        for (int i = 0; i < heap.size() - 1; i++)
        {
            if (task.priority > heap[i].priority )
        }
    }



};



#endif //MAXHEAP_H
