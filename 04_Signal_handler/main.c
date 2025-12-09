/*
Write a program that gracefully handles SIGINT and SIGTERM using signal() or sigaction(). This
introduces asynchronous event handling and teaches you how to perform cleanup operations
before program termination
*/

//execute as
// ./a.out &
// kill -SIGINT PID

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

typedef typeof(void (int)) *sighandler_t;

void handler_function(int signo);
sighandler_t my_signal(int signo,sighandler_t handler);

int main(void){
    if(my_signal(SIGINT,handler_function) == SIG_ERR)
        perror("sigaction()");
    
    if(my_signal(SIGTERM,handler_function) == SIG_ERR)
        perror("sigaction()");
    int choice;


    while(1)
        pause();        

    return 0;
    
}

void handler_function(int signo){
    if(signo == SIGTERM){
        printf("Sigterm received: %d\n",signo);
        printf("Doing Cleanup Operations.....\n");
        sleep(2);
        return;
    }else if(signo == SIGINT){
        printf("SIGTERM received: %d\n",signo);
        printf("Doing Cleanup Operations....\n");
        sleep(2);
        return;
    }else{
        puts("Another signal Accoured");
        printf("signal: %d\n",signo);
    }
}

sighandler_t my_signal(int signo,sighandler_t handler){
    struct sigaction act,oact;

    act.sa_handler = handler_function;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    
    if(sigaction(signo,&act,&oact) == 0)
        return(oact.sa_handler);
    else
        return SIG_ERR;

}
