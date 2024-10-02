# AES-128-192-256
AES128/192/256 + Cryptographically secure key/iv generator


#### To do
- Fix Key schedule bug
- implement decryption

- implement other key length variants 
- implement different modes of AES


#### non priority:
- implement galois multiplication for bytesub instead of table look up.
- add key generator dev/urandom/


### testing encryption
```
Key = 0123456789abcdef
data = testing this fun / 0x74,0x65,0x73,0x74,0x69,0x6E,0x67,0x20,0x74,0x68,0x69,0x73,0x20,0x66,0x75,0x6E


// correct output:
// 40 23 14 91 0A 7F 3D 60 1F F9 5B 2B B2 7A 11 B9


// currect output -> output not consistent
// current output:
// 01 d0 c8 fb bf 72 00 00 48 90 42 a9 de 5e 00 00
// 01 70 f6 63 43 74 00 00 48 e0 57 39 9e 59 00 00
// 01 10 6a d4 d5 7f 00 00 48 d0 18 b0 de 5d 00 00
// 01 50 40 63 c6 7f 00 00 48 20 c6 cc f1 5c 00 00

Fix first -> output consistency

- Bug 1 : key schedule not consistent with same key

- first partial fix : after declaring dynamic array for key schedule index 2,3 were not initialized -> kept changing output of key each run.

- key schedule fine for first 2 rounds -> from round 3 inconsistent

- g function? / memory leak?


```



#### Test  layers 1 - 3
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

#### Key schedule and function g
```bash
```