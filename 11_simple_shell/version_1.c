#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


#define MAX_WORDS 100
#define TRUE 1

char** parse_string(char* inpstr);

int main(void){
    char* inputString = NULL;
    char** argv = NULL;
    pid_t childPid;
    size_t n = 0,readChars = 0;

    int status = 0;

    while(TRUE){
        printf("\t\t\t Welcome to my Custom mini shell \n");
        printf("usr > ");
        readChars = getline(&inputString,&n,stdin);
        inputString[strcspn(inputString, "\n")] = '\0';
        argv = parse_string(inputString);
        
        if(argv[0] == NULL)
            continue;

        switch(fork()){
            case -1:
                perror("fork()");
                exit(EXIT_FAILURE);

            case 0:
                if(execvp(argv[0], argv) < 0){
                    perror("execvp()");
                    _exit(EXIT_FAILURE);
                }
                break;

            default:
                waitpid(-1,&status,0);
                break;
        }
        printf("\n");
    }

    for(int i = 0; argv[i] != NULL; i++)
        free(argv[i]);
    free(argv);

    exit(EXIT_SUCCESS);
}


char** parse_string(char* inpstr){
    char** words = NULL;
    int i,j,k;
    int start,length;

    words = (char**)malloc(sizeof(char*) * MAX_WORDS);
    if(words == NULL){
        perror("malloc()");
        exit(EXIT_FAILURE);
    }
    i = j = k = 0;

    while(inpstr[i] != '\0'){
        while(inpstr[i] == ' ')
            i++;

        if(inpstr[i] == '\0')
            break;

        start = i;

        while(inpstr[i] != '\0' && inpstr[i] != ' ')
            i++;

        length = i - start;

        words[j] = (char*)malloc(length + 1);

        for(k = 0; k < length; k++)
            words[j][k] = inpstr[start + k];

        words[j][k] = '\0';
        j++;
    }
    
    words[j] = NULL;
    return words;
}