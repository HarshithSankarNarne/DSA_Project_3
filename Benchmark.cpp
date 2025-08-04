#include "Benchmark.h"
#include <iomanip>
#include <iostream>
#include <random>
#include <fstream>
#include <sstream>


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
        if (low <= static_cast<long int>(output.length()) && static_cast<long int>(output.length()) <= high) {
            validInput = true;
        }
        else {
            std::cout << "Please enter a string consisting of between " + std::to_string(low) + " and " + std::to_string(high) + " characters.\n" << std::endl;
        }
    }
    return output;
}


std::pair<std::chrono::duration<unsigned long long, std::nano>,std::chrono::duration<unsigned long long, std::nano>> Benchmark::generateTasks(long int number) {
    // create the task objects and prepare them for adding
    if (datasetType == 0) {         // random
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<long int> dist(minPriority, maxPriority);
        for (long int i = 0; i < number; i++) {
            dataset[IDCounter] = Task(IDCounter, dist(gen), "Dummy Task " + std::to_string(IDCounter));
            counter++; IDCounter++;
        }
    }
    else if (datasetType == 1) {    // ascending
        for (long int i = 0; i < number; i++) {
            long int taskPriority = minPriority + i < maxPriority ? minPriority + i : maxPriority;
            dataset[IDCounter] = Task(IDCounter, taskPriority, "Dummy Task " + std::to_string(IDCounter));
            counter++; IDCounter++;
        }
    }
    else if (datasetType == 2) {    // descending
        for (long int i = 0; i < number; i++) {
            long int taskPriority = maxPriority - i > minPriority ? maxPriority - i : minPriority;
            dataset[IDCounter] = Task(IDCounter, taskPriority, "Dummy Task " + std::to_string(IDCounter));
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
                pairingHeap.insert(dataset[i].ID, dataset[i].priority, dataset[i].name);
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
            CSVData.emplace_back(std::vector<std::string>({"add auto", std::to_string(number), std::to_string(timerOn), std::to_string(maxInsertTime.count()), std::to_string(pairingInsertTime.count()), std::to_string(maxHeapTime.count()), std::to_string(pairHeapTime.count())}));
            std::cout << "Timer ON\n";
            std::cout << std::to_string(number) + " tasks added.\n";
            std::cout << "MaxHeap completed in " + std::to_string(maxInsertTime.count())<< " nanoseconds\n";
            std::cout << "Pairing Heap completed in " + std::to_string(pairingInsertTime.count()) << " nanoseconds\n" << std::endl;
            return std::pair<std::chrono::duration<unsigned long long, std::nano>,std::chrono::duration<unsigned long long, std::nano>>(maxInsertTime, pairingInsertTime);
        }
        else {                      // timer on, non-verbose
            auto maxStartTime = std::chrono::high_resolution_clock::now();
            for (long int i = IDCounter - number; i < IDCounter; i++) {
                maxHeap.insert(dataset[i]);
            }
            auto maxEndTime = std::chrono::high_resolution_clock::now();
            auto pairingStartTime = std::chrono::high_resolution_clock::now();
            for (long int i = IDCounter - number; i < IDCounter; i++) {
                pairingHeap.insert(dataset[i].ID, dataset[i].priority, dataset[i].name);
            }
            auto pairingEndTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<unsigned long long, std::nano> maxInsertTime = maxEndTime - maxStartTime;
            std::chrono::duration<unsigned long long, std::nano> pairingInsertTime = pairingEndTime - pairingStartTime;
            maxHeapTime += maxInsertTime;
            pairHeapTime += pairingInsertTime;
            CSVData.emplace_back(std::vector<std::string>({"add auto", std::to_string(number), std::to_string(timerOn), std::to_string(maxInsertTime.count()), std::to_string(pairingInsertTime.count()), std::to_string(maxHeapTime.count()), std::to_string(pairHeapTime.count())}));
            std::cout << "Timer ON\n";
            std::cout << std::to_string(number) + " tasks added.\n";
            std::cout << "MaxHeap completed in " + std::to_string(maxInsertTime.count()) << " nanoseconds\n";
            std::cout << "Pairing Heap completed in " + to_string(pairingInsertTime.count()) << " nanoseconds\n" << std::endl;
            return std::pair<std::chrono::duration<unsigned long long, std::nano>,std::chrono::duration<unsigned long long, std::nano>>(maxInsertTime, pairingInsertTime);
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
                pairingHeap.insert(dataset[i].ID, dataset[i].priority, dataset[i].name);
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
            CSVData.emplace_back(std::vector<std::string>({"add auto", std::to_string(number), std::to_string(timerOn), std::to_string(maxInsertTime.count()), std::to_string(pairingInsertTime.count()), std::to_string(maxHeapTime.count()), std::to_string(pairHeapTime.count())}));
            std::cout << "Timer OFF\n";
            std::cout << std::to_string(number) + " tasks added.\n";
            std::cout << "MaxHeap completed in " + to_string(maxInsertTime.count()) << " nanoseconds\n";
            std::cout << "Pairing Heap completed in " + to_string(pairingInsertTime.count()) << " nanoseconds\n" << std::endl;
            return std::pair<std::chrono::duration<unsigned long long, std::nano>,std::chrono::duration<unsigned long long, std::nano>>(maxInsertTime, pairingInsertTime);
        }
        else {                      // timer off, non-verbose
            auto maxStartTime = std::chrono::high_resolution_clock::now();
            for (long int i = IDCounter - number; i < IDCounter; i++) {
                maxHeap.insert(dataset[i]);
            }
            auto maxEndTime = std::chrono::high_resolution_clock::now();
            auto pairingStartTime = std::chrono::high_resolution_clock::now();
            for (long int i = IDCounter - number; i < IDCounter; i++) {
                pairingHeap.insert(dataset[i].ID, dataset[i].priority, dataset[i].name);
            }
            auto pairingEndTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<unsigned long long, std::nano> maxInsertTime = maxEndTime - maxStartTime;
            std::chrono::duration<unsigned long long, std::nano> pairingInsertTime = pairingEndTime - pairingStartTime;
            CSVData.emplace_back(std::vector<std::string>({"add auto", std::to_string(number), std::to_string(timerOn), std::to_string(maxInsertTime.count()), std::to_string(pairingInsertTime.count()), std::to_string(maxHeapTime.count()), std::to_string(pairHeapTime.count())}));
            std::cout << "Timer OFF\n";
            std::cout << std::to_string(number) + " tasks added.\n";
            std::cout << "MaxHeap completed in " + to_string(maxInsertTime.count()) << " nanoseconds\n";
            std::cout << "Pairing Heap completed in " + to_string(pairingInsertTime.count()) << " nanoseconds\n" << std::endl;
            return std::pair<std::chrono::duration<unsigned long long, std::nano>,std::chrono::duration<unsigned long long, std::nano>>(maxInsertTime, pairingInsertTime);
        }
    }
}

