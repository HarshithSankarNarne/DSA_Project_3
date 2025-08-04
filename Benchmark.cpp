#include "Benchmark.h"
#include <iomanip>
#include <iostream>
#include <random>

long int Benchmark::getNumber(std::string& info, long int low, long int high) {
    std::string input;
    int output = -1;
    bool validInput = false;
    while (!validInput) {
        std::cout << info;
        getline(std::cin, input);
        std::cout << "\n" << std::endl;
        try {
            output = stoi(input);
        }
        catch (...) {
            std::cout << "Please enter a valid input\n" << std::endl;
            continue;
        }
        if (low <= output && output <= high) {
            validInput = true;
        }
        else {
            std::cout << "Please select a valid number between " + std::to_string(low) + " and " + std::to_string(high) + ".\n" << std::endl;
        }
    }
    return output;
}

std::string Benchmark::getString(std::string& info, long int low, long int high) {
    std::string input;
    std::string output;
    bool validInput = false;
    while (!validInput) {
        std::cout << info;
        getline(std::cin, input);
        std::cout << "\n" << std::endl;
        if (low <= output.length() && output.length() <= high) {
            validInput = true;
        }
        else {
            std::cout << "Please enter a string consisting of between " + std::to_string(low) + " and " + std::to_string(high) + " characters.\n" << std::endl;
        }
    }
    return output;
}


