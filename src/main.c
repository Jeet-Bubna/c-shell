#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// returns the command to be evaluated
char *read_command(){
  char buffer[100];

  printf("$ ");
  fgets(buffer, 100, stdin);

  buffer[strcspn(buffer, "\n")] = '\0';

  char *text = malloc(strlen(buffer) + 1 ); // +1 because strlen doenst inclde null terminator '\0'
  strcpy(text, buffer);

  return text;
}

// default command for now, which is just command not found
int default_command(char *text){
  printf("%s: command not found\n", text);
  return 0;
}

// parses and executes the command
int eval(char *text){
  // parsing
  char command[] = "default";

  // executing
  default_command(text);
  return 0;
}

int main(int argc, char *argv[]) {
  
  while(1){
    // Flush after every printf
    setbuf(stdout, NULL);

    // REPL loop
    char *text = read_command();
    eval(text);
    free(text);
  }

  return 0;
}