std::pair<std::chrono::duration<unsigned long long, std::nano>,std::chrono::duration<unsigned long long, std::nano>> Benchmark::generateTasksManual(long int number) {
    std::cout << "Manual Task Entry: Enter the priority and name for each task you wish to add.\nPriority: May range from " + std::to_string(minPriority) + " (lowest priority) to " + std::to_string(maxPriority) + " (highest priority)\nName: May range from " + std::to_string(MIN_STRING_LENGTH) + " to " + std::to_string(MAX_STRING_LENGTH) + " characters\n";
    for (long int i = 0; i < number; i++) {
        std::string priorityInfo = "Enter Task ID " + std::to_string(IDCounter) + "'s Priority (" + std::to_string(minPriority) + "-" + std::to_string(maxPriority) + "): ";
        std::string nameInfo = "Enter Task ID " + std::to_string(IDCounter) + "'s Name (" + std::to_string(MIN_STRING_LENGTH) + "-" + std::to_string(MAX_STRING_LENGTH) + " characters): ";
        dataset[IDCounter] = Task(IDCounter, getNumber(priorityInfo, minPriority, maxPriority), getString(nameInfo, MIN_STRING_LENGTH, MAX_STRING_LENGTH));
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
                pairingHeap.insert(dataset[i].ID, dataset[i].priority, dataset[i].name);
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
            CSVData.emplace_back(std::vector<std::string>({"add manual", std::to_string(number), std::to_string(timerOn), std::to_string(maxInsertTime.count()), std::to_string(pairingInsertTime.count()), std::to_string(maxHeapTime.count()), std::to_string(pairHeapTime.count())}));
            std::cout << "Timer ON\n";
            std::cout << std::to_string(number) + " tasks added.\n";
            std::cout << "MaxHeap completed in " + to_string(maxInsertTime.count()) << " nanoseconds\n";
            std::cout << "Pairing Heap completed in " + to_string(pairingInsertTime.count()) << " nanoseconds\n" << std::endl;
            return std::pair<std::chrono::duration<unsigned long long, std::nano>,std::chrono::duration<unsigned long long, std::nano>>(maxInsertTime, pairingInsertTime);
        }
        else {                      // timer on, non-verbose
            auto maxStartTime = std::chrono::high_resolution_clock::now();
            for (long int i = IDCounter - number; i < IDCounter; i++) {
                maxHeap.insert(dataset[i]);
            }
            auto maxEndTime = std::chrono::high_resolution_clock::now();
            auto pairingStartTime = std::chrono::high_resolution_clock::now();
            for (long int i = IDCounter - number; i < IDCounter; i++) {
                pairingHeap.insert(dataset[i].ID, dataset[i].priority, dataset[i].name);
            }
            auto pairingEndTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<unsigned long long, std::nano> maxInsertTime = maxEndTime - maxStartTime;
            std::chrono::duration<unsigned long long, std::nano> pairingInsertTime = pairingEndTime - pairingStartTime;
            maxHeapTime += maxInsertTime;
            pairHeapTime += pairingInsertTime;
            CSVData.emplace_back(std::vector<std::string>({"add manual", std::to_string(number), std::to_string(timerOn), std::to_string(maxInsertTime.count()), std::to_string(pairingInsertTime.count()), std::to_string(maxHeapTime.count()), std::to_string(pairHeapTime.count())}));
            std::cout << "Timer ON\n";
            std::cout << std::to_string(number) + " tasks added.\n";
            std::cout << "MaxHeap completed in " + to_string(maxInsertTime.count()) << " nanoseconds\n";
            std::cout << "Pairing Heap completed in " + to_string(pairingInsertTime.count()) << " nanoseconds\n" << std::endl;
            return std::pair<std::chrono::duration<unsigned long long, std::nano>,std::chrono::duration<unsigned long long, std::nano>>(maxInsertTime, pairingInsertTime);
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
                pairingHeap.insert(dataset[i].ID, dataset[i].priority, dataset[i].name);
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
            CSVData.emplace_back(std::vector<std::string>({"add manual", std::to_string(number), std::to_string(timerOn), std::to_string(maxInsertTime.count()), std::to_string(pairingInsertTime.count()), std::to_string(maxHeapTime.count()), std::to_string(pairHeapTime.count())}));
            std::cout << "Timer OFF\n";
            std::cout << std::to_string(number) + " tasks added.\n";
            std::cout << "MaxHeap completed in " + to_string(maxInsertTime.count()) << " nanoseconds\n";
            std::cout << "Pairing Heap completed in " + to_string(pairingInsertTime.count()) << " nanoseconds\n" << std::endl;
            return std::pair<std::chrono::duration<unsigned long long, std::nano>,std::chrono::duration<unsigned long long, std::nano>>(maxInsertTime, pairingInsertTime);
        }
        else {                      // timer off, non-verbose
            auto maxStartTime = std::chrono::high_resolution_clock::now();
            for (long int i = IDCounter - number; i < IDCounter; i++) {
                maxHeap.insert(dataset[i]);
            }
            auto maxEndTime = std::chrono::high_resolution_clock::now();
            auto pairingStartTime = std::chrono::high_resolution_clock::now();
            for (long int i = IDCounter - number; i < IDCounter; i++) {
                pairingHeap.insert(dataset[i].ID, dataset[i].priority, dataset[i].name);
            }
            auto pairingEndTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<unsigned long long, std::nano> maxInsertTime = maxEndTime - maxStartTime;
            std::chrono::duration<unsigned long long, std::nano> pairingInsertTime = pairingEndTime - pairingStartTime;
            CSVData.emplace_back(std::vector<std::string>({"add manual", std::to_string(number), std::to_string(timerOn), std::to_string(maxInsertTime.count()), std::to_string(pairingInsertTime.count()), std::to_string(maxHeapTime.count()), std::to_string(pairHeapTime.count())}));
            std::cout << "Timer OFF\n";
            std::cout << std::to_string(number) + " tasks added.\n";
            std::cout << "MaxHeap completed in " + to_string(maxInsertTime.count()) << " nanoseconds\n";
            std::cout << "Pairing Heap completed in " + to_string(pairingInsertTime.count()) << " nanoseconds\n" << std::endl;
            return std::pair<std::chrono::duration<unsigned long long, std::nano>,std::chrono::duration<unsigned long long, std::nano>>(maxInsertTime, pairingInsertTime);
        }
    }
}

