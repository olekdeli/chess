#include "../include/pawns.hpp"
#include "../include/bitboard.hpp"

void initPawnAttack(){
	whitePawnAttackMask.resize(64,0);
	blackPawnAttackMask.resize(64,0);

	board pawnPos = 0x0000000000000001;

	for(int pos=0; pos!=64; pos++){
		whitePawnAttackMask[pos] = 
			(pawnPos << 7 & ~FILE_H) |
			(pawnPos << 9 & ~FILE_A);
		blackPawnAttackMask[pos] = 
			(pawnPos >> 7 & ~FILE_A) |
			(pawnPos >> 9 & ~FILE_H);
	pawnPos<<=1;
	}
}

void initPawnMove(){
	whitePawnMoveMask.resize(64,0);
	blackPawnMoveMask.resize(64,0);
	board pawnPos = 0x0000000000000001;

	for(int pos=0; pos!=64; pos++){
		whitePawnMoveMask[pos] = pawnPos << 8;
		blackPawnMoveMask[pos] = pawnPos >> 8;
		pawnPos<<=1;
	}
}
