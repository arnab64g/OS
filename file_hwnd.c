#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
int main()
{
    int p = open("file.txt", O_RDONLY | O_WRONLY);
    if(p < 0){
        printf("Creating file ..");
        p = open("file.txt", O_CREAT | O_RDONLY | O_WRONLY);
    }
    printf("\nFile: file.txt: %d\n", p);
    char s[200];
    printf("\nWrite 5 lines:\n");
    for (int i = 0; i < 5; i++){
        write(p, s, read(1, s, 100));
    }
    close(p);
    printf("\nFile Closed -- file.txt");
    printf("\nChecking file.txt contents.\n");
    p = open("file.txt", O_RDONLY);
    int p1 = open("file1.txt", O_CREAT | O_WRONLY | O_RDONLY);
    write(1, s, read(p, s, 200));
    close(p);
    p = open("file.txt", O_RDONLY);
    printf("\nCoppy from file.txt to file1.txt...\n");
    write(p1, s, strlen(s));
    close(p);
    close(p1);
    printf("\nBoth file Closed\n");
    printf("\nChecking Coppied Contents on file1.txt\n");
    p1 = open("file1.txt", O_RDONLY);    
    write(1, s, read(p1, s, strlen(s)));
    close(p1);
    return 0;
}