std::pair<std::chrono::duration<unsigned long long, std::nano>,std::chrono::duration<unsigned long long, std::nano>> Benchmark::removeTasks(long int number) {
    if (timerOn) {
        if (verbosity) {            // timer on, verbose
            std::chrono::duration<unsigned long long, std::nano> maxRemoveTime(0);
            std::chrono::duration<unsigned long long, std::nano> pairingRemoveTime(0);
            std::cout << "| " << "    ID    " << " | " << " Priority " << " | " << std::left << std::setw(50) << "Name" << " |\n";
            std::cout << std::setfill('-') << std::setw(80) << "\n";
            for (long int i = 0; i < number; i++) {
                deletedTasks.push_back(maxHeap.peek().ID);
                auto maxStartTime = std::chrono::high_resolution_clock::now();
                Task extracted = maxHeap.extractMax();
                auto maxEndTime = std::chrono::high_resolution_clock::now();
                maxRemoveTime += maxEndTime - maxStartTime;
            }
            for (long int i = 0; i < number; i++) {
                auto pairingStartTime = std::chrono::high_resolution_clock::now();
                Task extracted = pairingHeap.extractMax();
                auto pairingEndTime = std::chrono::high_resolution_clock::now();
                pairingRemoveTime += pairingEndTime - pairingStartTime;
                counter--;
                std::cout << "| " << std::right << std::setw(10) << extracted.ID << " | " << std::right << std::setw(10) << extracted.priority << " | " << std::left << std::setw(50) << extracted.name << " |\n";
            }
            std::cout << std::endl;
            maxHeapTime += maxRemoveTime;
            pairHeapTime += pairingRemoveTime;
            CSVData.emplace_back(std::vector<std::string>({"remove", std::to_string(number), std::to_string(timerOn), std::to_string(maxRemoveTime.count()), std::to_string(pairingRemoveTime.count()), std::to_string(maxHeapTime.count()), std::to_string(pairHeapTime.count())}));
            std::cout << "Timer ON\n";
            std::cout << std::to_string(number) + " tasks removed.\n";
            std::cout << "MaxHeap completed in " + std::to_string(maxRemoveTime.count()) << " nanoseconds\n";
            std::cout << "Pairing Heap completed in " + std::to_string(pairingRemoveTime.count()) << " nanoseconds\n" << std::endl;
            return std::pair<std::chrono::duration<unsigned long long, std::nano>,std::chrono::duration<unsigned long long, std::nano>>(maxRemoveTime, pairingRemoveTime);
        }
        else {                      // timer on, non-verbose
            std::chrono::duration<unsigned long long, std::nano> maxRemoveTime(0);
            std::chrono::duration<unsigned long long, std::nano> pairingRemoveTime(0);
            for (long int i = 0; i < number; i++) {
                deletedTasks.push_back(maxHeap.peek().ID);
                auto maxStartTime = std::chrono::high_resolution_clock::now();
                Task extracted = maxHeap.extractMax();
                auto maxEndTime = std::chrono::high_resolution_clock::now();
                maxRemoveTime += maxEndTime - maxStartTime;
            }
            for (long int i = 0; i < number; i++) {
                auto pairingStartTime = std::chrono::high_resolution_clock::now();
                Task extracted = pairingHeap.extractMax();
                auto pairingEndTime = std::chrono::high_resolution_clock::now();
                pairingRemoveTime += pairingEndTime - pairingStartTime;
                counter--;
            }
            maxHeapTime += maxRemoveTime;
            pairHeapTime += pairingRemoveTime;
            CSVData.emplace_back(std::vector<std::string>({"remove", std::to_string(number), std::to_string(timerOn), std::to_string(maxRemoveTime.count()), std::to_string(pairingRemoveTime.count()), std::to_string(maxHeapTime.count()), std::to_string(pairHeapTime.count())}));
            std::cout << "Timer ON\n";
            std::cout << std::to_string(number) + " tasks removed.\n";
            std::cout << "MaxHeap completed in " + std::to_string(maxRemoveTime.count()) << " nanoseconds\n";
            std::cout << "Pairing Heap completed in " + std::to_string(pairingRemoveTime.count()) << " nanoseconds\n" << std::endl;
            return std::pair<std::chrono::duration<unsigned long long, std::nano>,std::chrono::duration<unsigned long long, std::nano>>(maxRemoveTime, pairingRemoveTime);
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
                Task extracted = maxHeap.extractMax();
                auto maxEndTime = std::chrono::high_resolution_clock::now();
                maxRemoveTime += maxEndTime - maxStartTime;
            }
            for (long int i = 0; i < number; i++) {
                auto pairingStartTime = std::chrono::high_resolution_clock::now();
                Task extracted = pairingHeap.extractMax();
                auto pairingEndTime = std::chrono::high_resolution_clock::now();
                pairingRemoveTime += pairingEndTime - pairingStartTime;
                counter--;
                std::cout << "| " << std::right << std::setw(10) << extracted.ID << " | " << std::right << std::setw(10) << extracted.priority << " | " << std::left << std::setw(50) << extracted.name << " |\n";
            }
            std::cout << std::endl;
            CSVData.emplace_back(std::vector<std::string>({"remove", std::to_string(number), std::to_string(timerOn), std::to_string(maxRemoveTime.count()), std::to_string(pairingRemoveTime.count()), std::to_string(maxHeapTime.count()), std::to_string(pairHeapTime.count())}));
            std::cout << "Timer OFF\n";
            std::cout << std::to_string(number) + " tasks removed.\n";
            std::cout << "MaxHeap completed in " + std::to_string(maxRemoveTime.count()) << " nanoseconds\n";
            std::cout << "Pairing Heap completed in " + std::to_string(pairingRemoveTime.count()) << " nanoseconds\n" << std::endl;
            return std::pair<std::chrono::duration<unsigned long long, std::nano>,std::chrono::duration<unsigned long long, std::nano>>(maxRemoveTime, pairingRemoveTime);
        }
        else {                      // timer off, non-verbose
            std::chrono::duration<unsigned long long, std::nano> maxRemoveTime(0);
            std::chrono::duration<unsigned long long, std::nano> pairingRemoveTime(0);
            for (long int i = 0; i < number; i++) {
                deletedTasks.push_back(maxHeap.peek().ID);
                auto maxStartTime = std::chrono::high_resolution_clock::now();
                Task extracted = maxHeap.extractMax();
                auto maxEndTime = std::chrono::high_resolution_clock::now();
                maxRemoveTime += maxEndTime - maxStartTime;
            }
            for (long int i = 0; i < number; i++) {
                auto pairingStartTime = std::chrono::high_resolution_clock::now();
                Task extracted = pairingHeap.extractMax();
                auto pairingEndTime = std::chrono::high_resolution_clock::now();
                pairingRemoveTime += pairingEndTime - pairingStartTime;
                counter--;
            }
            CSVData.emplace_back(std::vector<std::string>({"remove", std::to_string(number), std::to_string(timerOn), std::to_string(maxRemoveTime.count()), std::to_string(pairingRemoveTime.count()), std::to_string(maxHeapTime.count()), std::to_string(pairHeapTime.count())}));
            std::cout << "Timer OFF\n";
            std::cout << std::to_string(number) + " tasks removed.\n";
            std::cout << "MaxHeap completed in " + to_string(maxRemoveTime.count()) << " nanoseconds\n";
            std::cout << "Pairing Heap completed in " + to_string(pairingRemoveTime.count()) << " nanoseconds\n" << std::endl;
            return std::pair<std::chrono::duration<unsigned long long, std::nano>,std::chrono::duration<unsigned long long, std::nano>>(maxRemoveTime, pairingRemoveTime);
        }
    }
}

