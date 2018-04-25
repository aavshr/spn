#ifndef __KEY_H__
#define __KEY_H__

#include "isolate.h"

/* XOR input with key
 * @param key_v: 32 bit key value
 * @param value: 8 bit valeu to XOR with
 * @param round: round of encryption to select respective key block 
 * return 8 bit value XORed with Key at corresponding round
 */
uint8_t key(uint32_t key_v, uint8_t value, unsigned int round){
	uint8_t key_block = isoMask(key_v , 32 - round * 8, 8);
	return (key_block ^ value);
}

#endif
