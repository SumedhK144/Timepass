#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
    pid_t pid;
    int status = 0;

    if((pid = fork()) < 0){
        perror("fork()");
        exit(EXIT_FAILURE);
    }else if(pid == 0){
        puts("---CHILD Process Info----");
        printf("pid: %ld\n",getpid());
        printf("gid: %ld\n",getgid());
        printf("ppid: %ld\n",getppid());
        printf("sid (Session id): %ld\n",getsid(0));
        exit(EXIT_SUCCESS);
    }else{
        wait(&status);
        puts("----PARENT process Info-----");
        printf("pid: %ld\n",getpid());
        printf("gid: %ld\n",getgid());
        printf("ppid: %ld\n",getppid());
        printf("sid (Session id): %ld\n",getsid(0));
        exit(EXIT_SUCCESS);
    }

    exit(EXIT_FAILURE);
}