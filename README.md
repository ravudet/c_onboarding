### install and configure IDE

1. Install Visual Studio 2022 Community version 17.14.16
2. Install the appropriate visual studio components using [`/.vsconfig`](/.vsconfig)

### create a new project

1. File -> New -> Project
2. Select "Empty Project" under the "C++" language
3. Click "Create"
4. Add a `hello.c` file with the following contents:
```c
#include <stdio.h>

int main() {
printf("Hello, World!\n");
return 0;
}
```
5. Right-click the project -> properties -> c/c++ -> Advanced
6. set "compile as" to "compile as c code (/TC)"
7. click ok

### confirm that you aren't accidentally compiling c++

```
#include <stdio.h>

void print(int x)
{
	printf("Integer:");
	printf(x);
	printf("\n");
}

void print(double x)
{
	printf("Double:");
	printf(x);
	printf("\n");
}

int main()
{
	print(5);
	print((int)3.14);
	return 0; 
}
```

### documentation

https://pubs.opengroup.org/onlinepubs/9699919799/functions/fclose.html
