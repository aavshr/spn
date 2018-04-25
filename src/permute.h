#ifndef __PERMUTE_H__
#define __PERMUTE_H__

#include <stdint.h>

/* circular left shift by 2 
 * @param value: 8 bit value to permtue
 * return permuted 8 bit value
 */
uint8_t permute(uint8_t value){
	return (value << 2 | value >> 6);
}

//decrypt permute
//circular right shift by 2
uint8_t d_permute(uint8_t value){
	return( value >> 2 | value << 6);
}
#endif
