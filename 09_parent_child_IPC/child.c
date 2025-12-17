#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 1024

int main(void){
    char buffer[MAX];
    ssize_t n = 0;

    n = read(STDIN_FILENO,buffer,MAX);
    if(n == 0){
        perror("read");
    }else{
        buffer[n] = '\0';
    }

    printf("CHILD: %s\n",buffer);
    exit(EXIT_SUCCESS);

}