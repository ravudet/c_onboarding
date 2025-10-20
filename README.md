1. Install Visual Studio 2022 Community version 17.14.16
2. Install the appropriate visual studio components using [`/.vsconfig`](/.vsconfig)
3. File -> New -> Project
4. Select "Empty Project" under the "C++" language
5. Click "Create"
6. Add a `hello.c` file with the following contents:
```c
#include <stdio.h>

int main() {
printf("Hello, World!\n");
return 0;
}
```
7. Right-click the project -> properties -> c/c++ -> Advanced
8. set "compile as" to "compile as c code (/TC)"
9. click ok











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
