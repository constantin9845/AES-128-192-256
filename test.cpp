#include "AES.h"
#include <iostream>

int main(){
	unsigned char A[] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
						0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F};


	unsigned char Y[16];

	std::cout<<std::endl;
	for(int i = 0; i < 16; i++){
		if(i%4==0){std::cout<<"\n";}
		std::cout<<std::hex<<(int)A[i]<<" ";
	}
	std::cout<<"\n";


	AES::encrypt(A,Y);


	std::cout<<std::endl;
	for(int i = 0; i < 16; i++){
		if(i%4==0){std::cout<<"\n";}
		std::cout<<std::hex<<(int)Y[i]<<" ";
	}
	std::cout<<"\n";

	return 0;
}


