# AES-128-192-256
AES128/192/256 + Cryptographically secure key/iv generator


#### To do
- Implement Galois calculation function DONE --> make bytesub use this function as well. remove lookup tables.
- Key schedule first steps: generate keys and key schedule.



```
Trace test for first 4 bytes:

start : 0x00,0x01,0x02,0x03,
		

after Byte sub: (tested)

0x63 0xf2 0x30 0xfe

after row shift layer: (tested) (first row unaffected)

0x63 0xf2 0x30 0xfe

After Mix col: (tested)

0x05 0x7e 0x30 0x8f


```
