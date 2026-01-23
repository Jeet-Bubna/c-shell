#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

typedef int (*cmd_fn)(char **args);

typedef struct {
		char *name;
		cmd_fn func;
} LookupTable;

// forward declarations
int cmd_exit(char **args);
int cmd_echo(char **args);
int cmd_type(char **args);

LookupTable commands[] = {
		{"exit", cmd_exit},
		{"echo", cmd_echo},
		{"type", cmd_type}
};

// function declarations
int cmd_exit(char **args) {
		exit(0);
		return 0;
}

int cmd_echo(char **args){
	int i = 0;
	while(args[i]){
		printf("%s ", args[i]);
		i++;
	}
	printf("\n");
	return 0;
}

int cmd_type(char **args){
	char *params = args[0];
	
	for(int i = 0; i < sizeof(commands)/sizeof(commands[0]); i++){
		if(strcmp(commands[i].name, params) == 0){
			printf("%s is a shell builtin\n", params);
			return 0;
		}
	}

	char *path = getenv("PATH");
	if(!path) return 0;

	char *path_copy = strdup(path);
	if(!path_copy) return 0;

	char *token = strtok(path_copy, ":");

	while(token){
		char fullAdress[512];
		snprintf(fullAdress, sizeof(fullAdress), "%s/%s", token, args[0]);
		if(access(fullAdress, X_OK) == 0){
			printf("%s is %s\n", args[0], fullAdress);
			free(path_copy);
			return 0;
		}
		token = strtok(NULL, ":");
	}

	printf("%s: not found\n", args[0]);
	free(path_copy);
	return 1;
}

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

int execprogram(char *args[]){

	pid_t pid = fork();

	if(pid == 0){
		// child process
		execvp(args[0], args);
		printf("%s: command not found\n", args[0]);
		exit(1);
	} else{
		wait(NULL);
	}

	return 0;
}

int eval(char *text) {
    char *args[64];
    int argc = 0;

    char *token = strtok(text, " ");
    if (!token) return 0;

    while (token && argc < 63) {
        args[argc++] = token;						// agrc++ --> use argc and then increase i
        token = strtok(NULL, " ");
    }
    args[argc] = NULL;

    for (int i = 0; i < sizeof(commands)/sizeof(commands[0]); i++) {
        if (strcmp(commands[i].name, args[0]) == 0) {
            return commands[i].func(&args[1]);
        }
    }

		execprogram(args);

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