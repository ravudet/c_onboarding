Creating a "Hello World" program in C using Visual Studio 2022 is a great way to get started with programming. Follow these steps:

1. Create a New Project

Open Visual Studio 2022.

Go to File > New > Project.

Select Empty Project under the C++ category (C projects are handled similarly to C++).

Name your project (e.g., HelloWorld) and click Create.

2. Add a C Source File

In the Solution Explorer, right-click on the Source Files folder.

Select Add > New Item.

Choose C++ File (.cpp), but rename it with a .c extension (e.g., hello.c).

Click Add.

3. Write the Code

Open the newly created hello.c file and add the following code:

#include <stdio.h>

int main() {
printf("Hello, World!\n");
return 0;
}
Copy
4. Configure the Compiler for C

Right-click on your project in the Solution Explorer and select Properties.

Navigate to Configuration Properties > C/C++ > Advanced.

Set the Compile As option to Compile as C Code (/TC).

Click OK to save changes.

5. Build and Run

Press Ctrl + Shift + B to build the project.

If there are no errors, press Ctrl + F5 to run the program.

The console will display:

Hello, World!
Copy
Tips

Ensure you have installed the "Desktop development with C++" workload during Visual Studio setup.

Use proper file extensions (.c) for C programs to avoid confusion with C++.

This simple program demonstrates how to set up and execute a basic C application in Visual Studio 2022!

Learn more:
1 -
learn.microsoft.com
2 -
stackoverflow.com
3 -
geeksforgeeks.org












## test that you're not accidentally c++





#include <iostream>

void print(int x) {
    std::cout << "Integer: " << x << std::endl;
}

void print(double x) {
    std::cout << "Double: " << x << std::endl;
}

int main() {
    print(5);
    print(3.14);
    return 0;
}