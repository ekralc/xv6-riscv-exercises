#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MSG_SIZE 1

int main(int argc, char *argv[]) {
  int a[2], b[2];
  pipe(a); pipe(b);

  int recv = a[0], send = b[1];

  if (fork() == 0) {
    // We're in the child process, so swap the recv and send pointers
    recv = b[0], send = a[1];
  } else {
    // Initial message
    write(send, "X", MSG_SIZE);
  }

  char buf[MSG_SIZE];
  for (;;) {
    read(recv, buf, sizeof buf);
    printf("process %d received %s\n", getpid(), buf);
    write(send, buf, sizeof buf);
  }

  exit(0);
}