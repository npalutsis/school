#include <stdio.h>
#include <ctype.h>

int main(void){
/*   char c;
   int count = 0;
   
   while (scanf("%c", &c) != EOF){
      if (c == '\n'){
         count++;
      }
      if (isupper(c)){
         printf("%c: %d\n", c, c - 'A');
      }
   }
   printf("There are %d lines.\n", count);
   
   return 0;
}
*/
/* declare array */
int frequency[26];
int ch;
FILE* txt_file = fopen ("appleterms.txt", "r");
 
 /* init the freq table: */
for (ch = 0; ch < 26; ch++)
frequency[ch] = 0;
 
   while (1) {
      ch = fgetc(txt_file);
      if (ch == EOF) break; /* end of file or read error.  EOF is typically -1 */
      
      /* assuming ASCII; "letters" means "a to z" */
      if ('a' <= ch && ch <= 'z')      /* lower case */
         frequency[ch-'a']++;
      else if ('A' <= ch && ch <= 'Z') /* upper case */
         frequency[ch-'A']++;
   }
}
