#Assignment 5  

**Name:** Nick Palutsis  
**Date:** March 27, 2018  

##Question 1  
```
// Question 1, Code auditing, static buffers (15 points)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELIM ","

void parser(char *str, int num_fields)
{
	int i;
	char *buf[24];

	// Constrained the loop to iterate only for the size of buf
	// This prevents writing to memory we do not own
	for (i = 0; i < num_fields && i < sizeof(buf)/sizeof(buf[0]); i++)
	{
		if (i == 0)
			buf[i] = strtok(str, DELIM);
		else
			buf[i] = strtok(NULL, DELIM);

		printf("%s\n", buf[i]);
	}
}

int main(int args, char **argv)
{
	parser(argv[1], atoi(argv[2]));
		
	return(0);
} 
```

##Safe Functions  
strlcpy
strlcat
fgets
snprintf
vsnprintf
strnlen