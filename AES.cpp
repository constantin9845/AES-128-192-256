

void AES::byteSub(unsigned char A){
	// we get a byte as 2 hex chars as input 
	// these 2 chars are x,y in S Box table
	// use to set B (from table)

	/*
		std::cout<< ((B >> 4) & 0x0F) <<std::endl; first
		std::cout<< (B & 0x0F) <<std::endl; last

	*/

	return SBOX[A/16][A%16];
}


void AES::shiftRow(unsigned char[] B){
	unsigned char[4][4] temp;

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
			B[index] = temp[j][i] 
			index++;
		}
	}
}