void Benchmark::generateTasks(long int number) {
    // create the task objects and prepare them for adding
    if (datasetType == 0) {         // random
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<long int> dist(MIN_PRIORITY, MAX_PRIORITY);
        for (long int i = 0; i < number; i++) {
            dataset[IDCounter] = Task(IDCounter, dist(gen), "Dummy Task " + std::to_string(IDCounter));
            counter++; IDCounter++;
        }
    }
    else if (datasetType == 1) {    // ascending
        for (long int i = 0; i < number; i++) {
            dataset[IDCounter] = Task(IDCounter, counter, "Dummy Task " + std::to_string(IDCounter));
            counter++; IDCounter++;
        }
    }
    else if (datasetType == 2) {    // descending
        for (long int i = 0; i < number; i++) {
            dataset[IDCounter] = Task(IDCounter, counter + number - i - 1, "Dummy Task " + std::to_string(IDCounter));
            counter++; IDCounter++;
        }
    }

    if (timerOn) {
        if (verbosity) {            // timer on, verbose
            auto maxStartTime = std::chrono::high_resolution_clock::now();
            for (long int i = IDCounter - number; i < IDCounter; i++) {
                maxHeap.insert(dataset[i]);
            }
            auto maxEndTime = std::chrono::high_resolution_clock::now();
            auto pairingStartTime = std::chrono::high_resolution_clock::now();
            for (long int i = IDCounter - number; i < IDCounter; i++) {
                pairingHeap.insert(dataset[i]);
            }
            auto pairingEndTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<unsigned long long, std::nano> maxInsertTime = maxEndTime - maxStartTime;
            std::chrono::duration<unsigned long long, std::nano> pairingInsertTime = pairingEndTime - pairingStartTime;
            maxHeapTime += maxInsertTime;
            pairHeapTime += pairingInsertTime;
            std::cout << "| " << "    ID    " << " | " << " Priority " << " | " << std::left << std::setw(50) << "Name" << " |\n";
            std::cout << std::setfill('-') << std::setw(80) << "\n";
            for (long int i = IDCounter - number; i < IDCounter; i++) {
                std::cout << "| " << std::right << std::setw(10) << dataset[i].ID << " | " << std::right << std::setw(10) << dataset[i].priority << " | " << std::left << std::setw(50) << dataset[i].name << " |\n";
            }
            std::cout << std::endl;
            std::cout << "Timer ON\n";
            std::cout << "MaxHeap completed in " + maxInsertTime.count() << " nanoseconds\n";
            std::cout << "Pairing Heap completed in " + pairingInsertTime.count() << " nanoseconds\n" << std::endl;
        }
        else {                      // timer on, non-verbose
            auto maxStartTime = std::chrono::high_resolution_clock::now();
            for (long int i = IDCounter - number; i < IDCounter; i++) {
                maxHeap.insert(dataset[i]);
            }
            auto maxEndTime = std::chrono::high_resolution_clock::now();
            auto pairingStartTime = std::chrono::high_resolution_clock::now();
            for (long int i = IDCounter - number; i < IDCounter; i++) {
                pairingHeap.insert(dataset[i]);
            }
            auto pairingEndTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<unsigned long long, std::nano> maxInsertTime = maxEndTime - maxStartTime;
            std::chrono::duration<unsigned long long, std::nano> pairingInsertTime = pairingEndTime - pairingStartTime;
            maxHeapTime += maxInsertTime;
            pairHeapTime += pairingInsertTime;
            std::cout << "Timer ON\n";
            std::cout << "MaxHeap completed in " + maxInsertTime.count() << " nanoseconds\n";
            std::cout << "Pairing Heap completed in " + pairingInsertTime.count() << " nanoseconds\n" << std::endl;
        }
    }
    else {
        if (verbosity) {            // timer off, verbose
            auto maxStartTime = std::chrono::high_resolution_clock::now();
            for (long int i = IDCounter - number; i < IDCounter; i++) {
                maxHeap.insert(dataset[i]);
            }
            auto maxEndTime = std::chrono::high_resolution_clock::now();
            auto pairingStartTime = std::chrono::high_resolution_clock::now();
            for (long int i = IDCounter - number; i < IDCounter; i++) {
                pairingHeap.insert(dataset[i]);
            }
            auto pairingEndTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<unsigned long long, std::nano> maxInsertTime = maxEndTime - maxStartTime;
            std::chrono::duration<unsigned long long, std::nano> pairingInsertTime = pairingEndTime - pairingStartTime;
            std::cout << "| " << "    ID    " << " | " << " Priority " << " | " << std::left << std::setw(50) << "Name" << " |\n";
            std::cout << std::setfill('-') << std::setw(80) << "\n";
            for (long int i = IDCounter - number; i < IDCounter; i++) {
                std::cout << "| " << std::right << std::setw(10) << dataset[i].ID << " | " << std::right << std::setw(10) << dataset[i].priority << " | " << std::left << std::setw(50) << dataset[i].name << " |\n";
            }
            std::cout << std::endl;
            std::cout << "Timer OFF\n";
            std::cout << "MaxHeap completed in " + maxInsertTime.count() << " nanoseconds\n";
            std::cout << "Pairing Heap completed in " + pairingInsertTime.count() << " nanoseconds\n" << std::endl;
        }
        else {                      // timer off, non-verbose
            auto maxStartTime = std::chrono::high_resolution_clock::now();
            for (long int i = IDCounter - number; i < IDCounter; i++) {
                maxHeap.insert(dataset[i]);
            }
            auto maxEndTime = std::chrono::high_resolution_clock::now();
            auto pairingStartTime = std::chrono::high_resolution_clock::now();
            for (long int i = IDCounter - number; i < IDCounter; i++) {
                pairingHeap.insert(dataset[i]);
            }
            auto pairingEndTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<unsigned long long, std::nano> maxInsertTime = maxEndTime - maxStartTime;
            std::chrono::duration<unsigned long long, std::nano> pairingInsertTime = pairingEndTime - pairingStartTime;
            std::cout << "Timer OFF\n";
            std::cout << "MaxHeap completed in " + maxInsertTime.count() << " nanoseconds\n";
            std::cout << "Pairing Heap completed in " + pairingInsertTime.count() << " nanoseconds\n" << std::endl;
        }
    }
}

