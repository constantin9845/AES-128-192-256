

void AES::byteSub(){
	// we get a byte as 2 hex chars as input --> 0xC2 : A
	// these 2 chars are x,y in S Box table
	// use to set B (from table)
	unsigned char A = 0xC2;

	unsigned char B = SBOX[A/16][A%16];


	/*
		std::cout<< ((B >> 4) & 0x0F) <<std::endl; first
		std::cout<< (B & 0x0F) <<std::endl; last

	*/
}