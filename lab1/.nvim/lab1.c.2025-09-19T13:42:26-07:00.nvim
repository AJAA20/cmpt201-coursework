#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  printf("Please enter some text \n");

  // get a line
  // handle errors
  // tokenize a line -- setup
  // tokenize loop
  // cleanup?

  char *line = NULL; // line buffer
  size_t n = 0;
  if (getline(&line, &n, stdin) != -1) {
    printf("Got: %s\n", line);
    char *ret = NULL;
    char *saveptr = NULL;
    char *str = line;
    while ((ret = strtok_r(str, " ", &saveptr))) {
      printf(" %s\n", ret);
      str = NULL;
    }
  } else {
    printf("Failure reading a line \n");
  }

  free(line);

  return 0;
}
