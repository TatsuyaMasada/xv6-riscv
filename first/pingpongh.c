// pingpong.c for xv6 (assignment #2 for CSC.T371)
// name: 政田　龍也
// id: 18B13969

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "usage: ./a.out N\n");
        exit(1);
    }

    int n = atoi(argv[1]);

    clock_t start_time = clock();

    unsigned char buf = 0;

    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);

    int rounds = 0;
    int status;
    int pid = fork();

    if(pid == 0) {
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
    } else {
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
    printf("# of time in %d rounds: %f[ms]\n", n, (double)(clock() - start_time)/CLOCKS_PER_SEC*1000);
    return 0;
}