# AES-128-192-256
AES128/192/256 + Cryptographically secure key/iv generator


#### To do
- Optimize functions

- implement other key length variants 
- implement different modes of AES


#### non priority:
- implement galois multiplication for bytesub instead of table look up.
- add key generator dev/urandom/
- test script


#### Find errors

Test vectors  key schedule: https://www.samiam.org/key-schedule.html
Test vectors Key + layer results : AES_Core128.pdf

- Key expansion correct (verified)

- Byte substitution correct (verified)

- Mix column correct (verified) 
		- bug fixed -> wrong column and row index variables when storing result

- Encryption finished (verified)


- Decryption:

- Bug fixed : decryption key application -> index not in reverse order but in reverse words (4 bytes)

- Bug fixed : inverse shift row layer - wrong indexing

- Bug/log error fixed: multiplication must perform reduction for each bit that is pushed out, not once for all shifts.

