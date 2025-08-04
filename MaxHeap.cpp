#include "MaxHeap.h"
#include <vector>
#include "Task.h"
using namespace std;

void MaxHeap::insert(Task task) {
    if(heap.size()==0) {
        heap.push_back(task);
    }
    else {
        heap.push_back(task);
        heapifyUp(heap.size()-1);
    }
};

void MaxHeap::heapifyUp(vector<Task>::size_type taskIndex) {
    vector<Task>::size_type parentIndex = (taskIndex-1)/2;
    if(taskIndex ==0 || heap[parentIndex].priority >= heap[taskIndex].priority) {
        return;
    }
    else {
        swap(heap[taskIndex], heap[parentIndex]);
        heapifyUp(parentIndex);
    };

};

//Understanding heapifyDown: https://www.geeksforgeeks.org/dsa/introduction-to-max-heap-data-structure/
void MaxHeap::heapifyDown(vector<Task>::size_type num) {
    vector<Task>::size_type left = 2 * num + 1;
    vector<Task>::size_type right= 2 * num + 2;
    vector<Task>::size_type biggest = num;
    if(left < heap.size() && heap[left].priority > heap[biggest].priority) {
        biggest = left;
    }
    if(right < heap.size() && heap[right].priority > heap[biggest].priority) {
        biggest = right;
    }
    if (biggest != num) {
        swap(heap[num], heap[biggest]);
        heapifyDown(biggest);
    }

};

Task MaxHeap::extractMax() {
    if(heap.size()==0) {
        Task emptyTask{-1, -1, "null"};
        return emptyTask;
        }
    vector<Task>::size_type zero = 0;
    Task returnVal = heap[zero];
    heap[zero]=heap.back();
    heap.pop_back();
    if(heap.size()!=0) {
        heapifyDown(0);
    }


    return returnVal;
};

Task MaxHeap::peek() {
    if(heap.size()==0) {
        Task emptyTask{-1, -1, "null"};
        return emptyTask;
    }
    vector<Task>::size_type zero = 0;
    return heap[zero];
};

void MaxHeap::clear() {
    while(heap.size() != 0) {
        extractMax();
    }
};


