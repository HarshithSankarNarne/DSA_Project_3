#include "Benchmark.h"
#include <random>

bool Benchmark::checkSpace(long int number) {
    long int remainingSpace = datasetMaxSize - static_cast<long int>(dataset.size()) - number;
    if (remainingSpace >= 0) {
        return true;
    }
    return false;
}

void Benchmark::generateTasks(long int number) {
    if (datasetType == 0) {         // random
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<long int> dist(0, 10000000);
        for (long int i = 0; i < number; i++) {
            dataset[counter] = Task(dist(gen), dist(gen), "Dummy Task " + std::to_string(counter));
            counter++;
        }
    }
    else if (datasetType == 1) {    // ascending
        for (long int i = 0; i < number; i++) {
            dataset[counter] = Task(counter, counter, "Dummy Task " + std::to_string(counter));
            counter++;
        }
    }
    else if (datasetType == 2) {    // descending
        for (long int i = 0; i < number; i++) {
            dataset[counter] = Task(counter + number - i - 1, counter + number - i - 1, "Dummy Task " + std::to_string(counter + number - i - 1));
            counter++;
        }
    }
//TODO: add tasks to heaps
}

void Benchmark::generateTasks(long int priority, std::string& name) {
    dataset[counter] = Task(counter, priority, name);
//TODO: add task to heaps
}

void Benchmark::removeTasks() {

}
