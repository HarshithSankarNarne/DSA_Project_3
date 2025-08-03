#pragma once
#include <string>
#include <map>
#include <chrono>
#include <unordered_map>
#include "PairingHeap.h"
#include "MaxHeap.h"
#include "Task.h"

class Benchmark {
    std::unordered_map<long int, Task> dataset;
    PairingHeap pairingHeap;
    MaxHeap maxHeap;
    long int counter = 0;
    long int IDCounter = 0;
    // default values for data generation
    long int datasetMaxSize = 100000;
    int datasetType = 0;    // 0 is random, 1 is ascending, 2 is descending
    bool verbosity = false;
    bool timerOn = false;
    auto maxHeapTime = std::chrono::duration<unsigned long long, std::nano>(0);
    auto pairHeapTime = std::chrono::duration<unsigned long long, std::nano>(0);
    const long int MIN_PRIORITY = 0;
    const long int MAX_PRIORITY = 10000000;
    const long int MIN_STRING_LENGTH = 0;
    const long int MAX_STRING_LENGTH = 50;

public:
    static long int getNumber(std::string& info, long int low, long int high);
    static std::string getString(std::string& info, long int low, long int high);
    void generateTasks(long int number);
    void generateTasksManual(long int number);
    void removeTasks();
    //TODO: add data to csv files
    void setSize(long int size) : datasetMaxSize(size) {}
    void setType(int type) : datasetType(type) {}
    void setVerbosity(bool verbosity) : verbosity(verbosity) {}
    void setTimer(bool timer) : timerOn(timer) {}
    long int getSize() { return datasetMaxSize;}
    long int getType() { return datasetType; }
    bool getVerbosity() { return verbosity; }
    bool getTimer() { return timerOn; }
    unsigned long long getMaxHeapTime() { return maxHeapTime.count(); }
    unsigned long long getPairHeapTime() { return pairHeapTime.count(); }
    long int getDataSize() { return static_cast<long int>(dataset.size()); }
};



