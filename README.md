# EasyArgs -  easy args parsing library

#### First of all you need include EasyArgs.h to your project, then before include code line add #define EASY_ARGS_MAX with number of values you want to parse
```c
// example
#define EASY_ARGS_MAX 3
#include "EasyArgs.h"
```

#### Before all of using you need to create ARG_HANDLE variable and execute init_easy_args function to initialize library
```c
// example
int main(int argc, const char** argv)
{
    ARG_HANDLE hargs;
    init_easy_args(&hargs, argc, &argv);
}
```

#### Full example
```c
#include <stdio.h>


#define EASY_ARGS_MAX 3
#include "EasyArgs.h"


int main(int argc, const char** argv)
{
	ARG_HANDLE hargs;
	init_easy_args(&hargs, argc, &argv);

	add_arg(&hargs, "(-n | --name)", "your name");
	add_arg(&hargs, "(-a | --age)", "your age");
	add_arg(&hargs, "(-v | --version)", "info about version");

	

	char* name_buff = NULL;
	int age = 0;
	int* age_ptr = &age;


	if (!is_arg(&hargs, "-h") || !is_arg(&hargs, "--help")) {
		print_help();
		return 0;
	}

	if (!get_arg(&hargs, "-n", ARG_STRING, &name_buff) || 
		!get_arg(&hargs, "--name", ARG_STRING, &name_buff)) {

		printf("name is: %s\n", name_buff);


		if (!get_arg(&hargs, "-a", ARG_INT, &age_ptr) ||
			!get_arg(&hargs, "--age", ARG_INT, &age_ptr)) {

			printf("age is: %d\n", age);
		}
	} else {
		print_help();
		return 1;
	}

	
	if (!is_arg(&hargs, "-v") || !is_arg(&hargs, "--version")) {
		printf("[VERSION]: 3.1.3.3.7\n");
	}


	return 0;
}
```
