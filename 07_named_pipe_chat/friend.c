#include "header.h"

int main(void){
    int infd,outfd;
    char line[MAX];
    ssize_t n = 0;

    if((infd = open("fifo1",O_RDONLY)) < 0){
        perror("open()");
        exit(EXIT_FAILURE);
    }
    if((outfd = open("fifo2",O_WRONLY)) < 0){
        perror("open()");
        exit(EXIT_FAILURE);
    }



    while(TRUE){
        n = read(infd,line,sizeof(line));
        if(n <= 0){
            perror("read()");
            exit(EXIT_FAILURE);
        }

        line[n] = '\0';
        printf("friend: %s",line);

        printf("you: ");
        fflush(stdout);

        if(fgets(line,sizeof(line),stdin) == NULL)
            break;

        if(write(outfd,line,strlen(line)) < 0){
            perror("write()");
            exit(EXIT_FAILURE);
        }
    }
}