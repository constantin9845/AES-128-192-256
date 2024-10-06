#include "AES.h"
#include <iostream>

int main(){
	unsigned char A[] = {
		0xb9, 0x14, 0x5a, 0x76,
		0x8b, 0x7d, 0xc4, 0x89,
		0xa0, 0x96, 0xb5, 0x46,
		0xf4, 0x3b, 0x23, 0x1f
	};


	unsigned char key[16] = {
		0x13, 0x9a, 0x35, 0x42,
		0x2f, 0x1d, 0x61, 0xde,
		0x3c, 0x91, 0x78, 0x7f,
		0xe0, 0x50, 0x7a, 0xfd
    };

    //KEY = 		13 9a 35 42 2f 1d 61 de 3c 91 78 7f e0 50 7a fd
	//PLAINTEXT = 	b9 14 5a 76 8b 7d c4 89 a0 96 b5 46 f4 3b 23 1f
	//CIPHERTEXT = 	d7 c3 ff ac 90 31 23 86 50 90 1e 15 73 64 c3 86

	std::cout<<std::endl;
	for(int i = 0; i < 16; i++){
		std::cout<<std::hex<<(int) key[i]<<" ";
	}
	std::cout<<std::endl;
	for(int i = 0; i < 16; i++){
		std::cout<<std::hex<<(int) A[i]<<" ";
	}
	std::cout<<std::endl;

	unsigned char* Y = AES::encrypt(A,key);

	unsigned char* RES = AES::decrypt(Y, key);

	delete[] Y;
	delete[] RES;

	return 0;
}

// correct output:
// F8 40 4A 16 35 46 D4 05 10 28 B3 32 7D 80 A5 B4 

// current output:
// 37 CB 7C 19 B0 1F ED 7f E4 9D CF 7B EF B5 AF 21
// 37 cb 7c 19 b0 1f ed 7f e4 9d cf 7b ef b5 af 21
