#ifndef __SUBS_H__ 
#define __SUBS_H__

#include "isolate.h"

/* provide bijection of 4 bit numbers
 * @param value = value to map
 * retrun mapped value
 */
uint8_t biject(uint8_t value){
	return (((value+ 1) * 7 ) % 16);
}

/* subsitutes upper 4 bits and lower 4 bits
 * with bijection 
 * @param value: value to substitute
 * return 8 bit subsituted value
 */
uint8_t subs(uint8_t value){
	uint8_t high, low;
	high = isoMask(value, 8, 4);
	low = isoMask(value, 4, 4);
	high = biject(high) << 4;
	low = biject(low);	
	return (high | low);
}

/* decrypt subs
 * create hash map and find bijection 
 */
uint8_t d_subs(uint8_t value){
	uint8_t high, low;
	unsigned int i, map[16];
	for(i=0; i<16; i++){
		map[biject(i)] = i;
	}
	high = isoMask(value, 8, 4);
	low = isoMask(value, 4, 4);
	high = map[high] << 4;
	low = map[low]; 
	return (high | low);
}
#endif

