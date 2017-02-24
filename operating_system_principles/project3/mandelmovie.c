#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
 
int main(int argc, char **argv){
    double x = 0.38941;
    double y = -0.265;
    double s = 0.000001;
 
    // Check for proper usage
    if (argc > 2) {
        printf("Too many arguments\nusage: ./mandelmovie [# of processes]\n");
        exit(EXIT_FAILURE);
    } else if(argc < 2) {
        printf("Not enough arguments\nusage: ./mandelmovie [# of processes]\n");
        exit(EXIT_FAILURE);
    } 

    int nProcesses = atoi(argv[1]);
    pid_t pids[nProcesses];
    double iter = (2-s)/49;

    int i, j;

    for(i = 0; i < 50; i = i + nProcesses){
        for(j = 0; j < nProcesses; ++j){
            if(i + j < 50){
                if((pids[j] = fork()) < 0){
                    printf("error: %s\n", strerror(errno));
                    exit(EXIT_FAILURE);
                }else if(pids[j] == 0){
                    char command[100];
                    sprintf(command, "./mandel -x %f -y %f -s %f -m 2000 -W 1680 -H 1050 -o mandel%i.bmp", x, y, 2-((i+j)*iter), (i+j)+1);
                    system(command);
                    exit(EXIT_SUCCESS);
                }
            }
        }
        int status, curr = nProcesses;
        pid_t pid;
        while(curr > 0){
            curr--;
            pid = wait(&status);
        }
    }
}