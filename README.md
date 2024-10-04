# AES-128-192-256
AES128/192/256 + Cryptographically secure key/iv generator


#### To do
- output consistent - but wrong output?
- implement decryption - key schedule left
- test inverse functions for every layer

- implement other key length variants 
- implement different modes of AES


#### non priority:
- implement galois multiplication for bytesub instead of table look up.
- add key generator dev/urandom/

#### Inconsistent output
```

```


#### Key schedule error
```
Key = 0123456789abcdef
data = testing this fun / 0x74,0x65,0x73,0x74,0x69,0x6E,0x67,0x20,0x74,0x68,0x69,0x73,0x20,0x66,0x75,0x6E


- Bug : key schedule not consistent with same key

-> bug fixed: genKey function returned pointer to local variable. with correct pointer and array -> key schedule consistent
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
