#include<stdio.h>
#include<unistd.h>
int main()
{
    pid_t cpid;
    cpid = fork();
    if(cpid == 0){
        printf("It is a child process \n");
        printf("Process ID: %d\n", getpid());
        printf(" Parent ID: %d\n", getppid());
    } 
    else{
        printf("It is Parent process \n");
        printf("Process ID: %d\n", getpid());
        printf("  Child ID: %d\n", cpid);
    }
}