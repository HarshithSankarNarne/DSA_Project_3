Readme
1. Download the zip file from Github and extract it
2. Open zip file of the code in CLion, or type g++ -std=c++14 -Wall -Werror -g -o P3.exe main.cpp Benchmark.cpp MaxHeap.cpp PairingHeap.cpp in command prompt to run the program.
3. The code should run when the zip file is opened in Clion when the Run button is clicked. Use C++ 14 when you create the project 
4. When the code is run, prompts will show up and you should read the prompts and pick the options you would like.
5. Quick simulate is the best way to see the code working. It is the first option under the Simulate menu (option 1).
6. To manually adjust the data, select 2 (Options) in the initial menu, and follow the prompts to change attributes of the data sets
7. To manually run the program, select 1 (Simulate) and follow the prompts for tracking time and/or deleting the data set.
8. To save data to a CSV file, select 4 in the simulation menu.


FYI: For testing.cpp, it was implemented to make sure the pairing heap was working properly.  You can ignore it completely. To make it work you need to comment out the int main in the testing.cpp and create a seperate configuration that only runs the testing.cpp. The testing.cpp plays not role in the actual project but was created by Harshith as he was developing the pairing heap and need a place to debug and test functionality simimlar to test.cpp in Project 1 and 2.
