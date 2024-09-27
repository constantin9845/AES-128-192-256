#include "AES.h"

unsigned char AES::byteSub(unsigned char A){
	// we get a byte as 2 hex chars as input 
	// these 2 chars are x,y in S Box table
	// use to set B (from table)

	/*
		std::cout<< ((B >> 4) & 0x0F) <<std::endl; first
		std::cout<< (B & 0x0F) <<std::endl; last

	*/

	return SBOX[A/16][A%16];
}


void AES::shiftRow(unsigned char B[]){
	unsigned char temp[4][4];

	int index = 0;
	// fill matrix
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			temp[j][i] = B[index];
			index++;
		}
	}

	//shift rows

	// row 2 shift right 3
	for(int i = 0; i < 3; i++){
		unsigned char k = temp[1][3];
		for(int j = 3; j >= 0; j--){
			temp[1][j] = temp[1][j-1];
		}
		temp[1][0] = k;
	}

	// row 3 shift right 2
	for(int i = 0; i < 2; i++){
		unsigned char k = temp[2][3];
		for(int j = 3; j >= 0; j--){
			temp[2][j] = temp[2][j-1];
		}
		temp[2][0] = k;
	}


	// row 4 shift right 1
	unsigned char k = temp[3][3];
	for(int j = 3; j >= 0; j--){
		temp[3][j] = temp[3][j-1];
	}
	temp[3][0] = k;


	// store new order back into B
	index = 0;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			B[index] = temp[j][i]; 
			index++;
		}
	}
}

// Mix column layer
// takes all 16 bytes
void AES::mixCol(unsigned char B[]){
	unsigned char temp[16];

	int tempIndex = 0;
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


		B[i] = c0; B[i+1] = c1; B[i+2] = c2; B[i+3] = c3;
	}
}


unsigned char AES::GFmultiply(unsigned char b, unsigned char temp){

	if(temp == 0x01){
		return b;
	}

	// b is reduced by p(x) only if MSB was set
	else if(temp == 0x02){
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
	else if(temp == 0x03){
		unsigned char shifted = b<<1;

		if(b & 0x80){
			shifted ^= 0x1B;
		}

		return shifted ^ b;
		
	}
	else{
		return 0x00;
	}
}

void AES::encrypt(unsigned char A[], unsigned char Y[]){

	// start with bytesub layer
	// call bytesub function for each byte
	for(int i = 0; i < 16; i++){
		Y[i] = byteSub(A[i]);
	}

	// Shift row layer
	// all 16 bytes are passed
	shiftRow(Y);

	// Mix column layer
	// all 16 bytes passed
	mixCol(Y);
}


// CHECK:
// Implement GF calc

// CALC
/*	
	p(x) = 0x1B
	if MSB set during multiplication by 2 --> mod p(x)

	A * C = 1 mod p(x)

	A * C when C = 0x01 = A
	A * C when C = 0x02 = one degree higher : x
	A * C when C = 0x03 = *(x+1)


*/ 





