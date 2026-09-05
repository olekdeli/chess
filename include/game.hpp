#include <iostream>
#include <vector>
#include <cstdint>

typedef std::uint64_t board;


#define FILE_A  0b1000000010000000100000001000000010000000100000001000000010000000
#define FILE_H  0b0000000100000001000000010000000100000001000000010000000100000001
#define FILE_AB 0b1100000011000000110000001100000011000000110000001100000011000000
#define FILE_GH 0b1000000010000000100000001000000010000000100000001000000010000000

/*
Board indexing convention as follows:

  | A  B  C  D  E  F  G  H
  | --|--|--|--|--|--|--|--| 
8 | 56 57 58 59 60 61 62 63
7 | 48 49 50 51 52 53 54 55
6 | 40 41 42 43 44 45 46 47
5 | 32 33 34 35 36 37 38 39
4 | 24 25 26 27 28 29 30 31
3 | 16 17 18 19 20 21 22 23
2 | 08 09 10 11 12 13 14 15 
1 | 00 01 02 03 04 05 06 07
*/

class gamestate{

	gamestate();

	board whiteKnight; //0b 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
	board whiteRook;
	board whiteBishop;
	board whiteKing;
	board whiteQueen;
	board whitePawns;

	board blackKnight;
	board blackRook;
	board blackBishop;
	board blackKing;
	board blackQueen;
	board blackPawns;

	board whites;
	board blacks;
	board allOccupied;

	//Precomputed Attack Masks for faster access 
	std::vector<board> knightAttackMask;
	std::vector<board> kingAttackMask;

	
	std::uint16_t move;
	//0-5 : Source square index
	//6-11: Destination square index
	//12-13:Promotion piece type  -  00:Knight, 01:Bishop, 10:Rook, 11:Queen
	//14-16:

	void init();
	void initPiecesStartPos();
	void initKnightAttackMask();

	void printBoardFormation(board object);



};
