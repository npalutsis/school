#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	// printf("hello world (pid:%d)\n", (int) getpid());
	int rc = fork();

	if (rc < 0) { // fork failed; exit
		fprintf(stderr, "Fork failed.\n");
		exit(1);
	} else if (rc == 0) { // child (new process)
		// printf("Hello, I am child (pid:%d)\n", (int) getpid());
		char *myargs[4];
		myargs[0] = strdup("cp"); // program: "cp"
		myargs[1] = strdup(argv[1]); // argument: file to copy
		myargs[2] = strdup("CloneFile");
		myargs[3] = NULL; // marks end of array
		execvp(myargs[0], myargs); // copies input to Clonefile
		// printf("This shouldn’t print out.\n");
	} else { // parent goes down this path (main)
		int cp = wait(NULL);
		// printf("hello, I am parent of %d (cp:%d) (pid:%d)\n",
		// rc, cp, (int) getpid());

        char *myargs[3];
		myargs[0] = strdup("md5sum"); // program: "md5sum"
        myargs[1] = strdup(argv[1]); // argument: file to copy
        myargs[2] = NULL; // marks end of array
        execvp(myargs[0], myargs); // runs md5sum on input file

        myargs[0] = strdup("md5sum"); // program: "md5sum"
        myargs[1] = strdup("CloneFile"); // argument: copied file
        myargs[2] = NULL; // marks end of array
        execvp(myargs[0], myargs); // runs md5sum on CloneFile
	}
	return 0;
}