void Benchmark::generateTasksManual(long int number) {
    std::cout << "Manual Task Entry: Enter the priority and name for each task you wish to add.\nPriority: May range from " + std::to_string(MIN_PRIORITY) + " (lowest priority) to " + std::to_string(MAX_PRIORITY) + " (highest priority)\nName: May range from " + std::to_string(MIN_STRING_LENGTH) + " to " + std::to_string(MAX_STRING_LENGTH) + " characters\n";
    for (long int i = 0; i < number; i++) {
        std::string priorityInfo = "Enter Task ID " + std::to_string(IDCounter) + "'s Priority (" + std::to_string(MIN_PRIORITY) + "-" + std::to_string(MAX_PRIORITY) + "): ";
        std::string nameInfo = "Enter Task ID " + std::to_string(IDCounter) + "'s Name (" + std::to_string(MIN_STRING_LENGTH) + "-" + std::to_string(MAX_STRING_LENGTH) + " characters): ";
        dataset[IDCounter] = Task(IDCounter, getNumber(priorityInfo, MIN_PRIORITY, MAX_PRIORITY), getString(nameInfo, MIN_STRING_LENGTH, MAX_STRING_LENGTH));
        counter++; IDCounter++;
    }

    if (timerOn) {
        if (verbosity) {            // timer on, verbose
            auto maxStartTime = std::chrono::high_resolution_clock::now();
            for (long int i = IDCounter - number; i < IDCounter; i++) {
                maxHeap.insert(dataset[i]);
            }
            auto maxEndTime = std::chrono::high_resolution_clock::now();
            auto pairingStartTime = std::chrono::high_resolution_clock::now();
            for (long int i = IDCounter - number; i < IDCounter; i++) {
                pairingHeap.insert(dataset[i]);
            }
            auto pairingEndTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<unsigned long long, std::nano> maxInsertTime = maxEndTime - maxStartTime;
            std::chrono::duration<unsigned long long, std::nano> pairingInsertTime = pairingEndTime - pairingStartTime;
            maxHeapTime += maxInsertTime;
            pairHeapTime += pairingInsertTime;
            std::cout << "| " << "    ID    " << " | " << " Priority " << " | " << std::left << std::setw(50) << "Name" << " |\n";
            std::cout << std::setfill('-') << std::setw(80) << "\n";
            for (long int i = IDCounter - number; i < IDCounter; i++) {
                std::cout << "| " << std::right << std::setw(10) << dataset[i].ID << " | " << std::right << std::setw(10) << dataset[i].priority << " | " << std::left << std::setw(50) << dataset[i].name << " |\n";
            }
            std::cout << std::endl;
            std::cout << "Timer ON\n";
            std::cout << "MaxHeap completed in " + maxInsertTime.count() << " nanoseconds\n";
            std::cout << "Pairing Heap completed in " + pairingInsertTime.count() << " nanoseconds\n" << std::endl;
        }
        else {                      // timer on, non-verbose
            auto maxStartTime = std::chrono::high_resolution_clock::now();
            for (long int i = IDCounter - number; i < IDCounter; i++) {
                maxHeap.insert(dataset[i]);
            }
            auto maxEndTime = std::chrono::high_resolution_clock::now();
            auto pairingStartTime = std::chrono::high_resolution_clock::now();
            for (long int i = IDCounter - number; i < IDCounter; i++) {
                pairingHeap.insert(dataset[i]);
            }
            auto pairingEndTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<unsigned long long, std::nano> maxInsertTime = maxEndTime - maxStartTime;
            std::chrono::duration<unsigned long long, std::nano> pairingInsertTime = pairingEndTime - pairingStartTime;
            maxHeapTime += maxInsertTime;
            pairHeapTime += pairingInsertTime;
            std::cout << "Timer ON\n";
            std::cout << "MaxHeap completed in " + maxInsertTime.count() << " nanoseconds\n";
            std::cout << "Pairing Heap completed in " + pairingInsertTime.count() << " nanoseconds\n" << std::endl;
        }
    }
    else {
        if (verbosity) {            // timer off, verbose
            auto maxStartTime = std::chrono::high_resolution_clock::now();
            for (long int i = IDCounter - number; i < IDCounter; i++) {
                maxHeap.insert(dataset[i]);
            }
            auto maxEndTime = std::chrono::high_resolution_clock::now();
            auto pairingStartTime = std::chrono::high_resolution_clock::now();
            for (long int i = IDCounter - number; i < IDCounter; i++) {
                pairingHeap.insert(dataset[i]);
            }
            auto pairingEndTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<unsigned long long, std::nano> maxInsertTime = maxEndTime - maxStartTime;
            std::chrono::duration<unsigned long long, std::nano> pairingInsertTime = pairingEndTime - pairingStartTime;
            std::cout << "| " << "    ID    " << " | " << " Priority " << " | " << std::left << std::setw(50) << "Name" << " |\n";
            std::cout << std::setfill('-') << std::setw(80) << "\n";
            for (long int i = IDCounter - number; i < IDCounter; i++) {
                std::cout << "| " << std::right << std::setw(10) << dataset[i].ID << " | " << std::right << std::setw(10) << dataset[i].priority << " | " << std::left << std::setw(50) << dataset[i].name << " |\n";
            }
            std::cout << std::endl;
            std::cout << "Timer OFF\n";
            std::cout << "MaxHeap completed in " + maxInsertTime.count() << " nanoseconds\n";
            std::cout << "Pairing Heap completed in " + pairingInsertTime.count() << " nanoseconds\n" << std::endl;
        }
        else {                      // timer off, non-verbose
            auto maxStartTime = std::chrono::high_resolution_clock::now();
            for (long int i = IDCounter - number; i < IDCounter; i++) {
                maxHeap.insert(dataset[i]);
            }
            auto maxEndTime = std::chrono::high_resolution_clock::now();
            auto pairingStartTime = std::chrono::high_resolution_clock::now();
            for (long int i = IDCounter - number; i < IDCounter; i++) {
                pairingHeap.insert(dataset[i]);
            }
            auto pairingEndTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<unsigned long long, std::nano> maxInsertTime = maxEndTime - maxStartTime;
            std::chrono::duration<unsigned long long, std::nano> pairingInsertTime = pairingEndTime - pairingStartTime;
            std::cout << "Timer OFF\n";
            std::cout << "MaxHeap completed in " + maxInsertTime.count() << " nanoseconds\n";
            std::cout << "Pairing Heap completed in " + pairingInsertTime.count() << " nanoseconds\n" << std::endl;
        }
    }
}