void Benchmark::resetTime() {
    std::cout << "Resetting time...\n";
    maxHeapTime = std::chrono::nanoseconds::zero();
    pairHeapTime = std::chrono::nanoseconds::zero();
    CSVData.emplace_back(std::vector<std::string>({"timer reset", "1", std::to_string(timerOn), "0", "0", std::to_string(maxHeapTime.count()), std::to_string(pairHeapTime.count())}));
}

void Benchmark::resetDataset() {
    std::cout << "Resetting dataset...\n";
    dataset.clear();
    deletedTasks.clear();
    maxHeap.clear();
    pairingHeap.clear();
    counter = 0;
    IDCounter = 0;
    maxHeapTime = std::chrono::nanoseconds::zero();
    pairHeapTime = std::chrono::nanoseconds::zero();
    CSVData = {{"Operation", "Quantity", "Timer", "MaxHeap Time Taken", "Pairing Heap Time Taken", "MaxHeap Timer Sum", "Pairing Heap Timer Sum"}};
    std::string verbosityString = verbosity ? "True" : "False";
    std::string timerString = timerOn ? "On" : "Off";
    std::cout << "Creating new dataset with the selected options:\nMax Size: " + std::to_string(getSize()) + "\nType: " + getType() + "\nVerbosity: " + verbosityString + "\nTimer: " + timerString + "\nDataset created.\n" << std::endl;
}

