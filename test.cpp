#include "AES.h"
#include <iostream>

int main(){
	
	unsigned char input[] = {
		0x6B, 0xC1, 0xBE, 0xE2,
		0x2E, 0x40, 0x9F, 0x96,
		0xE9, 0x3D, 0x7E, 0x11,
		0x73, 0x93, 0x17, 0x2A
	};

	unsigned char key[16] = {
		0x2b, 0x7e, 0x15, 0x16,
		0x28, 0xae, 0xd2, 0xa6,
		0xab, 0xf7, 0x15, 0x88,
		0x09, 0xcf, 0x4f, 0x3c
    };

    unsigned char output[16];
    
    std::cout<<std::endl;
    std::cout<<"Original"<<std::endl;
	for(int i = 0; i < 16; i++){
		std::cout<<std::hex<<(int)input[i]<<" ";
	}
	std::cout<<std::endl;

	AES::encrypt(input,output,key);

	std::cout<<std::endl;
	std::cout<<"Encrypted"<<std::endl;
	for(int i = 0; i < 16; i++){
		std::cout<<std::hex<<(int)output[i]<<" ";
	}
	std::cout<<std::endl;


	AES::decrypt(output, input, key);


	std::cout<<std::endl;
	std::cout<<"Decrypted"<<std::endl;
	for(int i = 0; i < 16; i++){
		std::cout<<std::hex<<(int)input[i]<<" ";
	}
	std::cout<<std::endl;


	return 0;
}