void Benchmark::removeTasks(long int number) {
    if (timerOn) {
        if (verbosity) {            // timer on, verbose
            std::chrono::duration<unsigned long long, std::nano> maxRemoveTime(0);
            std::chrono::duration<unsigned long long, std::nano> pairingRemoveTime(0);
            std::cout << "| " << "    ID    " << " | " << " Priority " << " | " << std::left << std::setw(50) << "Name" << " |\n";
            std::cout << std::setfill('-') << std::setw(80) << "\n";
            for (long int i = 0; i < number; i++) {
                deletedTasks.push_back(maxHeap.peek().ID);
                auto maxStartTime = std::chrono::high_resolution_clock::now();
                Task extracted = maxHeap.extract();
                auto maxEndTime = std::chrono::high_resolution_clock::now();
                maxRemoveTime += maxEndTime - maxStartTime;
            }
            for (long int i = 0; i < number; i++) {
                auto pairingStartTime = std::chrono::high_resolution_clock::now();
                Task extracted = pairingHeap.extract();
                auto pairingEndTime = std::chrono::high_resolution_clock::now();
                pairingRemoveTime += pairingEndTime - pairingStartTime;
                std::cout << "| " << std::right << std::setw(10) << extracted.ID << " | " << std::right << std::setw(10) << extracted.priority << " | " << std::left << std::setw(50) << extracted.name << " |\n";
            }
            std::cout << std::endl;
            maxHeapTime += maxRemoveTime;
            pairHeapTime += pairingRemoveTime;
            std::cout << "Timer ON\n";
            std::cout << "MaxHeap completed in " + maxRemoveTime.count() << " nanoseconds\n";
            std::cout << "Pairing Heap completed in " + pairingRemoveTime.count() << " nanoseconds\n" << std::endl;
        }
        else {                      // timer on, non-verbose
            std::chrono::duration<unsigned long long, std::nano> maxRemoveTime(0);
            std::chrono::duration<unsigned long long, std::nano> pairingRemoveTime(0);
            for (long int i = 0; i < number; i++) {
                deletedTasks.push_back(maxHeap.peek().ID);
                auto maxStartTime = std::chrono::high_resolution_clock::now();
                Task extracted = maxHeap.extract();
                auto maxEndTime = std::chrono::high_resolution_clock::now();
                maxRemoveTime += maxEndTime - maxStartTime;
            }
            for (long int i = 0; i < number; i++) {
                auto pairingStartTime = std::chrono::high_resolution_clock::now();
                Task extracted = pairingHeap.extract();
                auto pairingEndTime = std::chrono::high_resolution_clock::now();
                pairingRemoveTime += pairingEndTime - pairingStartTime;
            }
            maxHeapTime += maxRemoveTime;
            pairHeapTime += pairingRemoveTime;
            std::cout << "Timer ON\n";
            std::cout << "MaxHeap completed in " + maxRemoveTime.count() << " nanoseconds\n";
            std::cout << "Pairing Heap completed in " + pairingRemoveTime.count() << " nanoseconds\n" << std::endl;
        }
    }
    else {
        if (verbosity) {            // timer off, verbose
            std::chrono::duration<unsigned long long, std::nano> maxRemoveTime(0);
            std::chrono::duration<unsigned long long, std::nano> pairingRemoveTime(0);
            std::cout << "| " << "    ID    " << " | " << " Priority " << " | " << std::left << std::setw(50) << "Name" << " |\n";
            std::cout << std::setfill('-') << std::setw(80) << "\n";
            for (long int i = 0; i < number; i++) {
                deletedTasks.push_back(maxHeap.peek().ID);
                auto maxStartTime = std::chrono::high_resolution_clock::now();
                Task extracted = maxHeap.extract();
                auto maxEndTime = std::chrono::high_resolution_clock::now();
                maxRemoveTime += maxEndTime - maxStartTime;
            }
            for (long int i = 0; i < number; i++) {
                auto pairingStartTime = std::chrono::high_resolution_clock::now();
                Task extracted = pairingHeap.extract();
                auto pairingEndTime = std::chrono::high_resolution_clock::now();
                pairingRemoveTime += pairingEndTime - pairingStartTime;
                std::cout << "| " << std::right << std::setw(10) << extracted.ID << " | " << std::right << std::setw(10) << extracted.priority << " | " << std::left << std::setw(50) << extracted.name << " |\n";
            }
            std::cout << std::endl;
            std::cout << "Timer OFF\n";
            std::cout << "MaxHeap completed in " + maxRemoveTime.count() << " nanoseconds\n";
            std::cout << "Pairing Heap completed in " + pairingRemoveTime.count() << " nanoseconds\n" << std::endl;
        }
        else {                      // timer off, non-verbose
            std::chrono::duration<unsigned long long, std::nano> maxRemoveTime(0);
            std::chrono::duration<unsigned long long, std::nano> pairingRemoveTime(0);
            for (long int i = 0; i < number; i++) {
                deletedTasks.push_back(maxHeap.peek().ID);
                auto maxStartTime = std::chrono::high_resolution_clock::now();
                Task extracted = maxHeap.extract();
                auto maxEndTime = std::chrono::high_resolution_clock::now();
                maxRemoveTime += maxEndTime - maxStartTime;
            }
            for (long int i = 0; i < number; i++) {
                auto pairingStartTime = std::chrono::high_resolution_clock::now();
                Task extracted = pairingHeap.extract();
                auto pairingEndTime = std::chrono::high_resolution_clock::now();
                pairingRemoveTime += pairingEndTime - pairingStartTime;
            }
            std::cout << "Timer OFF\n";
            std::cout << "MaxHeap completed in " + maxRemoveTime.count() << " nanoseconds\n";
            std::cout << "Pairing Heap completed in " + pairingRemoveTime.count() << " nanoseconds\n" << std::endl;
        }
    }
}

