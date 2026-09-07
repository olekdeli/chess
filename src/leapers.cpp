#include "../include/leapers.hpp"
#include "../include/bitboard.hpp"

void initKnightAttack(){
	
	knightAttackMask.resize(64,0);	

	board knightPos=0x0000000000000001;
	
	for(int pos=0;pos!=64;pos++){
		
		knightAttackMask[pos] =(knightPos << 17 & ~FILE_A) |
  			  (knightPos << 15 & ~FILE_H) |
 			  (knightPos << 10 & ~FILE_AB)|
  			  (knightPos << 6 & ~FILE_GH) |
	  	          (knightPos >> 17 & ~FILE_H) |
  			  (knightPos >> 15 & ~FILE_A) |
	  		  (knightPos >> 10 & ~FILE_GH)|
 	 		  (knightPos >> 6 & ~FILE_AB);
		knightPos <<= 1;
	}

}

void initKingAttack(){
	kingAttackMask.resize(64,0);
	board kingPos = 0x0000000000000001;

	for(int pos=0;pos!=64;pos++){
		kingAttackMask[pos] = 
			(kingPos << 1 & ~FILE_A) |
			(kingPos << 7 & ~FILE_H) |
			(kingPos << 8) | 
			(kingPos << 9 & ~FILE_A) | 
			(kingPos >> 1 & ~FILE_H) | 
			(kingPos >> 7 & ~FILE_A) | 
			(kingPos >> 8 ) |
			(kingPos >> 9 & ~FILE_H);
		kingPos<<=1;
	}

}

