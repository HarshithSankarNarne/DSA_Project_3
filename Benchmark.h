#pragma once
#include <string>
#include <map>
#include <chrono>
#include <unordered_map>
#include "Task.h"

class Benchmark {
    std::unordered_map<long int, Task> dataset;
    long int counter = 0;
    // default values for data generation
    long int datasetMaxSize = 100000;
    int datasetType = 0;    // 0 is random, 1 is ascending, 2 is descending
    bool verbosity = false;
    bool timerOn = false;
    auto maxHeapTime = std::chrono::duration<long int, std::chrono::nanoseconds>(0);
    auto pairHeapTime = std::chrono::duration<long int, std::chrono::nanoseconds>(0);

public:
    bool checkSpace(long int number);
    void generateTasks(long int number);
    void generateTasks(long int priority, std::string& name);
    void removeTasks();
    void setSize(long int size) : datasetMaxSize(size) {}
    void setType(int type) : datasetType(type) {}
    void setVerbosity(bool verbosity) : verbosity(verbosity) {}
    void setTimer(bool timer) : timerOn(timer) {}
    long int getSize() { return datasetMaxSize;}
    long int getType() { return datasetType; }
    bool getVerbosity() { return verbosity; }
    bool getTimer() { return timerOn; }
    long int getDataSize() { return static_cast<long int>(dataset.size()); }
};



