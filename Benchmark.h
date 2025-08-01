#pragma once
#include <string>
#include <map>
#include <chrono>
#include <unordered_map>
#include "Task.h"

class Benchmark {
    std::unordered_map<unsigned long long, Task> dataset;
    unsigned long long counter = 0;
    // default values for data generation
    unsigned long long datasetSize = 100000;
    int datasetType = 0;    // 0 is random, 1 is ascending, 2 is descending
    bool verbosity = false;
    bool timerOn = false;
    auto maxHeapTime = std::chrono::duration<long long, std::chrono::nanoseconds>(0);
    auto pairHeapTime = std::chrono::duration<long long, std::chrono::nanoseconds>(0);

public:
    void generateTasks();
    void insertTasks();
    void removeTasks();
    void setSize(unsigned long long size) : datasetSize(size) {}
    void setType(int type) : datasetType(type) {}
    void setVerbosity(bool verbosity) : verbosity(verbosity) {}
    void setTimer(bool timer) : timerOn(timer) {}
};



