#include "AES.h"

// byte substitution layer
unsigned char AES::byteSub(unsigned char A){
	return SBOX[A/16][A%16];
}

// inverse byte substitution layer
unsigned char AES::inverseByteSub(unsigned char A){
	return INV_SBOX[A/16][A%16];
}

// shift row layer
void AES::shiftRow(unsigned char* B){
	unsigned char temp[4][4];

	int index = 0;
	// fill matrix
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			temp[j][i] = B[index];
			index++;
		}
	}

	//start shift rows

	// row 2 shifted right by 3
	for(int i = 0; i < 3; i++){
		unsigned char k = temp[1][3];
		for(int j = 3; j >= 0; j--){
			temp[1][j] = temp[1][j-1];
		}
		temp[1][0] = k;
	}

	// row 3 shifted right by 2
	for(int i = 0; i < 2; i++){
		unsigned char k = temp[2][3];
		for(int j = 3; j >= 0; j--){
			temp[2][j] = temp[2][j-1];
		}
		temp[2][0] = k;
	}


	// row 4 shifted right by 1
	unsigned char k = temp[3][3];
	for(int j = 3; j >= 0; j--){
		temp[3][j] = temp[3][j-1];
	}
	temp[3][0] = k;


	// store new order back into B
	index = 0;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			B[index] = temp[i][j]; 
			index++;
		}
	}
}

// shift row layer
void AES::inverseShiftRow(unsigned char* B){
	unsigned char temp[4][4];

	int index = 0;
	// fill matrix
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			temp[j][i] = B[index];
			index++;
		}
	}

	//start shift rows

	// row 2 shifted right by 1
	unsigned char k = temp[1][3];
	for(int j = 3; j >= 0; j--){
		temp[1][j] = temp[1][j-1];
	}
	temp[1][0] = k;

	// row 3 shifted right by 2
	for(int i = 0; i < 2; i++){
		unsigned char k = temp[2][3];
		for(int j = 3; j >= 0; j--){
			temp[2][j] = temp[2][j-1];
		}
		temp[2][0] = k;
	}


	// row 4 shifted right by 3
	for(int i = 0; i < 3; i++){
		unsigned char k = temp[3][3];
		for(int j = 3; j >= 0; j--){
			temp[3][j] = temp[3][j-1];
		}
		temp[3][0] = k;
	}


	// store new order back into B
	index = 0;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			B[index] = temp[i][j]; 
			index++;
		}
	}
}

// Mix column layer
void AES::mixCol(unsigned char* B){
	unsigned char temp[16];

	// Each 4 bytes are a column
	for(int i = 0; i < 16; i+=4){
		
		unsigned char c0 = GFmultiply(B[i],MIXCOL_MATRIX[0][0]) ^ GFmultiply(B[i+1],MIXCOL_MATRIX[0][1]) ^ 
		GFmultiply(B[i+2],MIXCOL_MATRIX[0][2]) ^ GFmultiply(B[i+3],MIXCOL_MATRIX[0][3]);

		unsigned char c1 = GFmultiply(B[i],MIXCOL_MATRIX[1][0]) ^ GFmultiply(B[i+1],MIXCOL_MATRIX[1][1]) ^ 
		GFmultiply(B[i+2],MIXCOL_MATRIX[1][2]) ^ GFmultiply(B[i+3],MIXCOL_MATRIX[1][3]);

		unsigned char c2 = GFmultiply(B[i],MIXCOL_MATRIX[2][0]) ^ GFmultiply(B[i+1],MIXCOL_MATRIX[2][1]) ^ 
		GFmultiply(B[i+2],MIXCOL_MATRIX[2][2]) ^ GFmultiply(B[i+3],MIXCOL_MATRIX[2][3]);

		unsigned char c3 = GFmultiply(B[i],MIXCOL_MATRIX[3][0]) ^ GFmultiply(B[i+1],MIXCOL_MATRIX[3][1]) ^ 
		GFmultiply(B[i+2],MIXCOL_MATRIX[3][2]) ^ GFmultiply(B[i+3],MIXCOL_MATRIX[3][3]);


		temp[i] = c0; temp[i+1] = c1; temp[i+2] = c2; temp[i+3] = c3;
	}

	// store result back into B
	for(int i = 0; i < 16; i++){
		B[i] = temp[i];
	}
}

