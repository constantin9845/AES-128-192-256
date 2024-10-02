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
void AES::applyKey(unsigned char C[], unsigned int* k, int& keyIndex){

	// key element -> 4 bytes
	// data elem -> 1 byte

	// 16 bytes of input
	for(int byte = 0; byte < 16; byte+=4){

		// 1. grab 4 bytes and reformat into 32 bit variable
		// 3. apply key
		// 4. break down again into 4 bytes

		unsigned int temp = (C[byte] << 24) ^ (C[byte+1] << 16) ^ (C[byte+2] << 8) ^ (C[byte+3]);
		temp ^= k[keyIndex++];

		C[byte] = (temp >> 24);
		C[byte+1] = (temp << 8) >> 24;
		C[byte+2] = (temp << 16) >> 24;
		C[byte+3] = (temp << 24) >> 24;

	}
}


//128 Key scheduler
unsigned int* AES::genKey(unsigned char K[]){

	// will store 4 bytes in each element
	unsigned int W[44];
	unsigned int* w = W;

	
	// load first 4 bytes into W
	W[0] = (K[0] << 24) | (K[1] << 16) | (K[2] << 8) | (K[3]);
	W[1] = (K[4] << 24) | (K[5] << 16) | (K[6] << 8) | (K[7]);
	W[2] = (K[8] << 24) | (K[9] << 16) | (K[10] << 8) | (K[11]);
	W[3] = (K[12] << 24) | (K[13] << 16) | (K[14] << 8) | (K[15]);


	// bit set for testing purposes
	//std::cout<<std::bitset<32>(c0);


	unsigned int gConst = 1;

	
	// left most word for each round key
	for(int i = 1; i <= 10; i++){
		W[4*i] = W[4*(i-1)] ^ g(W[(4*i)-1], gConst);
	}

	// other 3 words for each round key
	for(int i = 1; i <= 10; i++){
		for(int j = 1; j <= 3; j++){
			W[(4*i)+j] = W[(4*i)+j-1] ^ W[4*(i-1)+j];
		}
	}

	
	for(int i = 0; i < 44; i+=4){
		std::cout<<std::bitset<32>(W[i])<<std::endl;
	}
	
	
	return w;
}

// g function for key schedule
unsigned int AES::g(unsigned int w, unsigned int& gConst){


	// separate into 4 bytes
	unsigned int a = (w >> 24);
	unsigned int b = (w >> 16);
	unsigned int c = (w >> 8);
	unsigned int d = w;


	// 2. S-box substitution 
	// store in unsigned char to use byteSub function
	unsigned char tempA = byteSub(a & 0xff);
	unsigned char tempB = byteSub(b & 0xff);
	unsigned char tempC = byteSub(c & 0xff);
	unsigned char tempD = byteSub(d & 0xff);


	// Add round constant to left most byte:
	// const used , then shifted left by 1 --> if LMB set? --> mod p(x)
	tempA ^= gConst;

	// LMB set
	if(gConst & 0x80){
		gConst = (gConst << 1) ^ 0x11b;
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


	unsigned int res = (b << 24) ^ (c << 16) ^ (d << 8) ^ a;
	
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

	else{
		return 0x00;
	}
}

unsigned char* AES::encrypt(unsigned char input[], unsigned char KEY[]){

	// strores ciphertext
	unsigned char Y[16];
	unsigned char* y = Y;

	// Generate key schedule
	unsigned int* k = genKey(KEY);
	int keyIndex = 4;

	// perform FIRST ROUND

	// start with bytesub layer
	// call bytesub function for each byte of the input
	for(int i = 0; i < 16; i++){
		Y[i] = byteSub(input[i]);
	}

	// Shift row layer
	// all 16 bytes are passed
	shiftRow(Y);

	// Mix column layer
	// all 16 bytes passed
	mixCol(Y);

	// perform key addition
	applyKey(Y, k, keyIndex);


	// perform round 2 to 9
	for(int i = 0; i < 8; i++){

		// start with bytesub layer
		// call bytesub function for each byte
		for(int i = 0; i < 16; i++){
			Y[i] = byteSub(Y[i]);
		}

		// Shift row layer
		// all 16 bytes are passed
		shiftRow(Y);

		// Mix column layer
		// all 16 bytes passed
		mixCol(Y);

		// perform key addition
		applyKey(Y, k, keyIndex);
	}


	// perform round 10 without mixing columns
	for(int i = 0; i < 16; i++){
		Y[i] = byteSub(Y[i]);
	}

	shiftRow(Y);
	applyKey(Y, k, keyIndex);

	return y;
}






