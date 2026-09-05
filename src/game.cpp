#include "../include/game.hpp"

gamestate::gamestate(){

}

void gamestate::initKnightAttack(){
	
	knightAttackMask.resize(64,0);	

	board knightPos=0x0000000000000001
	
	for(int pos=0;pos!=64;pos++){
		
		knightAttackMask[i] =(knightPos << 17 & ~FILE_A) |
  			  (knightPos << 15 & ~FILE_H) |
 			  (knightPos << 10 & ~FILE_AB)|
  			  (knightPos << 6 & ~FILE_GH) |
	  	          (knightPos >> 17 & ~FILE_H) |
  			  (knightPos >> 15 & ~FILE_A) |
	  		  (knightPos >> 10 & ~FILE_GH)|
 	 		  (knightPos >> 6 & ~FILE_AB);
		knightPos<<1;
	}

}

void gamestate::initKingAttack(){
	kingAttackMask.resize(64,0);

	board kightPos=1;

	for(int pos=0;pos!=64;p++){
		kingAttackMask[i] = (kingPos << )

		kingPos<<1
	}

}

void gamestate::printBoardFormation(board object){

	for(int i=0;i!=64;i++){
		if(!object%2){std::cerr<<" ";} else
			std::cerr<<"X";
		if(i%8)std::cerr<<"\n";
	}

}
