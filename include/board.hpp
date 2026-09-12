#pragma once

#include "bitboard.hpp"


enum Colour { WHITE=0, BLACK=8 };
enum PieceType { PAWN=1, KNIGHT=2, BISHOP=3, ROOK=4, QUEEN=5, KING=6};


struct gameState{
	//Board Positions
	board whiteKnight = 0; //0b 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
	board whiteRook = 0;
	board whiteBishop = 0;
	board whiteKing = 0;
	board whiteQueen = 0;
	board whitePawns = 0;
	board blackKnight = 0;
	board blackRook = 0;
	board blackBishop = 0;
	board blackKing = 0;
	board blackQueen = 0;
	board blackPawns = 0;

	//Occupancy bitboards
	board whites = 0;
	board blacks = 0;
	board allOccupied = 0;
	uint8_t mailbox[64] = {0};

	Colour sideToMove = WHITE;

	void loadFEN(const std::string& fen);
		
	void toggle_mailbox(int index, PieceType piece, Colour);

	/* ByteCoding for mailbox
	-000 empty
	-001 pawn
	-010 knight
	-011 bishop
	-100 rook
	-101 queen
	-110 king
	0--- white
	1--- black
	*/

	void toggle_piece(Colour colour, PieceType type, int square);

};


