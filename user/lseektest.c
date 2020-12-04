#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main(void){
    char buf[15] = "lseek ok\n";
    char ans[15] = "";
    int fd=open("foo.txt",O_RDWR | O_CREATE | O_TRUNC);
    if(fd<0){
        exit(1);
    }

    if(lseek(fd, 0, SEEK_CUR) !=0) {
        printf("lseek bad1\n");
        exit(0);
    }

    write(fd , buf, strlen(buf));
    if(lseek(fd, 0, SEEK_CUR) != 9){
        printf("lseek bad2\n");
        exit(0);
    }

    if(lseek(fd, -4, SEEK_CUR) != 5) {
        printf("lseek bad3\n");
        exit(0);
    }

    if(lseek(fd, 5, SEEK_CUR) != 10) {
        printf("lseek bad4\n");
        exit(0);
    }

    if(lseek(fd, 0, SEEK_END) != 9) {
        printf("lseek bad5\n");
        exit(0);
    }
    

    if(lseek(fd, -4, SEEK_END) != 5) {
        printf("lseek bad6\n");
        exit(0);
    }
    
    
    if(lseek(fd, 5, SEEK_END) != 14) {
        printf("lseek bad7\n");
        exit(0);
    }

    write(fd, buf, strlen(buf));
    if(lseek(fd, 0, SEEK_END) != 23) {
        printf("lseek bad8\n");
        exit(0);
    }

    if(lseek(fd, 5, SEEK_SET) != 5) {
        printf("lseek bad9\n");
        exit(0);
    }

    if(lseek(fd, 14, SEEK_SET) != 14) {
        printf("lseek bad10\n");
        exit(0);
    }

    read(fd, ans, strlen(buf));
    
    printf("%s", ans);
    close(fd);
    exit(0);
}
