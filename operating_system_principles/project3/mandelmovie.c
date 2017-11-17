#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
 
int main(int argc, char **argv){
 
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
    double x = 0.286932;
    double y = 0.014287;
    double s = 0.000001;
    double iter = (2-s)/49;
    int i, j;

    for (i = 0; i < 50; i = i + nProcesses) {
        for (j = 0; j < nProcesses; ++j) {
            if( i + j < 50) {
                if ((pids[j] = fork()) < 0){
                    printf("error: %s\n", strerror(errno));
                    exit(EXIT_FAILURE);
                } else if (pids[j] == 0){
                    char command[100];
                    // sprintf(command, "./mandel -x %f -y %f -s %f -W 1500 -H 1500 -m 2000 -o mandel%i.bmp", x, y, 2-((i+j)*iter), (i+j)+1);
                    sprintf(command, "./mandel -x 0.2869325 -y 0.0142905 -s .000001 -W 1024 -H 1024 -m 1000");
                    system(command);
                    exit(EXIT_SUCCESS);
                }
            }
        }
        int status;
        int current = nProcesses;
        pid_t PID;
        while (current > 0){
            current--;
            PID = wait(&status);
        }
    }
}