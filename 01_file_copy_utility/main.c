#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


#define BUFFER_SIZE     4096
#define SUCCESS     1
#define FAILURE     -1
#define FILE_MODES  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

typedef int status_t;
typedef int descriptor_t;

char buffer[BUFFER_SIZE];

status_t copy_files(descriptor_t src_fd,descriptor_t dest_fd);

int main(void){
    char src_file[BUFFER_SIZE];
    char dest_file[BUFFER_SIZE];
    status_t status;
    descriptor_t src_fd,dest_fd;
    
    system("clear");
    
    puts("\t\t\t\tFile Copy Utility");
    
    printf("\t\t- Enter Source File name: ");
    scanf("%s",src_file);
    
    printf("\t\t- Enter Dest File name: ");
    scanf("%s",dest_file);
    

    if((src_fd = open(src_file,O_RDONLY)) < 0){
        perror("\t\tsrc open()");
        puts("\t\t=>Unable to copy file");
        exit(EXIT_FAILURE);
    }

    if((dest_fd = open(dest_file,O_WRONLY | O_CREAT | O_TRUNC,FILE_MODES))< 0){
        perror("\t\tdest open()");
        exit(EXIT_FAILURE);
    }

    status = copy_files(src_fd,dest_fd);
    if(status == SUCCESS){
        printf("\t\t=>%s copied to %s Successfully!!\n",src_file,dest_file);
        exit(EXIT_SUCCESS);
    }
    else
        exit(EXIT_FAILURE);


}


status_t copy_files(descriptor_t src_fd,descriptor_t dest_fd){
    ssize_t n = 0;

    while((n = read(src_fd,buffer,BUFFER_SIZE)) > 0)
       if(write(dest_fd,buffer,n) != n)
           perror("write()");

    if(n < 0){
        perror("read()");
        return FAILURE;
    }
    
    return SUCCESS;
}
