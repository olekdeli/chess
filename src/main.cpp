#include "../include/bitboard.hpp"
#include "../include/leapers.hpp"
#include "../include/pawns.hpp"
#include "../include/sliders.hpp"
#include "../include/board.hpp"






int main(){
	initPawnMove();
	initPawnAttack();
	initKnightAttack();
	initKingAttack();
	printBoardFormation(knightAttackMask[17]);
	std::cerr<<"\n";
	printBoardFormation(knightAttackMask[24]);
	std::cerr<<"\n";
	printBoardFormation(kingAttackMask[4]);
	std::cerr<<"\n";
	printBoardFormation(kingAttackMask[15]);
}
