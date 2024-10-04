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
		0x00, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00
    };



	unsigned char* Y = AES::encrypt(A,key);


	std::cout<<std::endl;
	for(int i = 0; i < 16; i++){
		std::cout<<std::hex<<(int)Y[i]<< " ";
	}
	std::cout<<"\n";

	return 0;
}

// correct output:
// F8 40 4A 16 35 46 D4 05 10 28 B3 32 7D 80 A5 B4 

// current output:
// 14 CD D9 5C 91 0E F7 96 91 3D C6 AC 3C 6C C9 F1
//
