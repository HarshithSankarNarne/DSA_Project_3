#ifndef MAXHEAP_H
#define MAXHEAP_H
#include <vector>
#include "Task.h"
using namespace std;

class MaxHeap{
    //Array-based implementation
    //insert, extract, find, benchmark using chrono
    //Priority is at the top
    //Large number on top
private:
    int size=0; //getting passed in by Parham in Main.cpp
    //We need to create an array
    vector<Task> heap;

public:
    //Insert
    //heapify up
    //extractmax
    //find
    void insert(Task task);
    //size_t for indexing: https://stackoverflow.com/questions/76305089/how-to-fix-no-viable-conversion-from-stdvectorint-stdallocatorinti
    void heapifyUp(vector<Task>::size_type taskIndex); //helper for insert
    void heapifyDown(vector<Task>::size_type num); //helper for extractMax
    Task extractMax();
    Task peek();
    void clear();




};



#endif //MAXHEAP_H
