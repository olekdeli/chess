/*
#include "../include/game.hpp"


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

void init(){
	initKingAttack();
	initKnightAttack();
	initPawnAttack();
	initPawnMove();
	//Set the pieces
	//initPiesesStartPos();

}

void printBoardFormation(board object){

	for(int i=0;i!=64;i++){
		if(object & (1ULL << i)) std::cerr<<"x";
		else std::cerr<<"o";
		
		if(i%8==7)std::cerr<<"\n";
	}

}*/
