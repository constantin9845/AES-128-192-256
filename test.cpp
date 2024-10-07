#include "AES.h"
#include <iostream>

int main(){
	unsigned char A[] = {
		0x49, 0x20, 0x6e, 0x65,
		0x65, 0x64, 0x20, 0x68,
		0x65, 0x6c, 0x70, 0x20,
		0x6e, 0x6f, 0x77, 0x0a
	};


	unsigned char key[16] = {
		0x0f, 0x0f, 0x0f, 0x0f,
		0x0f, 0x0f, 0x0f, 0x0f,
		0x0f, 0x0f, 0x0f, 0x0f,
		0x0f, 0x0f, 0x0f, 0x0f
    };

    std::cout<<std::endl;
	for(int i = 0; i < 16; i++){
		std::cout<<std::hex<<(int)A[i]<<" ";
	}
	std::cout<<std::endl;

	unsigned char* Y = AES::encrypt(A,key);

	std::cout<<std::endl;
	for(int i = 0; i < 16; i++){
		std::cout<<std::hex<<(int)Y[i]<<" ";
	}
	std::cout<<std::endl;

	unsigned char* RES = AES::decrypt(Y, key);

	std::cout<<std::endl;
	for(int i = 0; i < 16; i++){
		std::cout<<std::hex<<(int)RES[i]<<" ";
	}
	std::cout<<std::endl;

	

	delete[] Y;
	delete[] RES;

	return 0;
}

// correct output (encryption):
// 38 5b 88 c3 ab 76 00 56 d4 18 3f 12 e3 52 a3 93


// currently
// input:
// 49 20 6e 65 65 64 20 68 65 6c 70 20 6e 6f 77 0a

// cipher text:
// 02 f4 32 3f ad 8b 14 47 ad 7f 8b fd fa 07 62 cd

// decrypt:
// 8c bf a9 22 55 ba 1f 13 7d df b4 d6 ad 93 87 c3
