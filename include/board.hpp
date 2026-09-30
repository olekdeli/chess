#pragma once

#include "bitboard.hpp"

#define QUIET_MOVE_FLAG 0b0000
#define DOUBLE_PUSH_FLAG 0b0001
#define KING_SIDE_CASTLE_FLAG 0b0010
#define QUEEN_SIDE_CASTLE_FLAG 0b0011
#define NORMAL_CAPTURE_FLAG 0b0100
#define EN_PASS_FLAG 0b0101

#define KNIGHT_PROMOTION_FLAG 0b1000
#define BISHOP_PROMOTION_FLAG 0b1001
#define ROOK_PROMOTION_FLAG 0b1010
#define QUEEN_PROMOTION_FLAG 0b1011

#define KNIGHT_PROMOTION_CAPTURE_FLAG 0b1000
#define BISHOP_PROMOTION_CAPTURE_FLAG 0b1001
#define ROOK_PROMOTION_CAPTURE_FLAG 0b1010
#define QUEEN_PROMOTION_CAPTURE_FLAG 0b1011



enum Colour { WHITE=0, BLACK=8 };
enum PieceType { PAWN=1, KNIGHT=2, BISHOP=3, ROOK=4, QUEEN=5, KING=6};

struct Move {
    uint16_t moveValue;

    Move(int source, int target, int flag = 0) {
        moveValue = (source & 0x3F) | ((target & 0x3F) << 6) | ((flag & 0xF) << 12);
    }

    inline int getSource() const { return moveValue & 0x3F; }
    inline int getTarget() const { return (moveValue >> 6) & 0x3F; }
    inline int getFlag() const { return (moveValue >> 12) & 0xF; }
};

struct UndoInfo {

	uint32_t undoInfo;
	/*
	 0-2   captured piece
	 3-6   castling rights
	 7-12  en Passant square 
	 13-19 half-move clock 
	 */

	UndoInfo() : undoInfo(0) {}

	UndoInfo(PieceType capturedPiece, uint8_t enPassantSquare, uint8_t castlingRights, int halfMove){
       undoInfo = (capturedPiece & 0x7)|((castlingRights & 0xF)<<3)|((enPassantSquare & 0x3F) << 7)|((halfMove & 0x7F)<<13);
    }
	PieceType getCapturedPiece() const  { return static_cast<PieceType>(undoInfo & 0x7); }
	uint8_t   getCastlingRights() const { return (undoInfo >> 3) & 0xF; }
	uint8_t   getEpSquare() const       { return (undoInfo >> 7) & 0x3F; }
	int       getHalfMoveClock() const  { return (undoInfo >> 13) & 0x7F; }

};



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

	UndoInfo history[256];
	int currentPly = 0;
	uint8_t castlingRights = 0b1111;
	uint8_t epSquare = 0; //Ghost pawn. 0 for not existing 
	int halfMoveClock = 0;

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

	
	void makeMove(Move move);
	void unmakeMove(Move move);

};