void Benchmark::writeCSV() {
    CSVData.emplace_back(std::vector<std::string>({"end", "1", std::to_string(timerOn), "0", "0", std::to_string(maxHeapTime.count()), std::to_string(pairHeapTime.count())}));
    std::cout << "Creating CSV file...\n";
    auto timeNow = std::time(nullptr);
    auto timeLocal = *std::localtime(&timeNow);
    std::ostringstream timeStream;
    timeStream << std::put_time(&timeLocal, "%Y-%m-%d-%H-%M-%S");
    std::string timeString = timeStream.str();
    std::ofstream outFile("log-" + timeString + ".csv");
    if (!outFile.is_open()) {
        std::cout << "Failed to open CSV file for writing. Ensure write permissions are available for this directory.\n" << std::endl;
        return;
    }
    std::cout << "Writing CSV file...\n";
    for (const auto& line : CSVData) {
        for (unsigned long long i = 0; i < line.size(); ++i) {
            outFile << line[i];
            if (i != line.size() - 1) {
                outFile << ",";
            }
        }
        outFile << "\n";
    }
    outFile.close();
    std::cout << "CSV file successfully written at log-" + timeString + ".csv\n" << std::endl;
}

void Benchmark::setSize(long int size) {
    datasetMaxSize = size;
    CSVData.emplace_back(std::vector<std::string>({"dataset resize", std::to_string(size), std::to_string(timerOn), "0", "0", std::to_string(maxHeapTime.count()), std::to_string(pairHeapTime.count())}));
}

