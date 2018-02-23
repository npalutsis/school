#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sodium.h>

int main (int argc, char **argv) {
    // if (sodium_init() < 0) {
        /* panic! the library couldn't be initialized, it is not safe to use */
        // printf("Trouble loading Sodium library...\n");
        // return -1;
    // }

	int encryptFlag = 0;
	int decryptFlag = 0;
	char key[256];
	char nonce[192];
	char inputFile[50];
	char outputFile[50];
	char *cvalue = NULL;
	int index;
	int c;

	opterr = 0;

	// if (argc != 6) {
	//   printf("Unexpected input. Use -h for further help.\n");
	//   return -1;
	// }

	// Read in flag
	while ((c = getopt (argc, argv, "edh")) != -1) {
		switch (c) {
			case 'e':
				encryptFlag = 1;
				printf("Encrypting...\n");
				break;
			case 'd':
				decryptFlag = 1;
				printf("Decrypting...\n");
				break;
			case 'h':
				printf("./p1 -[action] [key] [nonce] [input file] [output file]\n");
				printf("-e = encryption\n");
				printf("-d = decryption\n");
				return 0;
				break;
			default:
				abort ();
		}
	}

	if (argc != 6) {
	  printf("Unexpected input. Use -h for further help.\n");
	  return -1;
	}

	// Read in inputs
	memcpy(key, argv[2], sizeof(key));
	memcpy(nonce, argv[3], sizeof(nonce));
	memcpy(inputFile, argv[4], sizeof(inputFile));
	memcpy(outputFile, argv[5], sizeof(outputFile));

	printf("%s\n%s\n%s\n%s\n", key, nonce, inputFile, outputFile);

	char * buffer = 0;
	long length;
	FILE * f = fopen (inputFile, "rb");

	if (f) {
		fseek (f, 0, SEEK_END);
		length = ftell (f);
		fseek (f, 0, SEEK_SET);
		buffer = malloc (length);
		if (buffer) {
			fread (buffer, 1, length, f);
		}
		fclose (f);
	}
	char * ciphertext = 0;

	if (buffer) {
		// start to process your data / extract strings here...
		printf("%s\n", buffer);
		crypto_secretbox(ciphertext, buffer, sizeof(buffer), nonce, key);
	}

	printf("%s\n", ciphertext);

	// Output to file
	FILE *fp = fopen(outputFile, "w");
	if (fp != NULL)
	{
		fputs(ciphertext, fp);
		fclose(fp);
	}

	// printf ("encryptFlag = %d, decryptFlag = %d, cvalue = %s\n",
	// 				encryptFlag, decryptFlag, cvalue);

	// for (index = optind; index < argc; index++)
	// 	printf ("Non-option argument %s\n", argv[index]);
	return 0;
}