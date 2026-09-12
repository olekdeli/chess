#include "../include/bitboard.hpp"
#include "../include/leapers.hpp"
#include "../include/pawns.hpp"
#include "../include/sliders.hpp"
#include "../include/board.hpp"
#include "../include/GUI.hpp"






int main(){
	initPawnMove();
	initPawnAttack();
	initKnightAttack();
	initKingAttack();

	gameState game;

	game.loadFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
	printBoard(game);
}