void Benchmark::setType(int type) {
    datasetType = type;
    CSVData.emplace_back(std::vector<std::string>({"dataset type", std::to_string(type), std::to_string(timerOn), "0", "0", std::to_string(maxHeapTime.count()), std::to_string(pairHeapTime.count())}));
}

void Benchmark::setVerbosity(bool verbose) {
    verbosity = verbose;
    CSVData.emplace_back(std::vector<std::string>({"verbosity", std::to_string(verbose), std::to_string(timerOn), "0", "0", std::to_string(maxHeapTime.count()), std::to_string(pairHeapTime.count())}));
}

void Benchmark::setTimer(bool timer) {
    timerOn = timer;
    CSVData.emplace_back(std::vector<std::string>({"timer set", std::to_string(timer), std::to_string(timerOn), "0", "0", std::to_string(maxHeapTime.count()), std::to_string(pairHeapTime.count())}));
}

void Benchmark::setMinPriority(long int priority) {
    minPriority = priority;
    CSVData.emplace_back(std::vector<std::string>({"min priority set", std::to_string(priority), std::to_string(timerOn), "0", "0", std::to_string(maxHeapTime.count()), std::to_string(pairHeapTime.count())}));
}

void Benchmark::setMaxPriority(long int priority) {
    maxPriority = priority;
    CSVData.emplace_back(std::vector<std::string>({"max priority set", std::to_string(priority), std::to_string(timerOn), "0", "0", std::to_string(maxHeapTime.count()), std::to_string(pairHeapTime.count())}));

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
    std::cout << "Current time:\nMaxHeap completed in " + std::to_string(getMaxHeapTime()) + " nanoseconds.\nPairing Heap completed in " + std::to_string(getPairHeapTime()) + " nanoseconds.\n" << std::endl;
}
