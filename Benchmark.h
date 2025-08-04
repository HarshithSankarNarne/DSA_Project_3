#pragma once
#include <string>
#include <map>
#include <chrono>
#include <unordered_map>
#include <vector>
#include "PairingHeap.h"
#include "MaxHeap.h"
#include "Task.h"

class Benchmark {
    std::unordered_map<long int, Task> dataset;
    std::vector<long int> deletedTasks;
    // csv operations: add auto, add manual, remove, timer set, timer reset, dataset resize, dataset type, verbosity, min priority set, max priority set, end
    std::vector<std::vector<std::string>> CSVData = {{"Operation", "Quantity", "Timer", "MaxHeap Time Taken", "Pairing Heap Time Taken", "MaxHeap Timer Sum", "Pairing Heap Timer Sum"}};
    MaxHeap maxHeap;
    PairingHeap pairingHeap;
    long int counter = 0;
    long int IDCounter = 0;
    // default values for data generation
    long int datasetMaxSize = 100000;
    long int minPriority = 0;
    long int maxPriority = 100000;
    int datasetType = 0;    // 0 is random, 1 is ascending, 2 is descending
    bool verbosity = false;
    bool timerOn = true;
    std::chrono::duration<unsigned long long, std::nano> maxHeapTime = std::chrono::nanoseconds::zero();
    std::chrono::duration<unsigned long long, std::nano> pairHeapTime = std::chrono::nanoseconds::zero();
    const long int MIN_MIN_PRIORITY = 0;
    const long int MAX_MAX_PRIORITY = 10000000;
    const long int MIN_STRING_LENGTH = 0;
    const long int MAX_STRING_LENGTH = 50;
    const long int MAX_MAX_DATASET_SIZE = 10000000;

public:
    static long int getNumber(std::string& info, long int low, long int high);
    static std::string getString(std::string& info, long int low, long int high);
    std::pair<std::chrono::duration<unsigned long long, std::nano>,std::chrono::duration<unsigned long long, std::nano>> generateTasks(long int number);
    std::pair<std::chrono::duration<unsigned long long, std::nano>,std::chrono::duration<unsigned long long, std::nano>> generateTasksManual(long int number);
    std::pair<std::chrono::duration<unsigned long long, std::nano>,std::chrono::duration<unsigned long long, std::nano>> removeTasks(long int number);
    void resetTime();
    void resetDataset();
    void writeCSV();
    //TODO: add data to csv files
    void setSize(long int size);
    void setType(int type);
    void setVerbosity(bool verbosity);
    void setTimer(bool timer);
    void setMinPriority(long int priority);
    void setMaxPriority(long int priority);
    long int getSize() { return datasetMaxSize;}
    std::string getType();
    bool getVerbosity() { return verbosity; }
    bool getTimer() { return timerOn; }
    unsigned long long getMaxHeapTime() { return maxHeapTime.count(); }
    unsigned long long getPairHeapTime() { return pairHeapTime.count(); }
    long int getMinPriority() { return minPriority; }
    long int getMaxPriority() { return maxPriority; }
    long int getMinMinPriority() const { return MIN_MIN_PRIORITY; }
    long int getMaxMaxPriority() const { return MAX_MAX_PRIORITY; }
    long int getMinStringLength() const { return MIN_STRING_LENGTH; }
    long int getMaxStringLength() const { return MAX_STRING_LENGTH; }
    long int getDataSize() { return counter; }
    long int getMaxMaxDatasetSize() const { return MAX_MAX_DATASET_SIZE; }
    void printCurrentTime();
};



