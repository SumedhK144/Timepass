/*
    Execute Program using
    gcc main.c -o m 
    ./m filename/s
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

#define BUFFER_SIZE 4096

void print_permissions_and_type(struct stat* buf);

int main(int argc, char* argv[]){
    if(argc == 1){
        puts("Arguments should be greater that one");
        exit(EXIT_FAILURE);
    }

    struct stat buffer;
    int i = 1;
    while(argv[i] != NULL){
        char* src_file = argv[i];

        if(stat(src_file,&buffer) < 0)
            perror("stat()");
        
    
        printf("------------------------------------------------------\n");
        printf("File: %-5s\n",src_file);
        
        printf("Size: %-5ld\t\t",buffer.st_size);
        printf("Blocks :%-d\t",buffer.st_blocks);
        printf("IO Block: %-2d\n",buffer.st_blksize);
        
        printf("UID: %-3ld\t",buffer.st_uid);
        printf("GID: %-3ld\t",buffer.st_gid);
        print_permissions_and_type(&buffer);

        printf("Inode no: %-3d\t",buffer.st_ino);
        printf("Link cnt: %-d\t",buffer.st_nlink);
        printf("Device: %d,%d\n",buffer.st_rdev,buffer.st_dev);
        
        printf("Access: %s",ctime(&buffer.st_atime));
        printf("Modify: %s",ctime(&buffer.st_mtime));
        printf("change: %s",ctime(&buffer.st_ctime));
       
        printf("========================================================\n");
        i++;
    }

    exit(EXIT_SUCCESS);
}


void print_permissions_and_type(struct stat* buf){
    printf("Access: ");
    printf((S_IRUSR & buf->st_mode) ? "r" : "-");
    printf((S_IWUSR & buf->st_mode) ? "w" : "-");
    printf((S_IXUSR & buf->st_mode) ? "x" : "-");

    printf((S_IRGRP & buf->st_mode) ? "r" : "-");
    printf((S_IWGRP & buf->st_mode) ? "w" : "-");
    printf((S_IXGRP & buf->st_mode) ? "x" : "-");

    printf((S_IROTH & buf->st_mode) ? "r" : "-");
    printf((S_IWOTH & buf->st_mode) ? "w" : "-");
    printf((S_IXOTH & buf->st_mode) ? "x" : "-");

    printf("\t");

    if(S_ISREG(buf->st_mode))
        printf("REGULAR\n");
    else if(S_ISDIR(buf->st_mode))
        printf("DIR\n");
    else if(S_ISDIR(buf->st_mode))
        printf("DIR\n");
    else if(S_ISCHR(buf->st_mode))
        printf("CHAR DEV\n");
    else if(S_ISBLK(buf->st_mode))
        printf("BLK DEV\n");
    else if(S_ISLNK(buf->st_mode))
        printf("LINK\n");
    else if(S_ISFIFO(buf->st_mode))
        printf("FIFO\n");
    else
        printf("OTHER FILE TYPE");

}