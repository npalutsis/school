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

	int keyFlag = 0;
	int encryptFlag = 0;
	int decryptFlag = 0;
	int c;

	opterr = 0;

	// Read in flag value
	while ((c = getopt (argc, argv, "kedh")) != -1) {
		switch (c) {
			case 'k':
				keyFlag = 1;
				break;
			case 'e':
				encryptFlag = 1;
				break;
			case 'd':
				decryptFlag = 1;
				break;
			case 'h':
				printf("For mode k: ./main -[k] [basename]\n");
				printf("For modes e & d: ./main [-e | -d] [secret key] [public key] [nonce] [input file] [output file]\n");
				printf("\nModes:\n");
				printf("-k = key generation\n");
				printf("-e = encryption\n");
				printf("-d = decryption\n");
				return 0;
				break;
			default:
				printf("Aborting...\n");
				abort();
		}
	}

	unsigned char secretKey[crypto_box_SECRETKEYBYTES];
	unsigned char publicKey[crypto_box_PUBLICKEYBYTES];

	char * publicFile[sizeof(argv[2]) + 7];
	char * secretFile[sizeof(argv[2]) + 7];

	memcpy(publicFile, argv[2], sizeof(argv[2]));
	memcpy(secretFile, argv[2], sizeof(argv[2]));

	if (keyFlag) {

		if (argc != 3) {
			printf("Unexpected input. Use -h for further help.\n");
			return -1;
		}

		printf("Generating keys...\n");
		strcat(publicFile, ".public");
		strcat(secretFile, ".secret");

		crypto_box_keypair(publicKey, secretKey);

		// Output to files
		FILE * fp;
		fp = fopen(publicFile , "w");
		if (fp) {
			fwrite(publicKey, 1, crypto_box_PUBLICKEYBYTES, fp);
			fclose(fp);			
		} else {
			printf("Something went wrong delivering the public key\n");
			return -1;
		}

		fp = fopen(secretFile, "w");
		if (fp) {
			fwrite(secretKey, 1, crypto_box_SECRETKEYBYTES, fp);
			fclose(fp);
		} else {
			printf("Something went wrong delivering the public key\n");
			return -1;
		}

		printf("Done\n");


	} else if (encryptFlag) {

		// Ensure proper number of input arguments
		if (argc != 7) {
			printf("Unexpected input. Use -h for further help.\n");
			return -1;
		}

		// Load input file
		FILE * fp;
		fp = fopen(argv[5], "rb");
		fseek(fp, 0, SEEK_END);
		int inputSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		char * inputData = malloc(sizeof(unsigned char) * inputSize);
		fread(inputData, inputSize, 1, fp);
		inputData = malloc(sizeof(unsigned char) * inputSize);
		if (inputData) {
			fread(inputData, inputSize, 1, fp);
		} else {
			printf("Something went wrong opening the input file\n");
			return -1;
		}
		fclose(fp);

		unsigned char nonce[crypto_box_NONCEBYTES];
		unsigned char inputFile[inputSize];
		unsigned char outputFile[inputSize];
		unsigned char encrypted[inputSize + crypto_box_MACBYTES];

		memcpy(nonce, argv[4], sizeof(nonce));
		memcpy(inputFile, inputData, sizeof(inputFile));
		memcpy(outputFile, inputData, sizeof(outputFile));

		// Load public key
		fp = fopen(argv[3], "rb");
		fseek(fp, 0, SEEK_END);
		int publicSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		char * publicData = malloc(sizeof(unsigned char) * publicSize);
		if (publicData) {
			fread(publicData, publicSize, 1, fp);
		} else {
			printf("Something went wrong opening the public key\n");
			return -1;
		}
		fclose(fp);

		// Load secret key
		fp = fopen(argv[2], "rb");
		fseek(fp, 0, SEEK_END);
		int secretSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		char * secretData = malloc(sizeof(unsigned char) * secretSize);
		if (secretData) {
			fread(secretData, secretSize, 1, fp);
		} else {
			printf("Something went wrong opening the secret key\n");
			return -1;
		}
		fclose(fp);

		printf("Encrypting...\n");
		if (crypto_box_easy(encrypted, inputData, inputSize, nonce, publicData, secretData) != 0) {
			printf("Something went wrong during encryption\n");
			return -1;
		} else {
			fp = fopen(argv[6], "w");
			fwrite(encrypted, 1, sizeof(encrypted), fp);
			fclose(fp);
		}
		printf("Done\n");

	} else if (decryptFlag) {

		// Ensure proper number of input arguments
		if (argc != 7) {
			printf("Unexpected input. Use -h for further help.\n");
			return -1;
		}

		// Load the input file
		FILE *fp;
		fp = fopen(argv[5],"r");
		fseek(fp, 0, SEEK_END);
		int inputSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		char * inputData = malloc(sizeof(unsigned char) * inputSize);
		if (inputData) {
			fread(inputData, inputSize, 1, fp);
		} else {
			printf("Something went wrong opening the input file\n");
			return -1;
		}
		fclose(fp);

		unsigned char nonce[crypto_box_NONCEBYTES];
		unsigned char inputFile[inputSize];
		unsigned char outputFile[inputSize];
		unsigned char decrypted[inputSize];

		memcpy(nonce, argv[4], sizeof(nonce));
		memcpy(inputFile, inputData, sizeof(inputFile));
		memcpy(outputFile, inputData, sizeof(outputFile));

		// Load public key
		fp = fopen(argv[3], "rb");
		fseek(fp, 0, SEEK_END);
		int publicSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		char * publicData = malloc(sizeof(unsigned char) * publicSize);
		if (publicData) {
			fread(publicData, publicSize, 1, fp);
		} else {
			printf("Something went wrong opening the public key\n");
			return -1;
		}
		fclose(fp);

		// Load secret key
		fp = fopen(argv[2], "rb");
		fseek(fp, 0, SEEK_END);
		int secretSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		char * secretData = malloc(sizeof(unsigned char) * secretSize);
		if (secretData) {
			fread(secretData, secretSize, 1, fp);
		} else {
			printf("Something went wrong opening the secret key\n");
			return -1;
		}
		fclose(fp);

		printf("Decrypting...\n");
		// printf("Decrypted: %s\n", decrypted);
		// printf("InputData: %s\n", inputData);
		// printf("InputSize: %d\n", inputSize);
		// printf("Nonce: %s\n", nonce);
		// printf("PublicData: %s\n", publicData);
		// printf("SecretData: %s\n", secretData);
		if (crypto_box_open_easy(decrypted, inputData, inputSize, nonce, publicData, secretData) != 0) {
			printf("Someting went wrong during decryption\n");
			return -1;
		} else {
			fp = fopen(argv[6], "w");
			fwrite(decrypted, 1, inputSize - crypto_box_MACBYTES , fp);
			fclose(fp);
		}
		printf("Done\n");
				
	} else {

		printf("Sorry, something went wrong.\n");
		return -1;

	}

	return 0;
}