// Inverse Mix column layer
void AES::inverseMixCol(unsigned char* B){
	unsigned char temp[16];

	// Each 4 bytes are a column
	for(int i = 0; i < 16; i+=4){
		
		unsigned char c0 = GFmultiply(B[i],INVERSE_MIXCOL_MATRIX[0][0]) ^ GFmultiply(B[i+1],INVERSE_MIXCOL_MATRIX[0][1]) ^ 
		GFmultiply(B[i+2],INVERSE_MIXCOL_MATRIX[0][2]) ^ GFmultiply(B[i+3],INVERSE_MIXCOL_MATRIX[0][3]);

		unsigned char c1 = GFmultiply(B[i],INVERSE_MIXCOL_MATRIX[1][0]) ^ GFmultiply(B[i+1],INVERSE_MIXCOL_MATRIX[1][1]) ^ 
		GFmultiply(B[i+2],INVERSE_MIXCOL_MATRIX[1][2]) ^ GFmultiply(B[i+3],INVERSE_MIXCOL_MATRIX[1][3]);

		unsigned char c2 = GFmultiply(B[i],INVERSE_MIXCOL_MATRIX[2][0]) ^ GFmultiply(B[i+1],INVERSE_MIXCOL_MATRIX[2][1]) ^ 
		GFmultiply(B[i+2],INVERSE_MIXCOL_MATRIX[2][2]) ^ GFmultiply(B[i+3],INVERSE_MIXCOL_MATRIX[2][3]);

		unsigned char c3 = GFmultiply(B[i],INVERSE_MIXCOL_MATRIX[3][0]) ^ GFmultiply(B[i+1],INVERSE_MIXCOL_MATRIX[3][1]) ^ 
		GFmultiply(B[i+2],INVERSE_MIXCOL_MATRIX[3][2]) ^ GFmultiply(B[i+3],INVERSE_MIXCOL_MATRIX[3][3]);


		temp[i] = c0; temp[i+1] = c1; temp[i+2] = c2; temp[i+3] = c3;
	}

	// store result back into B
	for(int i = 0; i < 16; i++){
		B[i] = temp[i];
	}
}

// Key addition layer
void AES::applyKey(unsigned char* C, unsigned int* k, int& keyIndex){
	/*
	for(int i = 4; i < 44; i++){
		std::cout<<std::hex<<(int)k[i]<<" ";
	}
	std::cout<<std::endl;
	std::cout<<"*****************************"<<std::endl;
	*/
	// key element -> 4 bytes
	// data elem -> 1 byte

	// 16 bytes of input
	for(int byte = 0; byte < 16; byte+=4){

		// 1. grab 4 bytes and reformat into 32 bit variable
		// 3. apply key
		// 4. break down again into 4 bytes

		unsigned int temp = (C[byte] << 24) ^ (C[byte+1] << 16) ^ (C[byte+2] << 8) ^ (C[byte+3]);
		temp ^= k[keyIndex++];

		C[byte] = (temp >> 24) & 0xFF;
		C[byte+1] = (temp >> 16) & 0xFF;
		C[byte+2] = (temp >> 8) & 0xFF;
		C[byte+3] = temp & 0xFF;

	}
}


//128 Key scheduler
unsigned int* AES::genKey(unsigned char K[]){

	// will store 4 bytes in each element
	unsigned int* W = new unsigned int[44];

	
	// load first 4 bytes into W
	W[0] = (K[0] << 24) | (K[1] << 16) | (K[2] << 8) | (K[3]);
	W[1] = (K[4] << 24) | (K[5] << 16) | (K[6] << 8) | (K[7]);
	W[2] = (K[8] << 24) | (K[9] << 16) | (K[10] << 8) | (K[11]);
	W[3] = (K[12] << 24) | (K[13] << 16) | (K[14] << 8) | (K[15]);

	unsigned int gConst = 1; // round constant

	// key expansion
	for(int i = 4; i < 44; i++){
		if(i % 4 == 0){
			W[i] = W[i-4] ^ g(W[i-1], gConst);
		}
		else{
			W[i] = W[i-1] ^ W[i-4]; 
		}
	}
	
	return W;
}

// g function for key schedule
unsigned int AES::g(unsigned int w, unsigned int& gConst){

	// rotate left
	unsigned rotatedW = (w << 8) | (w >> 24);


	// separate into 4 bytes
	unsigned char a = (rotatedW >> 24) & 0xFF;
	unsigned int b = (rotatedW >> 16) & 0xFF;
	unsigned int c = (rotatedW >> 8) & 0xFF;
	unsigned int d = rotatedW & 0xFF;


	// 2. S-box substitution 
	// store in unsigned char to use byteSub function
	unsigned char tempA = byteSub(a);
	unsigned char tempB = byteSub(b);
	unsigned char tempC = byteSub(c);
	unsigned char tempD = byteSub(d);


	// Add round constant to left most byte:
	// const used , then shifted left by 1 --> if LMB set? --> mod p(x)
	tempA ^= gConst;

	// LMB set
	if(gConst & 0x80){
		gConst = (gConst << 1) ^ 0x11B;
	}
	else{
		gConst = gConst << 1;
	}


	// Add 4 bytes back together after left rotation
	a = b = c = d = 0;

	a = a ^ tempA;
	b = b ^ tempB;
	c = c ^ tempC;
	d = d ^ tempD;


	// combine bytes back together into a word
	unsigned int res = (tempA << 24) ^ (tempB << 16) ^ (tempC << 8) ^ tempD;
	
	return res;
}

