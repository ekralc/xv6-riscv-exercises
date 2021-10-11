#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
        printf("a statement here before\n");

        int currentpid = getpid();

        printf("the current pid is %d\n", currentpid);

        int pid = fork();
        
        if (pid > 0) {
                printf("parent: child=%d\n", pid);
                pid = wait((int *)0);
                printf("child %d is done\n", pid);
        } else if (pid == 0) {
                printf("child: exiting\n");
                exit(0);
        } else {
                printf("fork error\n");
        }

        exit(0);
        return 0;
}