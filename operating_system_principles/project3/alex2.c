//Alex Mukasyan
//Project 03
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
 
int main(int argc, char **argv){
    float x = 0.38941;
    float y = -0.265;
    float s = 0.000001;
 
    if (argc < 2){
        printf("Missing arguments\n");
        printf("Usage ./mandelmovie <# of processes>\n");
    }else if(argc > 2){
        printf("Too many arguments\n");
        printf("Usage ./mandelmovie <# of processes>\n");
    }else{
        int numproc = atoi(argv[1]);
        float iter = (2-s)/49;
        pid_t pids[numproc];
 
        int i, j;
 
        for(i = 0; i < 50; i = i+numproc){
            for(j = 0; j < numproc; ++j){
                if(i + j < 50){
                    if((pids[j] = fork()) < 0){
                        printf("error: %s\n",strerror(errno));
                        exit(EXIT_FAILURE);
                    }else if(pids[j] == 0){
                        char command[100];
                        sprintf(command, "./mandel -x %F -y %F -s %F -m 2000 -W 1680 -H 1050 -o mandel%i.bmp", x, y, 2-((i+j)*iter), (i+j)+1);
                        system(command);
                        exit(EXIT_SUCCESS);
                    }
                }
            }
            int status, curr = numproc;
            pid_t pid;
            while(curr > 0){
                pid = wait(&status);
                curr--;
            }
        }
    }
 
 
}