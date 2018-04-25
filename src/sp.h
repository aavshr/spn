#ifndef __SP_H__
#define __SP_H__

#include "key.h"
#include "permute.h"
#include "subs.h"

/* apply substitution permutation network for four rounds
 * @param key_v: 32 bit key 
 * @param value: 8 bit value to apply sp to
 * return 8 bit result after sp
 */
uint8_t sp(unsigned int key_v, uint8_t value){
	uint8_t result, temp;
	temp = key(key_v, value, 0);
	temp = key(key_v, permute(subs(temp)), 1);
	temp = key(key_v, permute(subs(temp)), 2);
	result = key(key_v, subs(temp), 3);
	return result;
}
/* decrypt sp network
 * reverse rounds 
 */
uint8_t d_sp(unsigned int key_v, uint8_t value){
	uint8_t result, temp;
	temp = d_subs(key(key_v, value, 3));
	temp = d_subs(d_permute(key(key_v, temp, 2)));
	temp = d_subs(d_permute(key(key_v, temp, 1)));
	result = key(key_v, temp, 0);
	return result;	
}
#endif
