/*
#include <iostream>
#include <vector>
#include <cstdint>

typedef std::uint64_t board;

constexpr uint64_t FILE_A  = 0x0101010101010101ULL;
constexpr uint64_t FILE_H  = 0x8080808080808080ULL;
constexpr uint64_t FILE_AB = 0x0303030303030303ULL;
constexpr uint64_t FILE_GH = 0xC0C0C0C0C0C0C0C0ULL;
*/
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
/*
	//Board Positions
	inline board whiteKnight; //0b 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
	inline board whiteRook;
	inline board whiteBishop;
	inline board whiteKing;
	inline board whiteQueen;
	inline board whitePawns;
	inline board blackKnight;
	inline board blackRook;
	inline board blackBishop;
	inline board blackKing;
	inline board blackQueen;
	inline board blackPawns;

	//Occupancy bitboards
	inline board whites;
	inline board blacks;
	inline board allOccupied;

	//Precomputed Attack/Move Masks for faster access 
	inline std::vector<board> knightAttackMask;
	inline std::vector<board> kingAttackMask;
	inline std::vector<board> whitePawnAttackMask; 
	inline std::vector<board> whitePawnMoveMask;
	inline std::vector<board> blackPawnAttackMask;
	inline std::vector<board> blackPawnMoveMask;

	//For move history
	inline std::vector<std::uint16_t> move;
	//0-5 : Source square index
	//6-11: Destination square index
	//12-13:Promotion piece type  -  00:Knight, 01:Bishop, 10:Rook, 11:Queen
	//14-16:

	void init();
	void initPiecesStartPos();
	void initKnightAttack();
	void initKingAttack();
	void initPawnAttack();
	void initPawnMove();

	void printBoardFormation(board object);


*/
