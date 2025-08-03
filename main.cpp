#include <iostream>
#include "Benchmark.h"

int getInput(int low, int high);
void printCurrentTime(Benchmark& benchmark);

int main()
{
    std::string welcomeScreen = "Priority Task Manager\n1. Simulate\n2. Options\n3. Exit\n\n";
    std::string simulationMenu = "Simulation\n1. Quick Simulation\n2. Begin timer\n3. Stop timer\n4. Print current total time\n5. Reset dataset\n6. Reset time\n7. Add tasks\n8. Remove top tasks\n9. Back to menu\n0. Print this menu again\n\n";
    std::string optionsMenu = "Options\n1. Adjust dataset size (0-10000000) [default: 100000]\n2. Adjust dataset type (Random, Ascending, Descending) [default: Random]\n3. Set verbosity (Verbose: slow, prints each operation to screen; Non-Verbose: fast, only returns time to complete) [default: Non-Verbose]\n4. Back to menu\n0. Print this menu again\n\n";
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
            else if (choice == 0) {
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

            }
            else if (choice == 2) {     // start/stop timer
                if (!benchmark.getTimer()) {
                    std::cout << "The timer is currently OFF. Turn on the timer? 0 for no, 1 for yes.\n\n";
                    int selection = getInput(0, 1);
                    if (selection == 0) {
                        std::cout << "Timer change cancelled.\n\n";
                    }
                    else if (selection == 1) {
                        benchmark.setTimer(true);
                        std::cout << "Timer started.\n";
                        printCurrentTime(benchmark);
                    }
                }
                else {
                    std::cout << "The timer is currently ON. Turn off the timer? 0 for no, 1 for yes.\n\n";
                    int selection = getInput(0, 1);
                    if (selection == 0) {
                        std::cout << "Timer change cancelled.\n\n";
                    }
                    else if (selection == 1) {
                        benchmark.setTimer(false);
                        std::cout << "Timer stopped.\n";
                        printCurrentTime(benchmark);
                    }
                }
            }
            else if (choice == 3) {     // check time
                printCurrentTime(benchmark);
            }
            else if (choice == 4) {     // print CSV file

            }
            else if (choice == 5) {

            }
            else if (choice == 6) {

            }
            else if (choice == 7) {     // add tasks
                long int freeSpace = benchmark.getSize() - benchmark.getDataSize();
                if (freeSpace <= 0) {
                    std::cout << "Dataset full. Please select another option.\n\n";
                    continue;
                }
                std::cout << "How many tasks to add? Enter a number between 1 and " + std::to_string(freeSpace) + ". 0 to cancel.\n\n";
                std::string addInfo = "Tasks: ";
                long int taskNumber = Benchmark::getNumber(addInfo, 0, freeSpace);
                if (taskNumber == 0) {
                    std::cout << "Cancelled task add.\n\n";
                }
                else {
                    std::cout << "Automatic or manual? Enter 0 for automatic task generation, 1 for manual entering.\n\n";
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

            }
            else if (choice == 9) {     // return to menu
                screen = 0;
                seenMenu = false;
            }
            else if (choice == 0) {
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
                std::cout << "Adjust the maximum dataset size to a value between 0 and 10,000,000. Cannot be lower than the current number of tasks.\nCurrent tasks: " + std::to_string(benchmark.getDataSize()) + "\nCurrent max capacity: " + std::to_string(benchmark.getSize()) + "\n\n";
                benchmark.setSize(getInput(benchmark.getDataSize(), 10000000));
            }
            else if (choice == 2) {     // adjust dataset type
                std::string currentType;
                if (benchmark.getType() == 0) {
                    currentType = "Random";
                }
                else if (benchmark.getType() == 1) {
                    currentType = "Ascending";
                }
                else if (benchmark.getType() == 2) {
                    currentType = "Descending";
                }
                else {
                    currentType = "Unknown";
                }
                std::cout << "Adjust the dataset type for autogenerated tasks.\n0 for Random, 1 for Ascending, and 2 for Descending.\nCurrent type: " + currentType + "\n\n";
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
                std::cout << "Adjust the verbosity for operations done. Verbose operations will take more time but show the details for each task.\n0 for Non-Verbose, 1 for Verbose.\n Current verbosity: " + currentVerbosity + "\n\n";
                benchmark.setVerbosity(getInput(0, 1));
            }
            else if (choice == 4) {     // return to menu
                screen = 0;
                seenMenu = false;
            }
            else if (choice == 0) {
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
        std::cout << "\n\n";
        try {
            output = stoi(input);
        }
        catch (...) {
            std::cout << "Please enter a valid input\n\n";
            continue;
        }
        if (low <= output && output <= high) {
            validInput = true;
        }
        else {
            std::cout << "Please select a valid option between " + std::to_string(low) + " and " + std::to_string(high) + "\n\n";
        }
    }
    return output;
}

void printCurrentTime(Benchmark& benchmark) {
    std::cout << "Current time:\nMaxHeap completed in " + std::to_string(benchmark.getMaxHeapTime()) + " nanoseconds.\nPairing Heap completed in " + std::to_string(benchmark.getPairHeapTime()) + " nanoseconds\n\n";
}
