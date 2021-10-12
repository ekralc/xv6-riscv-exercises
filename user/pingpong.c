#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  int to[2];
  int from[2];

  pipe(to);
  pipe(from);

  int *printing = malloc(sizeof(int));
  *printing = 0;
  int pid = fork();

  if (pid > 0) {
    char buf[1];

    char yes = 'Q';
    fprintf(to[0], &yes);

    for (;;) {
      read(to[1], buf, sizeof buf);
      while (!*printing) {
        *printing = 1;
        printf("Received %c in parent process\n\n", buf[0]);
        sleep(100);
        *printing = 0;
        break;
      }
      write(from[0], buf, sizeof buf);
    }
  } else if (pid == 0) {
    char buf[1];

    for (;;) {
      read(from[1], buf, sizeof buf);
      
      while (!*printing) {
        *printing = 1;
        printf("Received %c in child process\n\n", buf[0]);
        sleep(100);
        *printing = 0;
        break;
      }
      write(to[0], buf, sizeof buf);
    }
  } else {
    printf("fork error\n");
  }

  exit(0);
  return 0;
}