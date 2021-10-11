#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Invalid number of arguments\n");
    exit(0);
    return 0;
  }

  int procCount = atoi(argv[1]);
  if (procCount < 1) {
    printf("Process count must be greater than 0\n");
    exit(0);
    return 0;
  }

  for (int i = 0; i < procCount; i++) {
    int pid = fork();
    if (pid == 0) {
      pid = getpid();
      printf("Hello from process %d\n", pid);
      exit(0);
    }
    wait((int*) 0);
  }

  printf("All this talk about forks, but what about knives?\n");

  exit(0);
  return 0;
}