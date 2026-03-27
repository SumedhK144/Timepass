#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_WORDS   100

char** parseCommands(char* inpStr);

int main(void){
    size_t n = 0;
    char* inpline = NULL;
    char** resultString = NULL;

    printf("enter the input string: ");
    getline(&inpline,&n,stdin);
    resultString = parseCommands(inpline);
    int i = 0;
    while(resultString[i] != NULL){
        printf("resultString[%d]: %s\n",i,resultString[i]);
        i++;
    }
}

char** parseCommands(char* inpStr){
    char** commands = (char**)malloc(MAX_WORDS * sizeof(char*));
    if(commands == NULL){
        perror("malloc()");
        exit(EXIT_FAILURE);
    }

    char* start = NULL;
    char* ptr = NULL;
    int i = 0;

    start = inpStr;
    ptr = inpStr;

    while(*ptr){
        if(*ptr == '|'){
            *ptr = '\0';

            commands[i++] = strdup(start);
            start = ptr + 1;
        }
        ptr++;
    }

    //for last command
    commands[i++] = strdup(start);
    commands[i] = NULL;
        
    return commands;
}