#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>


void list_dir(DIR* dp);

int main(int argc,char* argv[]){
    if(argc == 1){
        puts("Arguments should be more that one");
        exit(EXIT_FAILURE);
    }

    int i = 1;
    while(argv[i] != NULL){
        DIR* dp = NULL;

        if((dp = opendir(argv[i])) == NULL){
            perror("opendir()");
        }
        printf("----------Contents of %s-----------\n",argv[i]);
        list_dir(dp);
        printf("=================================================\n");
        i++;
    }

    
}

void list_dir(DIR* dp){
    struct dirent* p_buffer = NULL;

    while((p_buffer = readdir(dp)) != NULL){
        printf("Filename: %-13.10s\tInode: %-7ld\n",p_buffer->d_name,
                (unsigned long)p_buffer->d_ino);
    }

    closedir(dp);
}