#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  // TODO: Uncomment the code below to pass the first stage
  printf("$ ");

  char text[100];

  fgets(text, 100, stdin);
  text[strlen(text) - 1] = '\0';

  printf("%s: command not found\n", text);

  return 0;
}
