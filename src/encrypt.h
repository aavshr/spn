#include "isolate.h"
#include "subs.h"
#include "permute.h"
#include "key.h"
#include "sp.h"
#include <math.h>
#include <stdlib.h>

#define CHAIN_ON 1
#define CHAIN_OFF 0

/*encrypt text, divide input into 8 bit chunks and apply sp
 * @param key_v: 32bit key
 * @param value: text to encrypt
 * @param chaining: flag to set block chaining on or off
 * @param iv: initialization vector, if chaining is set on
 * @return encrypted text
 */
unsigned int encrypt(uint32_t key_v, unsigned int value, int chaining, unsigned int iv) {
	unsigned int i, bit_length, no_chunks, final;
	uint8_t* chunks, *results;
	unsigned int *shifted_results;

	bit_length = (int)log2(value) + 1;
	if(bit_length % 8 != 0){
		bit_length = bit_length + (8 - bit_length % 8);
	}
	no_chunks = bit_length/8;

	chunks = malloc(sizeof(uint8_t) * no_chunks);
	results = malloc(sizeof(uint8_t) * no_chunks);
	shifted_results = malloc(sizeof(unsigned int) * no_chunks);

	if(!chunks || !results || !shifted_results){
		fprintf(stderr, "Error Allocating Memory!\n");
		exit(1);
	}

	for(i=0; i < no_chunks; i++){
		chunks[i] = isoMask(value, bit_length, 8);
		bit_length-=8;
	}

	for(i=0; i< no_chunks; i++){
		if(!chaining){
			results[i] = sp(key_v , chunks[i]);
		}
		else{
			/* if block chaining is set
			 * for first iterations xor input chunk with IV
			 * for other iterations xor with previous result
			 */
			if(i == 0){
				results[i] = chunks[i] ^ iv; 
			}
			else{
				results[i] = chunks[i] ^ results[i-1];
			}
			results[i] = sp(key_v, results[i]);
			//left shitf results at respective bit positions
		}
		shifted_results[i] = results[i] << (8 * (no_chunks - i - 1));	
	}
		
	final = 0;
	for(i=0; i < no_chunks ; i++){
		//OR the shifted results, for final value
		final = final | shifted_results[i];		
	}

	free(chunks);
	free(results);
	free(shifted_results);
	return final;
}

