#include "AES.h"
#include <iostream>

int main(){
	unsigned char A[] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
						0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F};


	unsigned char Y[16];

	unsigned char key[16] = {
    0x8e, 0xe9, 0xd1, 0x09,
    0x64, 0xf3, 0x63, 0xb9,
    0xee, 0x38, 0x74, 0x70,
    0xb0, 0x15, 0x50, 0x7a
};


	std::cout<<std::endl;
	for(int i = 0; i < 16; i++){
		if(i%4==0){std::cout<<"\n";}
		std::cout<<std::hex<<(int)A[i]<<" ";
	}
	std::cout<<"\n";


	AES::encrypt(A,Y,key);


	std::cout<<std::endl;
	for(int i = 0; i < 16; i++){
		if(i%4==0){std::cout<<"\n";}
		std::cout<<std::hex<<(int)Y[i]<<" ";
	}
	std::cout<<"\n";

	return 0;
}


