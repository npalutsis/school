#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>

#define BUFFER_LEN 4098

int stringIsInt(char *);

int main (int argc, char *argv[]) {

    // check if program was run properly
    if (argc != 1) {
        printf("myshell: Usage: ./myshell\n");
        exit(EXIT_FAILURE);
    }

    char input[BUFFER_LEN];     // command input string
    char* words[100];           // parsed command arguments
    int nwords;                 // number of words
    int rc;                     // return code
    int temp;                   // temporary variable

    while (1) {

        input[4097] = '\0';                     // max size is 4096

        printf("myshell> ");                    // shell prompt
        fflush(stdout);       

        if (!fgets(input, BUFFER_LEN, stdin))   // quits if EOF
            break;
        if (input[4097] != '\0') {              // exceeded character limit
            fprintf(stderr,"myshell: input error: exceeded the maximum character limit of 4096\n");
            continue;
        }        
        size_t length = strlen(input);
        if (input[length - 1] == '\n')          // remove new line character
            input[length - 1] = '\0';

        if (strcmp(input, "quit") == 0 || strcmp(input, "exit") == 0)   //check if user quits
            break;

        char *token;                            // parse input into separate strings
        nwords = 0;
        token = strtok(input, " \t\n");

        if (token == "\n" || token == NULL)     // skips to top of loop if user hits 'enter'
            continue;

        char *command = token;                  // store command separate from arguments
        token = strtok(NULL, " \t\n");

        while (token != NULL) {                 // break when done parsing arguments
            words[nwords] = token;      
            token = strtok(NULL," \t\n");
            nwords++;
            if (nwords >= 100) {                // break if user exceeds word limit
                printf("myshell: Warning: myshell will only reads the first 100 words\n");
                break;
            }
        }
        words[nwords] = NULL;                   //set last value to NULL for execvp

        if (strcmp(command, "start") == 0) {

            if (words[0] == NULL) {
                printf("myshell: Usage: start [program] {arguments}\n");
                continue;
            }

            rc = fork();                        // fork child

            if (rc < 0) {                       // fork failed
                fprintf(stderr, "myshell: start error: %s", strerror(errno));
                exit(EXIT_FAILURE);
            } else if (rc == 0) {               // child
                if (execvp(words[0],words) == -1)
                    fprintf(stderr, "myshell: start error: %s", strerror(errno));
                exit(EXIT_FAILURE);
            } else {                            // parent
                printf("myshell: process %d started\n", rc);
            }

        } else if (strcmp(command, "wait") == 0) {
            pid_t status;
            rc = waitpid(-1, &status, 0);
        
            if (rc < 0) {                       // if waitpid fails
                if (errno == ECHILD) {
                    fprintf(stderr, "myshell: wait error: no processes to wait for\n");
                } else {
                    fprintf(stderr, "myshell: wait error: %s\n", strerror(errno));
                    exit(EXIT_FAILURE);
                }
            } else {                            // waitpid succeeded -> check exit status
                if (WIFSIGNALED(status)) {
                    printf("myshell: process %d exited abnormally with signal %d: %s\n", rc, WTERMSIG(status), strsignal(status));
                } else if (WIFEXITED(status)) {
                    printf("myshell: process %d exited normally with status %d\n", rc, WEXITSTATUS(status));
                }
            }          

        } else if (strcmp(command, "run") == 0) {

            if (words[0] == NULL) {
                printf("myshell: usage: start [program] {arguments}\n");
                continue;
            }

            rc = fork();                        // fork child

            if (rc < 0) {                       // fork failed
                fprintf(stderr, "myshell: run error: %s", strerror(errno));
                exit(EXIT_FAILURE);
            } else if (rc == 0) {               // child
                if (execvp(words[0],words) == -1)
                    fprintf(stderr, "myshell: run error: %s", strerror(errno));
                exit(EXIT_FAILURE);
            } else {                            // parent
                printf("myshell: process %d started\n", rc);
            }  

            pid_t status;
            rc = waitpid(rc, &status, 0);
        
            if (rc < 0) {                       // if waitpid fails
                if (errno == ECHILD) {
                    fprintf(stderr, "myshell: run error: no processes to wait for\n");
                } else {
                    fprintf(stderr, "myshell: run error: %s\n", strerror(errno));
                    exit(EXIT_FAILURE);
                }
            } else {                            // waitpid succeeded -> check exit status
                if (WIFSIGNALED(status)) {
                    printf("myshell: process %d exited abnormally with signal %d: %s\n", rc, WTERMSIG(status), strsignal(status));
                } else if (WIFEXITED(status)) {
                    printf("myshell: process %d exited normally with status %d\n", rc, WEXITSTATUS(status));
                }
            } 

        } else if (strcmp(command, "kill") == 0) {

            if (words[0] == NULL) {             // PID entered as argument
                fprintf(stderr, "myshell: kill error: kill requires a proper PID\n");
                continue;
            }

            if (stringIsInt(words[0])) {        // argument is a number
                temp = atoi(words[0]);
                if (temp != 0) {                // if string could be converted to int
                    rc = kill(temp, SIGKILL);   // kill the process
                    if (rc == 0) {
                        printf("myshell: process %d killed\n", temp);
                    } else {
                        if (errno == ESRCH) {
                            fprintf(stderr, "myshell: kill error: the entered PID does not refer to an existing process\n");
                        } else {
                            fprintf(stderr, "myshell: kill error: %s\n", strerror(errno));
                        }
                    }
                } else {        // argument is not a number
                    fprintf(stderr, "myshell: error: kill requires a proper PID\n");
                }
            } else {            // argument is a number
                fprintf(stderr, "myshell: error: kill requires a proper PID\n");
            }
            
        } else if (strcmp(command, "stop") == 0) {
            
            if (words[0] == NULL) {             // PID entered as argument
                fprintf(stderr, "myshell: stop error: stop requires a proper PID\n");
                continue;
            }

            if (stringIsInt(words[0])) {        // argument is a number
                temp = atoi(words[0]);
                if (temp != 0) {                // if string could be converted to int
                    rc = kill(temp, SIGSTOP);   // stop the process
                    if (rc == 0) {
                        printf("myshell: process %d stopped\n", temp);
                    } else {
                        if (errno == ESRCH) {
                            fprintf(stderr, "myshell: stop error: the entered PID does not refer to an existing process\n");
                        } else {
                            fprintf(stderr, "myshell: stop error: %s\n", strerror(errno));
                        }
                    }
                } else {        // argument is a number
                    fprintf(stderr, "myshell: stop error: stop requires a proper PID\n");
                }
            } else {            // argument is a number
                fprintf(stderr, "myshell: stop error: stop requires a proper PID\n");
            }

        } else if (strcmp(command, "continue") == 0) {
            
            if (words[0] == NULL) {             // PID entered as argument
                fprintf(stderr, "myshell: continue error: continue requires a proper PID\n");
                continue;
            }

            if (stringIsInt(words[0])) {        // argument is a number
                temp = atoi(words[0]);
                if (temp != 0) {                // if string could be converted to int
                    rc = kill(temp, SIGCONT);   // continue the process
                    if (rc == 0) {
                        printf("myshell: process %d continueed\n", temp);
                    } else {
                        if (errno == ESRCH) {
                            fprintf(stderr, "myshell: continue error: the entered PID does not refer to an existing process\n");
                        } else {
                            fprintf(stderr, "myshell: continue error: %s\n", strerror(errno));
                        }
                    }
                } else {        // argument is a number
                    fprintf(stderr, "myshell: continue error: continue requires a proper PID\n");
                }
            } else {            // argument is a number
                fprintf(stderr, "myshell: continue error: continue requires a proper PID\n");
            }

        } else {
            fprintf(stderr, "myshell: unkown command: %s\n", command);
        }
    }
} 

int stringIsInt (char *c) {
    if (!*c) 
        return 0;
    for (int i = 0; c[i] != NULL; i++) {
        if (i == 0 && c[i] == '-') {}           // checks if number is negative
        else if (!isdigit(c[i])) {return 0;}    // checks if number
    }
    return 1;
}