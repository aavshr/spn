# Substitution-Permutation Network
This is an implementation of a subsitution-permutation network of 8-bit
block ciphers with 32-bit keys. The encryption can be done in both 
electronic codebook mode or in cipher block chaining mode. Decryption is also implemented.

## Substitution
The substitution step uses 4-bit S-boxes applied to lower and upper 4 bits 
of an 8-bit word. Subsitution is give by x  = 7(x+1) mod 16. 4-bit chunks
are natural numbers of their corresponding binary encodings.

## Permutation 
The permutation is a cyclic 2-bit left-shift.

## Rounds
There are 4 rounds of encryption.
+ Round 0: Key Step(XOR with key) with first 8 bits of key
+ Round 1: Subsitution step followed by a permutation step followed by key step with the next 8 bits of the key.
+ Round 2: Subsitution step followed by a permutation step followed by key step with the next 8 bits of the key.
+ Round 3: Sbstitution step followed by a key step with the last 8 bits of the key.

## Usage

```shell
spn <key> <initialization vector> <clear text> <chain flag>
```

	
