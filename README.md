# AES-128-192-256
AES128/192/256 + Cryptographically secure key/iv generator


#### To do
- determine type for Key schedule array, need 32 bit elements
- implement g function for key scheduler
- In key addition function, each element in key array --> 32 bits / data is 1 byte, need to resize key before addition.


#### non priority:
- implement galois multiplication for bytesub instead of table look up.
- add key generator dev/urandom/



```
Layers 1-3
Trace test for first 4 bytes:

start : 0x00,0x01,0x02,0x03,
		

after Byte sub: (tested)

0x63 0xf2 0x30 0xfe

after row shift layer: (tested) (first row unaffected)

0x63 0xf2 0x30 0xfe

After Mix col: (tested)

0x05 0x7e 0x30 0x8f


```