void Benchmark::resetTime() {
    std::cout << "Resetting time...\n";
    maxHeapTime = 0;
    pairHeapTime = 0;
}

void Benchmark::resetDataset() {
    std::cout << "Resetting dataset...\n";
    dataset.clear();
    deletedTasks.clear();
    maxHeap.clear();
    pairingHeap.clear();
    counter = 0;
    IDCounter = 0;
    maxHeapTime = 0;
    pairHeapTime = 0;
    std::string verbosityString = verbosity ? "True" : "False";
    std::string timerString = timerOn ? "On" : "Off";
    std::cout << "Creating new dataset with the selected options:\nMax Size: " + std::to_string(getSize()) + "\nType: " + getType() + "\nVerbosity: " + verbosityString + "\nTimer: " + timerString + "\nDataset created.\n" << std::endl;
}

std::string Benchmark::getType() {
    if (datasetType == 0) {
        return "Random";
    }
    else if (datasetType == 1) {
        return "Ascending";
    }
    else if (datasetType == 2) {
        return "Descending";
    }
    else {
        return "Unknown";
    }
}

void Benchmark::printCurrentTime() {
    std::cout << "Current time:\nMaxHeap completed in " + std::to_string(getMaxHeapTime()) + " nanoseconds.\nPairing Heap completed in " + std::to_string(getPairHeapTime()) + " nanoseconds\n" << std::endl;
}
