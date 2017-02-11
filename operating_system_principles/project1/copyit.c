#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void displayMessage();
 
int main(int argc, char *argv[])
{
   int bytesCopied = 0;
   char c;
   FILE *source, *destination, *copying, *closing;

   if (argv[3] != NULL) {
      printf("copyit: Too many arguments!\nusage: copyit <sourcefile> <targetfile>\n");
      exit(EXIT_FAILURE);
   }
 
   source = fopen(argv[1], "r");
 
   if (source == NULL)
   {
      printf("copyit: Couldn't open file %s: %s.\n", argv[1], strerror(errno));
      exit(EXIT_FAILURE);
   }
 
   destination = fopen(argv[2], "w");
 
   if (destination == NULL)
   {
      fclose(source);
      printf("copyit: Couldn't create file %s: %s.\n", argv[2], strerror(errno));
      exit(EXIT_FAILURE);
   }
 
   signal(SIGALRM, displayMessage);
   alarm(1);

   while ((c = fgetc(source)) != EOF) {
      // copying = fputc(c, destination);
      if (fputc(c, destination) == EOF) {
         printf("copyit: Couldn't write to file %s: %s.\n", argv[2], strerror(errno));
         exit(EXIT_FAILURE);
      } else {
         bytesCopied += sizeof(c);
      }
   }
 
   // closing = fclose(source);
   if (fclose(source)) {
      printf("copyit: Couldn't close file %s: %s.\n", argv[1], strerror(errno));
      exit(EXIT_FAILURE);
   }

   // closing = fclose(destination);
   if (fclose(destination)) {
      printf("copyit: Couldn't close file %s: %s.\n", argv[2], strerror(errno));
      exit(EXIT_FAILURE);
   }   

   printf("copyit: Copied %d bytes from file %s to %s.\n", bytesCopied, argv[1], argv[2]);
 
   return 0;
}

void displayMessage()
{
   alarm(1);
   printf("copyit: still copying...\n");
}