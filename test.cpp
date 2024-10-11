#include "AES.h"
#include <iostream>

int main(){
	
	unsigned char A[] = {
		0x6b, 0xc1, 0xbe, 0xe2,
		0x2e, 0x40, 0x9f, 0x96,
		0xe9, 0x3d, 0x7e, 0x11,
		0x73, 0x93, 0x17, 0x2a
	};

	// 6B C1 BE E2 2E 40 9F 96 E9 3D 7E 11 73 93 17 2A


	unsigned char key[16] = {
		0x2b, 0x7e, 0x15, 0x16,
		0x28, 0xae, 0xd2, 0xa6,
		0xab, 0xf7, 0x15, 0x88,
		0x09, 0xcf, 0x4f, 0x3c
    };

    // 2B 7E 15 16 28 AE D2 A6 AB F7 15 88 09 CF 4F 3C
    
    std::cout<<std::endl;
    std::cout<<"Original"<<std::endl;
	for(int i = 0; i < 16; i++){
		std::cout<<std::hex<<(int)A[i]<<" ";
	}
	std::cout<<std::endl;

	unsigned char* Y = AES::encrypt(A,key);

	std::cout<<std::endl;
	std::cout<<"Encrypted"<<std::endl;
	for(int i = 0; i < 16; i++){
		std::cout<<std::hex<<(int)Y[i]<<" ";
	}
	std::cout<<std::endl;

	unsigned char* RES = AES::decrypt(Y, key);


	std::cout<<std::endl;
	std::cout<<"Decrypted"<<std::endl;
	for(int i = 0; i < 16; i++){
		std::cout<<std::hex<<(int)RES[i]<<" ";
	}
	std::cout<<std::endl;
	



	

	delete[] Y;
	delete[] RES;

	return 0;
}

// correct output (encryption):
// 51 40 23 29 33 A7 16 F6 6B 7B FE B1 F8 C7 DD B5

// my output:
// 30 12 9c a3 b8 ec 95 e2 e6 02 a6 3a aa 37 97 df

// decrypt:
// 11 7c 30 4f 83 3d 30 db 80 ca 9f ae bb 82 c7 af