// Galois field multiplication for Mix col funcion
unsigned char AES::GFmultiply(unsigned char b, unsigned char temp){

	// multiplying by 1 --> no change
	if(temp == 0x01){
		return b;
	}

	// multiply by 2
	// 2 = x --> left shift by 1
	else if(temp == 0x02){
		// perform shift
		unsigned char shifted = b<<1;

		// if MSB was set --> need to reduce in GF
		if(b & 0x80){
			return shifted ^ 0x1B;
		}
		//MSB was 0
		else{
			return shifted;
		}
	}

	// multiply by 3
	// 3 = x+1 --> left shift by 1 and XOR(add) to initial value
	else if(temp == 0x03){
		// perform shift
		unsigned char shifted = b<<1;

		// if MSB was set --> need to reduce in GF
		if(b & 0x80){
			shifted ^= 0x1B;
		}

		// XOR(add) to initial value 
		return shifted ^ b;	
	}

	// multiply by 9 (INV)
	// 9 = x^3 + 1 ==> left shift 3 and XOR(add) initial value
	// perform reduction if bits 6,7 or 8 are set
	else if(temp == 0x09){
		//perform shift
		unsigned char shifted = b<<3;

		// one of 3 LMB set --> reduce
		if(b & 0x08 || b & 0x07 || b & 0x06){
			shifted ^= 0x1B;
		}

		// XOR(add) to initial value
		return shifted ^ b;
	}

	// multiply by b(11) (INV)
	// b = x^3 + x + 1 ==> left shift 3 XOR left shift 1 XOR initial value
	// perform reduction if bits 6,7 or 8 are set
	else if(temp == 0x0B){
		//perform shifts
		unsigned char shifted = b<<3;
		unsigned char shifted2 = b<<1;

		// LMB set --> reduce both
		if(b & 0x08){
			shifted ^= 0x1B;
			shifted2 ^= 0x1B;
		}
		else if(b & 0x07 || b & 0x06){
			shifted ^= 0x1B;
		}

		// XOR(add) to initial value
		return shifted ^ shifted2 ^ b;
	}

	// multiply by d(13) (INV)
	// d = x^3 + x^2 + 1 ==> left shift 3 XOR left shift 2 XOR initial value
	// perform reduction if bits 6,7 or 8 are set
	else if(temp == 0x0D){
		//perform shifts
		unsigned char shifted = b<<3;
		unsigned char shifted2 = b<<2;

		// LMB set --> reduce both
		if(b & 0x08){
			shifted ^= 0x1B;
			shifted2 ^= 0x1B;
		}
		else if(b & 0x07){
			shifted ^= 0x1B;
			shifted2 ^= 0x1B;
		}
		else if(b & 0x06){
			shifted ^= 0x1B;
		}

		// XOR(add) to initial value
		return shifted ^ shifted2 ^ b;
	}

	// multiply by e(14) (INV)
	// e = x^3 + x^2 + x ==> left shift 3 XOR left shift 2 XOR left shift 1
	// perform reduction if bits 6,7 or 8 are set
	else if(temp == 0x0E){
		//perform shifts
		unsigned char shifted = b<<3;
		unsigned char shifted2 = b<<2;
		unsigned char shifted3 = b<<1;

		// LMB set --> reduce both
		if(b & 0x08){
			shifted ^= 0x1B;
			shifted2 ^= 0x1B;
			shifted3 ^= 0x1B;
		}
		else if(b & 0x07){
			shifted ^= 0x1B;
			shifted2 ^= 0x1B;
		}
		else if(b & 0x06){
			shifted ^= 0x1B;
		}

		// XOR(add) to initial value
		return shifted ^ shifted2 ^ shifted3;
	}

	else{
		return 0x00;
	}
}

unsigned char* AES::encrypt(unsigned char input[], unsigned char KEY[]){

	// strores ciphertext
	unsigned char* Y = new unsigned char[16];

	// Generate key schedule
	unsigned int* k = genKey(KEY);
	int keyIndex = 4;


	// perform round 1 to 9
	for(int i = 0; i < 9; i++){


		// start with bytesub layer
		// call bytesub function for each byte
		if(i == 0){
			for(int i = 0; i < 16; i++){
				Y[i] = byteSub(input[i]);
			}
		}
		else{
			for(int i = 0; i < 16; i++){
				Y[i] = byteSub(Y[i]);
			}
		}

		// Shift row layer
		// all 16 bytes are passed
		shiftRow(Y);

		// Mix column layer
		// all 16 bytes passed
		mixCol(Y);

		// perform key addition
		applyKey(Y, k, keyIndex);

		for(int i = 0; i < 16; i++){
			std::cout<<std::hex<<(int)Y[i]<<" ";
		}
		std::cout<<std::endl;
	}


	// perform round 10 without mixing columns
	for(int i = 0; i < 16; i++){
		Y[i] = byteSub(Y[i]);
	}

	shiftRow(Y);
	applyKey(Y, k, keyIndex);

	for(int i = 0; i < 16; i++){
		std::cout<<std::hex<<(int)Y[i]<<" ";
	}
	std::cout<<std::endl;

	delete[] k;
	k = nullptr;
	
	return Y;
}

unsigned char* decrypt(unsigned char A[], unsigned char KEY[]){
	/*
	Structure
	1. key addition
	2. Inverse Mix column layer (except round 1)
	3. Inverse Shift row layer
	4. inverse Byte Sub
	*/

	// Perform round 1

}








