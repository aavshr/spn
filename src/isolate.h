#ifndef __ISOLATE_H__
#define __ISOLATE_H__

#include <stdint.h>
#include <stdlib.h>

/* isolate specific bits from value
 * @param value: value to isolate bits from 
 * @param startBit: position of bit to start from
 * @param runs: no of bits to extract
 * return: bits extracted
 */
unsigned int isoMask(unsigned int value, unsigned int startBit, unsigned int runs){
	unsigned int mask, temp;
	mask = (1 << runs) - 1;
       	mask = mask << (startBit-runs);	
	temp = value & mask;
	return temp >> (startBit-runs);	
}

#endif
