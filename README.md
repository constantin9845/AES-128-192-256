# AES-128-192-256
AES128/192/256 + Cryptographically secure key/iv generator


#### To do
- output consistent - but wrong output -> key schedule is correct
- verify shift rows and mix cols -> are rows and cols not transposed incorrectly? 


- implement other key length variants 
- implement different modes of AES


#### non priority:
- implement galois multiplication for bytesub instead of table look up.
- add key generator dev/urandom/




#### Key schedule error
```
Key = 0123456789abcdef
data = testing this fun / 0x74,0x65,0x73,0x74,0x69,0x6E,0x67,0x20,0x74,0x68,0x69,0x73,0x20,0x66,0x75,0x6E


- Bug : key schedule not consistent with same key

-> bug fixed: genKey function returned pointer to local variable. with correct pointer and array -> key schedule consistent
```


