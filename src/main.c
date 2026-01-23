#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*cmd_fn)(char **args);

typedef struct {
    char *name;
    cmd_fn func;
} LookupTable;

int cmd_exit(char **args) {
    exit(0);
    return 0;
}

int cmd_echo(char **args){
  char *params = args[0];
  char *rest = args[1];

  printf("%s %s\n", params, rest);
}

LookupTable commands[] = {
    {"exit", cmd_exit},
    {"echo", cmd_echo}
};

char *read_command() {
    char buffer[100];

    printf("$ ");
    fgets(buffer, 100, stdin);

    buffer[strcspn(buffer, "\n")] = '\0';

    char *text = malloc(strlen(buffer) + 1);
    strcpy(text, buffer);

    return text;
}

int default_command(char *text) {
    printf("%s: command not found\n", text);
    return 0;
}

int eval(char *text) {
    char *func = strtok(text, " ");
    if (!func) return 0;  // empty input

    char *param = strtok(NULL, " ");
    char *rest = NULL;

    if (param) {
        rest = text + strlen(func) + strlen(param) + 2;
    }

    // Build args array
    char *args[2] = {param, rest};

    for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
        if (strcmp(commands[i].name, func) == 0) {
            return commands[i].func(args);
        }
    }

    default_command(func);
    return 0;
}

int main() {
    while (1) {
        setbuf(stdout, NULL);
        char *text = read_command();
        eval(text);
        free(text);
    }
    return 0;
}
