#include "include/game.hpp"

int main(){

	init();
	printBoardFormation(knightAttackMask[17]);
	std::cerr<<"\n";
	printBoardFormation(knightAttackMask[24]);
	std::cerr<<"\n";
	printBoardFormation(kingAttackMask[4]);
	std::cerr<<"\n";
	printBoardFormation(kingAttackMask[15]);
}
