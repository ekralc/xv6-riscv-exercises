#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  int a[2], b[2];
  pipe(a); pipe(b);

  int pid;
  char buf[1];

  pid = fork();

  if (pid != 0) {
    // get the ball rolling
    write(a[1], "X", 1);

    for (;;) {
      read(b[0], buf, sizeof buf);
      printf("process %d received %s\n", getpid(), buf);
      write(a[1], buf, sizeof buf);
    }
  } else {
    for (;;) {
      read(a[0], buf, sizeof buf);
      printf("process %d received %s\n", getpid(), buf);
      write(b[1], buf, sizeof buf);
    } 
  }

  exit(0);
}