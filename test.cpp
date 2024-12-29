#include "AES.h"
#include <iostream>

int main(){
	
	unsigned char input[] = {
		0x1f, 0xd4, 0xee, 0x65,
		0x60, 0x3e, 0x61, 0x30,
		0xcf, 0xc2, 0xa8, 0x2a,
		0xb3, 0xd5, 0x6c, 0x24
	};

	unsigned char key[16] = {
		0x88, 0x09, 0xe7, 0xdd,
		0x3a, 0x95, 0x9e, 0xe5,
		0xd8, 0xdb, 0xb1, 0x3f,
		0x50, 0x1f, 0x22, 0x74
    };

    unsigned char IV[16] = {
		0xe5, 0xc0, 0xbb, 0x53,
		0x5d, 0x7d, 0x54, 0x57,
		0x2a, 0xd0, 0x6d, 0x17,
		0x0a, 0x0e, 0x58, 0xae
    };

    unsigned char output[16];
    
    std::cout<<std::endl;
    std::cout<<"Original"<<std::endl;
	for(int i = 0; i < 16; i++){
		std::cout<<std::hex<<(int)input[i]<<" ";
	}
	std::cout<<std::endl;

	AES::encryptCBC(input,output,key,IV);

	std::cout<<std::endl;
	std::cout<<"Encrypted"<<std::endl;
	for(int i = 0; i < 16; i++){
		std::cout<<std::hex<<(int)output[i]<<" ";
	}
	std::cout<<std::endl;


	AES::decryptCBC(output, input, key, IV);


	std::cout<<std::endl;
	std::cout<<"Decrypted"<<std::endl;
	for(int i = 0; i < 16; i++){
		std::cout<<std::hex<<(int)input[i]<<" ";
	}
	std::cout<<std::endl;


	return 0;
}


