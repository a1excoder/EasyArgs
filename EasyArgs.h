#ifndef EASY_ARGS_H
#define EASY_ARGS_H

#include <assert.h>
#include <string.h>
#include <stdlib.h>

// #define NDEBUG
// 
// #define EASY_ARGS_MAX 0

typedef enum {
	ARG_INT = 0,
	ARG_FLOAT,
	ARG_STRING
} EASY_ARG_TYPES;

typedef struct {
	char* arg_keys;
	char* description;
} ArgElement;

typedef struct {
	int argc;
	const char** argv;
} ARG_HANDLE;

static ArgElement easy_args_data[EASY_ARGS_MAX];

void print_help()
{
	for (int i = 0; i < EASY_ARGS_MAX; i++) {
		printf("%s - %s\n", easy_args_data[i].arg_keys, easy_args_data[i].description);
	}
}

void init_easy_args(ARG_HANDLE* hArg, int argc, const char*** argv)
{
	hArg->argc = argc;
	hArg->argv = *argv;

	for (int i = 0; i < EASY_ARGS_MAX; i++) {
		easy_args_data[i].arg_keys = NULL;
	}
}

int add_arg(ARG_HANDLE* hArg, const char* arg_key, const char* description)
{
	assert(hArg != NULL && arg_key != NULL);

	for (int i = 0; i < EASY_ARGS_MAX; i++) {
		if (easy_args_data[i].arg_keys == NULL) {
			easy_args_data[i].arg_keys = arg_key;
			easy_args_data[i].description = description;

			return 0;
		}
	}

	return -1;
}


int get_arg(ARG_HANDLE* hArg, const char *key, EASY_ARG_TYPES type, void** dst)
{
	assert(hArg != NULL && key != NULL);

	int arg_int = 0;
	float arg_float = 0.f;

	for (int i = 1; i < hArg->argc; i++) {
		if (strchr(hArg->argv[i], '-') != NULL) {
			if (!strcmp(hArg->argv[i], key)) {
				if (hArg->argv[i + 1] != NULL) {

					switch (type) {
					case ARG_INT:
						arg_int = atoi(hArg->argv[i + 1]);
						memmove(*dst, &arg_int, sizeof(int));
						break;
					case ARG_FLOAT:
						arg_float = atof(hArg->argv[i + 1]);
						memmove(*dst, &arg_float, sizeof(float));
						break;
					case ARG_STRING:
						*dst = hArg->argv[i + 1];
						break;
					default:
						return -3;
					}

					return 0;
				}

				return -2;
			}
		}
	}


	return -1;
}

int is_arg(ARG_HANDLE* hArg, const char* key)
{
	assert(hArg != NULL && key != NULL);

	for (int i = 1; i < hArg->argc; i++) {
		if (strchr(hArg->argv[i], '-') != NULL) {
			if (!strcmp(hArg->argv[i], key)) {
				return 0;
			}
		}
	}

	return -1;
}


#endif // EASY_ARGS_H