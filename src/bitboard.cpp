#include "../include/bitboard.hpp"

void printBoardFormation(board object){

	for(int i=0;i!=64;i++){
		if(object & (1ULL << i)) std::cerr<<"x";
		else std::cerr<<"o";
		
		if(i%8==7)std::cerr<<"\n";
	}

}
