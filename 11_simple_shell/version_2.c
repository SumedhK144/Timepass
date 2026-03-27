/*
    This programm is for only one pipe
    e.g. echo "hello" | wc
         ls -l | wc 
    means i've handled the one one io redirection using pipe
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
 

#define TRUE    1
#define MAX_WORDS    100

char** parseCommands(char* inputStr);

int main(void){
    char* inpCmd = NULL;
    char** parsedCmd = NULL;
    int fd[2];

    while(TRUE){
        printf("usr > ");
        getline(&inpCmd,NULL,stdin);
        parsedCmd = parseCommands(inpCmd);
        
        if(pipe(fd) < 0){
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        switch(fork()){
            case -1:
                perror("fork()");
                exit(EXIT_FAILURE);

            case 0:
                close(fd[0]);
                dup2(fd[1],STDOUT_FILENO);
                if(execlp()) //problem arised here 
        }
    }
}


char** parseCommands(char* inputStr){
    char** ppCommands = NULL;
    char* start = NULL;
    char* ptr = NULL;
    int i = 0;

    ppCommands = (char**)malloc(MAX_WORDS * sizeof(char*));
    if(ppCommands == NULL){
        perror("malloc()");
        exit(EXIT_FAILURE);
    }

    start = inputStr;
    ptr = inputStr;
    i = 0;

    while(*ptr){
        if(*ptr == '|'){
            ptr = '\0';

            ppCommands[i++] = strdup(start);
            start = ptr + 1; 
        }
        ptr++;
    }

    ppCommands[i++] = strdup(start);
    ppCommands[i] = NULL;
    return ppCommands;
}