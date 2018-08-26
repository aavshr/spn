#include <stdio.h>
#include "encrypt.h"
#include "decrypt.h"

int main(int argc, char* argv[]){
	unsigned int ecb_input;
	uint32_t key_v;
	unsigned int iv;
	unsigned int chain = 0;

	if(argc!=5){
		fprintf(stderr, "Usage: spn <key> <initialization vector> <clear text> <chain flag>\n");
		return 0;
	}

	key_v = atoi(argv[1]);
	iv = atoi(argv[2]);
	ecb_input = atoi(argv[3]);
	chain = atoi(argv[4]);
	
	fprintf(stdout, "Encrypted: %x\n", encrypt(key_v,ecb_input, chain, iv));  
	return 0;	
}
