#include <stdio.h>
#include "encrypt.h"
#include "decrypt.h"

int main(int argc, char* argv[]){
	int i;
	unsigned int ecb_input = 0x616261;
	uint32_t key_v = 0x98267351;
	unsigned int iv = 0x42;
	
	//uint128_t chain_input = 0x68656c6c6f20776f726c64;
	//divide chain_input because its too large for unsigned int
	unsigned int chain_input1 = 0x68656c; // first 23 bits
	unsigned int chain_input2 = 0x6c6f2077; //next 32 bits
	unsigned int chain_input3 = 0x6f726c64; //last 32 bits
	
	//unsinged int cyphered text = 0x3451f6fd3b6126e0ae5815;
	//divide cyphered text because its too large for unsigned int
	unsigned int cypher_text1 = 0x3451f6;
	unsigned int cypher_text2 = 0xfd3b6126;
	unsigned int cypher_text3 = 0xe0ae5815;
		
	unsigned int ecb_result = encrypt(key_v, ecb_input, CHAIN_OFF, iv);

	/* for first iteration use iv
	 * for other iterations use last 8 bits of previous result/cyphered text 
	 * as input is divided
	 */
	unsigned int chain_result1 = encrypt(key_v, chain_input1, CHAIN_ON, iv);	
	unsigned int chain_result2 = encrypt(key_v, chain_input2, CHAIN_ON , isoMask(chain_result1,8,8));
	unsigned int chain_result3 = encrypt(key_v, chain_input3, CHAIN_ON, isoMask(chain_result2,8,8));
	
	unsigned int decypher1 = decrypt(key_v, cypher_text1, CHAIN_ON, iv);	
	unsigned int decypher2 = decrypt(key_v, cypher_text2, CHAIN_ON , isoMask(cypher_text1,8,8));
	unsigned int decypher3 = decrypt(key_v, cypher_text3, CHAIN_ON, isoMask(cypher_text2,8,8));
	
	printf("ECB Cypher: %x\n", ecb_result); 
	printf("Chain Cypher: %x%x%x\n", chain_result1, chain_result2, chain_result3);
	printf("Decyphered text: %x%x%x\n", decypher1, decypher2, decypher3);
	
	
	return 0;	
}
