#include <stdio.h>

int stringlength(char *str);
int isitaletter(char c);
void stringcopy(char *source, char *dest);
void stringcat(char *dest, char *source);
int stringcompare(char *str1, char *str2);
char *strdup(char *str);

int main(void)
{
   char s1[20];
   char s2[20];
   printf("Enter a string: ");
   scanf("%s", &s1);
   printf("Enter a string: ");
   scanf("%s", &s2);
   printf("value = %d\n", stringcompare(s1, s2));

   return 0;
}
//===============================================================

int stringlength(char *str) {
	int length = 0;
	while(*str != '\0') {
		length++;
		str++;
	}
	return length;
}
//----------------------------------------------------------------

int isitaletter(char c) {
	return (c >= 'A' && c <= 'z');
}
//----------------------------------------------------------------

void stringcopy(char *source, char *dest) {
	while(*source != '\0') {
		*dest = *source;
		dest++;
		source++;
	}

	*dest = '\0'; // Append the null terminator
}
//----------------------------------------------------------------

void stringcat(char *dest, char *source) {
	while(*dest != '\0') dest++; // Move dest to the end, so we can start appending
	while(*source != '\0') {
		*dest = *source;
		dest++;
		source++;
	}

	*dest = '\0'; // Add the null terminator at the new end
}
//----------------------------------------------------------------

int stringcompare(char *str1, char *str2){
   while(*str1 != '\0' && *str2 != '\0'){
      if(*str1 != *str2)
         break;
      str1++;
      str2++;
   }
   if(*str1 != *str2)
      return 0;
   else
      return 1;
}
//----------------------------------------------------------------

/*char *strdup(char *str) {
	int length = strlen(str);
	char *ret = malloc(len*sizeof(char));

	int i;
	// Goes to length + 1 to also copy the null terminator
	for(i = 0; i < length + 1; i++) {
		ret[i] = str[i];
	}

	return ret;
}*/
