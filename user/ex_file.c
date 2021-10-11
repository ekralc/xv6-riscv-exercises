#include "kernel/types.h"
#include "user/user.h"

#define STDIN 0
#define STDOUT 1
#define STDERR 2

int main() {
  char buf[512];
  int n;

  for (;;) {
    n = read(STDIN, buf, sizeof buf);

    if (n == 0) {
      break;
    }

    if (n < 0) {
      fprintf(STDERR, "read error\n");
      exit(1);
    }

    if (write(STDOUT, buf, n) != n) {
      fprintf(STDERR, "write error\n");
      exit(1);
    }
  }

  exit(0);
}