#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(void){
    pid_t pid;
    int fd[2];
    char* msg = "Hello From Parent";
    int status = 0;

    if(pipe(fd) < 0){
        perror("pipe()");
        exit(EXIT_FAILURE);
    }

    if((pid = fork()) < 0){
        perror("fork()");
        exit(EXIT_FAILURE);
    }else if(pid == 0){
        close(fd[1]);

        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);

        if(execl("c",(char*)0) < 0)
            perror("execl()");
    }else{
    
        close(fd[0]);
        write(fd[1],msg,strlen(msg));
        close(fd[1]);
        
        wait(&status);

        exit(EXIT_SUCCESS);
    }

}