# Linux Command Flashcards

![CMake compilation]()

This program uses two-argumented templated linked-list that reads a list of linux commands from a csv file, and an array which will store user profiles also read from a csv file.

From the commands list, we generate a command line game where a command is picked at random, then displayed to the screen along with 3 descriptions. One of the descriptions is correct while the other two are chosen at random. The ordering of the descriptions should also be random so as to not be predictable.

## Game Menu
![main_menu](https://user-images.githubusercontent.com/34149684/128798659-b1d5619b-ad28-4f67-b121-b93bc4ba158e.png)

## Build Instructions

We automate the build with the provided `CMakeLists.txt` file.

### Prerequisite
Install these from your distribution's package manager or any other equivalent ways:
* `g++`
* `cmake`
* `build-essential`

### Instructions:
From the project root, run the following
* `mkdir build; cmake -B build -S .; cmake --build build`

### Run
After building, you can run the program by first changing directory to build, then execute the binary file,
* `cd build`
* `./flashcards`
