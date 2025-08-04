#include <iostream>
#include "Benchmark.h"

int getInput(int low, int high);

int main()
{
    std::string welcomeScreen = "Priority Task Manager\n1. Simulate\n2. Options\n3. Exit\n" << std::endl;
    std::string simulationMenu = "Simulation\n1. Quick Simulation\n2. Begin timer\n3. Stop timer\n4. Print current total time\n5. Reset dataset\n6. Reset time\n7. Add tasks\n8. Remove top tasks\n9. Back to menu\n0. Print this menu again\n" << std::endl;
    std::string optionsMenu = "Options\n1. Adjust dataset size (0-10000000) [default: 100000]\n2. Adjust dataset type (Random, Ascending, Descending) [default: Random]\n3. Set verbosity (Verbose: slow, prints each operation to screen; Non-Verbose: fast, only returns time to complete) [default: Non-Verbose]\n4. Back to menu\n0. Print this menu again\n" << std::endl;
    int screen = 0;             // 0 for welcome screen, 1 for simulation menu, 2 for options menu
    bool seenMenu = false;      // avoids repeating printing the current menu
    Benchmark benchmark;

    // main program loop
    while (true) {
        if (screen == 0) {          // welcome menu
            if (!seenMenu) {
                std::cout << welcomeScreen;
                seenMenu = true;
            }
            int choice = getInput(0, 3);
            if (choice == 1) {          // move to simulation menu
                screen = 1;
                seenMenu = false;
            }
            else if (choice == 2) {     // move to options menu
                screen = 2;
                seenMenu = false;
            }
            else if (choice == 3) {     // close program
                std::cout << "Closing Program..." << std::endl;
                break;
            }
            else if (choice == 0) {     // show menu again
                seenMenu = false;
            }
        }
//TODO: complete simulation menu
        else if (screen == 1) {     // simulation menu
            if (!seenMenu) {
                std::cout << simulationMenu;
                seenMenu = true;
            }
            int choice = getInput(0, 9);
            if (choice == 1) {          // quick simulation
                std::cout << "Adds tasks up to the maximum heap size based on the current task generation scheme, then removes them down to the previously inserted tasks. Make sure to turn on the timer beforehand if it is off and you wish to save time data. If the heaps are empty, this is equivalent to performing a full run.\n0 to cancel, 1 to continue\n" << std::endl;
                int selection = getInput(0, 1);
                if (selection == 0) {
                    std::cout << "Quick simulation cancelled.\n" << std::endl;
                }
                else if (selection == 1) {
                    long int freeSpace = benchmark.getSize() - benchmark.getDataSize();
                    if (freeSpace <= 0) {
                        std::cout << "Dataset full. Please select another option.\n" << std::endl;
                        continue;
                    }
                    benchmark.printCurrentTime();
                    unsigned long long maxStartTime = benchmark.getMaxHeapTime();
                    unsigned long long pairingStartTime = benchmark.getPairHeapTime();
                    benchmark.generateTasks(freeSpace);
                    unsigned long long maxPostInsertTime = benchmark.getMaxHeapTime();
                    unsigned long long pairingPostInsertTime = benchmark.getPairHeapTime();
                    benchmark.removeTasks(freeSpace);
                    unsigned long long maxPostRemoveTime = benchmark.getMaxHeapTime();
                    unsigned long long pairingPostRemoveTime = benchmark.getPairHeapTime();
                    std::string timerValue = benchmark.getTimer() ? "Timer ON" : "Timer OFF";
                    std::cout << "Summary:\n" + timerValue + "\nMaxHeap: insertion " + std::to_string(maxPostInsertTime - maxStartTime) + " ns, deletion " + std::to_string(maxPostRemoveTime - maxPostInsertTime) + " ns, sum " + std::to_string(maxPostRemoveTime - maxStartTime) + "\nPairing Heap: insertion " + std::to_string(pairingPostInsertTime - pairingStartTime) + " ns, deletion " + std::to_string(pairingPostRemoveTime - pairingPostInsertTime) + " ns, sum " + std::to_string(pairingPostRemoveTime - pairingStartTime) + "\n" << std::endl;
                }
            }
            else if (choice == 2) {     // start/stop timer
                if (!benchmark.getTimer()) {
                    std::cout << "The timer is currently OFF. Turn on the timer? 0 for no, 1 for yes.\n" << std::endl;
                    int selection = getInput(0, 1);
                    if (selection == 0) {
                        std::cout << "Timer change cancelled.\n" << std::endl;
                    }
                    else if (selection == 1) {
                        benchmark.setTimer(true);
                        std::cout << "Timer started.\n";
                        benchmark.printCurrentTime();
                    }
                }
                else {
                    std::cout << "The timer is currently ON. Turn off the timer? 0 for no, 1 for yes.\n" << std::endl;
                    int selection = getInput(0, 1);
                    if (selection == 0) {
                        std::cout << "Timer change cancelled.\n" << std::endl;
                    }
                    else if (selection == 1) {
                        benchmark.setTimer(false);
                        std::cout << "Timer stopped.\n";
                        benchmark.printCurrentTime();
                    }
                }
            }
            else if (choice == 3) {     // check time
                if (!benchmark.getTimer()) {
                    std::cout << "The timer is currently OFF.\n" << std::endl;
                    benchmark.printCurrentTime();
                }
                else {
                    std::cout << "The timer is currently ON.\n" << std::endl;
                    benchmark.printCurrentTime();
                }
            }
            else if (choice == 4) {     // print CSV file

            }
            else if (choice == 5) {     // reset dataset
                std::cout << "Reset the current dataset, with all tasks and timers, back to empty, with the presently selected options.\nNote: Differs from removing all tasks, as this operation will reset all unsaved log data and IDs for this run as well. Continue?\n0 to cancel, 1 to continue\n" << std::endl;
                int selection = getInput(0, 1);
                if (selection == 0) {
                    std::cout << "Reset cancelled.\n" << std::endl;
                }
                else if (selection == 1) {
                    benchmark.resetDataset();
                    benchmark.printCurrentTime();
                }
            }
            else if (choice == 6) {     // reset time
                std::cout << "Reset the current clock time to 0 for both the MaxHeap and Pairing Heap. Does not change timer condition.\n0 to cancel, 1 to confirm.\n" << std::endl;
                int selection = getInput(0, 1);
                if (selection == 0) {
                    std::cout << "Timer reset cancelled.\n" << std::endl;
                }
                else if (selection == 1) {
                    benchmark.resetTime();
                    benchmark.printCurrentTime();
                }
            }
            else if (choice == 7) {     // add tasks
                long int freeSpace = benchmark.getSize() - benchmark.getDataSize();
                if (freeSpace <= 0) {
                    std::cout << "Dataset full. Please select another option.\n" << std::endl;
                    continue;
                }
                std::cout << "How many tasks to add? Enter a number between 1 and " + std::to_string(freeSpace) + ". 0 to cancel.\n" << std::endl;
                std::string addInfo = "Tasks: ";
                long int taskNumber = Benchmark::getNumber(addInfo, 0, freeSpace);
                if (taskNumber == 0) {
                    std::cout << "Cancelled task add.\n" << std::endl;
                }
                else {
                    std::cout << "Automatic or manual? Enter 0 for automatic task generation, 1 for manual entering.\n" << std::endl;
                    int autoSwitch = getInput(0, 1);
                    if (autoSwitch == 0) {
                        benchmark.generateTasks(taskNumber);
                        seenMenu = false;
                    }
                    else if (autoSwitch == 1) {
                        benchmark.generateTasksManual(taskNumber);
                        seenMenu = false;
                    }
                }
            }
            else if (choice == 8) {     // remove top tasks
                long int taskCount = benchmark.getDataSize();
                if (taskCount <= 0) {
                    std::cout << "Dataset empty. Please select another option.\n" << std::endl;
                    continue;
                }
                std::cout << "How many tasks to extract? Enter a number between 1 and " + std::to_string(taskCount) + ". 0 to cancel.\n" << std::endl;
                std::string extractInfo = "Tasks: ";
                long int taskNumber = Benchmark::getNumber(extractInfo, 0, taskCount);
                if (taskNumber == 0) {
                    std::cout << "Cancelled task extract.\n" << std::endl;
                }
                else {
                    benchmark.removeTasks(taskNumber);
                    seenMenu = false;
                }
            }
            else if (choice == 9) {     // return to menu
                screen = 0;
                seenMenu = false;
            }
            else if (choice == 0) {     // show menu again
                seenMenu = false;
            }
        }

        else if (screen == 2) {
            if (!seenMenu) {
                std::cout << optionsMenu;
                seenMenu = true;
            }
            int choice = getInput(0, 4);
            if (choice == 1) {          // adjust dataset size
                std::cout << "Adjust the maximum dataset size to a value between 0 and 10,000,000. Cannot be lower than the current number of tasks.\nCurrent tasks: " + std::to_string(benchmark.getDataSize()) + "\nCurrent max capacity: " + std::to_string(benchmark.getSize()) + "\n" << std::endl;
                benchmark.setSize(getInput(benchmark.getDataSize(), 10000000));
            }
            else if (choice == 2) {     // adjust dataset type
                std::string currentType = benchmark.getType();
                std::cout << "Adjust the dataset type for autogenerated tasks.\n0 for Random, 1 for Ascending, and 2 for Descending.\nCurrent type: " + currentType + "\n" << std::endl;
                benchmark.setType(getInput(0, 2));
            }
            else if (choice == 3) {     // adjust verbosity
                std::string currentVerbosity;
                if (!benchmark.getVerbosity()) {
                    currentVerbosity = "Non-Verbose";
                }
                else {
                    currentVerbosity = "Verbose";
                }
                std::cout << "Adjust the verbosity for operations done. Verbose operations will take more time but show the details for each task.\n0 for Non-Verbose, 1 for Verbose.\n Current verbosity: " + currentVerbosity + "\n" << std::endl;
                benchmark.setVerbosity(getInput(0, 1));
            }
            else if (choice == 4) {     // return to menu
                screen = 0;
                seenMenu = false;
            }
            else if (choice == 0) {     // show menu again
                seenMenu = false;
            }
        }
    }

    return 0;
}

int getInput(int low, int high) {
    std::string input;
    int output = -1;
    bool validInput = false;
    while (!validInput) {
        std::cout << "Enter your selection: ";
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
            std::cout << "Please select a valid option between " + std::to_string(low) + " and " + std::to_string(high) + "\n" << std::endl;
        }
    }
    return output;
}

