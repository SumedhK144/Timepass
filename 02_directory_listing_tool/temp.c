#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

int main(void){
    DIR* dp = NULL;
    struct dirent *buffer = NULL;

    dp = opendir("/home/sumedh");
    if(dp == NULL){
        perror("opendir()");
        exit(EXIT_FAILURE);
    }

    while((buffer = readdir(dp)) != NULL)
        printf("filename: %-10.10s\t inode: %-5ld\n",buffer->d_name,(unsigned long)buffer->d_ino);

    closedir(dp);

    return 0;
}
