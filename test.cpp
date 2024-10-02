#include "AES.h"
#include <iostream>

int main(){
	unsigned char A[] = {
		0x74,0x65,0x73,0x74,
		0x69,0x6E,0x67,0x20,
		0x74,0x68,0x69,0x73,
		0x20,0x66,0x75, 0x6E
	};


	unsigned char key[16] = {
		0x00, 0x01, 0x02, 0x03, 
		0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 
        0x0c, 0x0d, 0x0e, 0x0f
    };


	std::cout<<std::endl;
	for(int i = 0; i < 16; i++){
		if(i%4==0){std::cout<<"\n";}
		std::cout<<std::hex<<(int)key[i]<<" ";
	}
	std::cout<<"\n";


	unsigned char* Y = AES::encrypt(A,key);


	std::cout<<std::endl;
	for(int i = 0; i < 16; i++){
		std::cout<<std::hex<<(int)Y[i]<< " ";
	}
	std::cout<<"\n";

	return 0;
}

// correct output:
// 40 23 14 91 0A 7F 3D 60 1F F9 5B 2B B2 7A 11 B9


// current output:
// 01 d0 c8 fb bf 72 00 00 48 90 42 a9 de 5e 00 00
// 01 70 f6 63 43 74 00 00 48 e0 57 39 9e 59 00 00
// 01 10 6a d4 d5 7f 00 00 48 d0 18 b0 de 5d 00 00
// 01 50 40 63 c6 7f 00 00 48 20 c6 cc f1 5c 00 00
// 01 10 b8 24 d5 71 00 00 48 a0 22 aa 9f 5c 00 00
//