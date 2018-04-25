#include <stdio.h>
#include "isolate.h"
#include "permute.h"
#include "subs.h"
#include "key.h"
#include "sp.h"
#include "encrypt.h"
#include "decrypt.h"

static int passed = 0;
static int failed = 0;
static int tests = 0;

// test key step
void test_key(uint32_t key_v, uint8_t value, uint8_t *result){
	int i;
	for(i=0; i<4; i++){	
		if(key(key_v, value, i) != result[i]){
			fprintf(stderr, "Failed Key Step at round %d\n", i);
			failed++;
			tests++;
		}	
		else{
			passed++;
			tests++;
		}
	}
}

//test substitution step
void test_subs(uint8_t value, uint8_t result){
	if(subs(value) != result){
		fprintf(stderr, "Failed Substitution\n");
		failed++;
		tests++;
	}
	else{
		passed++;
		tests++;
	}	
}

void test_subs_decrypt(uint8_t value){
	if (value !=  d_subs(subs(value))){
		fprintf(stderr, "Failed decrypting substitution\n");
		fprintf(stderr, "Value: %d\n",value);
		failed++;
		tests++;
	}
	else{
		passed++;
		tests++;
	}
}
//test permutation step
void test_permutation(uint8_t value, uint8_t result){
	if(permute(value) != result){
		fprintf(stderr, "Failed Permutation\n");     
		failed++;
       	        tests++;
	}
	else{
		passed++;
		tests++;
	}
}

void test_permute_decrypt(uint8_t value){
	if (value !=  d_permute(permute(value))){
		fprintf(stderr, "Failed decrypting permutation\n");
		failed++;
		tests++;
	}
	else{
		passed++;
		tests++;
	}
}

// test substituion-permutation
void test_sp(uint32_t key_v, uint8_t value, uint8_t result){
	if(sp(key_v, value) != result){
		fprintf(stderr, "Failed SP Network\n");     
		failed++;
       	        tests++;
	}
	else{
		passed++;
		tests++;
	}
}

void test_sp_decrypt(uint32_t key_v, uint8_t value){
	if (value !=  d_sp(key_v, sp(key_v, value))){
		fprintf(stderr, "Failed decrypting sp network\n");
		failed++;
		tests++;
	}
	else{
		passed++;
		tests++;
	}
}

//test decrypt
void test_decrypt(uint32_t key_v, unsigned int value, unsigned int iv){
	if(value != decrypt(key_v, encrypt(key_v, value, CHAIN_ON, iv), CHAIN_ON, iv)){
			fprintf(stderr, "Failed Chain Decrypt\n");
			failed++;
			tests++;
	}
	else{
		passed++;
		tests++;
	}
}

int main(){
	unsigned int value = 0x616261, iv = 0x42;
	uint32_t key_v = 0x98267351;
	uint8_t key_results[4] = {103, 217, 140, 174};  
	
	//key step
	test_key(key_v, 255, key_results);
	
	//substitution step
	test_subs(240, 7);	
	test_subs(215, 40);
	test_subs_decrypt(240);
	test_subs_decrypt(215);

	//permutation step
	test_permutation(255, 255);
	test_permutation(215, 95);
	test_permute_decrypt(255);
	test_permute_decrypt(95);

	//substitution-permutation
	test_sp(key_v, 97, 242);
	test_sp_decrypt(key_v, 0xe);
	test_sp_decrypt(key_v, 0x51);
	test_sp_decrypt(key_v, 0xf6);
	test_sp_decrypt(key_v, 0xfd);
			
	//total decrypt
	test_decrypt(key_v, value, iv);

	printf("Tests: %d, Passed: %d, Failed: %d\n", tests, passed, failed);

	return 0;
}
