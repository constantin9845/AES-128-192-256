#include "AES.h"

// byte substitution layer
unsigned char AES::byteSub(unsigned char A){
	return SBOX[A/16][A%16];
}

// shift row layer
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

// Mix column layer
void AES::mixCol(unsigned char B[]){
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

// Key addition layer
void AES::applyKey(unsigned char C[], unsigned char K[]){

	for(int i = 0; i < 16; i++){
		C[i] = C[i]^K[i];
	}
}


//128 Key scheduler
unsigned char* AES::genKey(unsigned char K[]){

	// Each element in W must be 32 bits, unsigned char too small
	//unsigned char W[44];
	//unsigned char* w = W;

	// load key into first 4 of W


	// left most word for each round key
	for(int i = 1; i <= 10; i++){
		W[4*i] = W[4*(i-1)] + g(W[(4*i)-1]);
	}

	// other 3 words for each round key
	for(int i = 1; i <= 10; i++){
		for(int j = 1; j <= 3; j++){
			W[(4*i)+j] = W[(4*i)+j-1] + W[4*(i-1)+j];
		}
	}


	//return w;

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






