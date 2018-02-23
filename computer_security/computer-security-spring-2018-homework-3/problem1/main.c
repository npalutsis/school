#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sodium.h>

int main (int argc, char **argv) {

	if (sodium_init() < 0) {
		// Sodium library was not initialized properly
		printf("Trouble loading Sodium library...\n");
		return -1;
	}

	int encryptFlag = 0;
	int decryptFlag = 0;
	int c;

	opterr = 0;

	// Read in flag value
	while ((c = getopt (argc, argv, "edh")) != -1) {
		switch (c) {
			case 'e':
				encryptFlag = 1;
				break;
			case 'd':
				decryptFlag = 1;
				break;
			case 'h':
				printf("./p1 -[mode] [key] [nonce] [input file] [output file]\n");
				printf("\nModes:\n");
				printf("-e = encryption\n");
				printf("-d = decryption\n");
				return 0;
				break;
			default:
				abort();
		}
	}

	// Ensure proper number of input arguments
	if (argc != 6) {
		printf("Unexpected input. Use -h for further help.\n");
		return -1;
	}

	char * inputData = 0;
	long inputSize;
	FILE * fp = fopen (argv[4], "rb");

	// Read input file
	if (fp) {
		fseek(fp, 0, SEEK_END);
		inputSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		inputData = malloc(sizeof(unsigned char) * inputSize);
		if (inputData) {
			fread(inputData, inputSize, 1, fp);
		}
		fclose(fp);
	} else {
		printf("Something went wrong opening the file\n");
		return -1;
	}

	// Read in remaining inputs
	unsigned char nonce[crypto_secretbox_NONCEBYTES];
	unsigned char key[crypto_secretbox_KEYBYTES];
	unsigned char inputFile[inputSize];
	unsigned char outputFile[inputSize];
	unsigned char encrypted[inputSize + crypto_secretbox_MACBYTES];
	unsigned char decrypted[inputSize];

	memcpy(nonce, argv[3], sizeof(nonce));
	memcpy(key, argv[2], sizeof(key));
	memcpy(inputFile, inputData, sizeof(inputFile));
	memcpy(outputFile, inputData, sizeof(outputFile));

	if (encryptFlag) {

		// Encrypt the data
		if (crypto_secretbox_easy(encrypted, inputData, inputSize, nonce, key) != 0) {
			printf("Something went wrong during encryption\n");
		} else {
			FILE *fp;
			fp = fopen(argv[5], "w");
			fwrite(encrypted, 1 , sizeof(encrypted), fp);
			fclose(fp);
		}

	} else if (decryptFlag) {

		// Decrypt the data
		if (crypto_secretbox_open_easy(decrypted, inputData, inputSize, nonce, key) != 0){
			printf("Something went wrong during decryption\n");
		} else {
			FILE *fp;
			fp = fopen(argv[5], "w");
			fwrite(decrypted, 1, inputSize - crypto_secretbox_MACBYTES, fp);
			fclose(fp);
		}

	} else {

		printf("Sorry, something went wrong.\n");
		return -1;

	}

	return 0;
}