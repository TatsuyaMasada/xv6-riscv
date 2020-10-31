// pingpong.c for xv6 (assignment #1 for CSC.T371)
// name: 政田　龍也
// id: 18B13969

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(1, "usage: %s N\n", argv[0]);
        exit(1);
    }

    // # of rounds
    int n = atoi(argv[1]);

    // tick value before starting rounds
    int start_tick = uptime();

    unsigned char buf = 0;
    int fd1[2], fd2[2];
    pipe(fd1); // parent sends
    pipe(fd2);  // child sends
    int pid = fork();
    int status;
    int rounds = 0;

    if(pid == 0) { /* child */
        close(fd1[1]);
        close(fd2[0]);
        while(rounds < n) {
            while(1) {
                if(read(fd1[0], &buf, 1) == 1) {
                    buf++;
                    break;
                }
            }
            write(fd2[1], &buf, 1);
            rounds++;
        }
        exit(0);
    } else { /* parent */
        close(fd1[0]);
        close(fd2[1]);
        while(rounds < n) {
            write(fd1[1], &buf, 1);
            while(1) {
                if(read(fd2[0], &buf, 1) == 1) {
                    buf++;
                    rounds++;
                    break;
                }
            }
        }
        wait(&status);
    }

    // print # of ticks in nrounds
    printf("# of ticks in %d rounds: %d\n", n, uptime() - start_tick);
    exit(0);
}
