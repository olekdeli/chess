#include "../include/moveGen.hpp"
#include "../include/leapers.hpp"
#include "../include/sliders.hpp"
#include "../include/pawns.hpp"

void initAllMasks(){
	void initKnightAttack();
	void initKingAttack();

	void initCrossMask();
	void initPlusMask();
	void initQueenMask();

	void initPawnMove();
	void initPawnAttack();
}

void generateMoves(const gameState& game, std::vector<Move>& moveList) {
    if (game.sideToMove == WHITE) {
        generatePawnMoves(game, moveList, WHITE);
        generateKnightMoves(game, moveList, WHITE);
	generateBishopMoves(game,moveList,WHITE);
	generateRookMoves(game,moveList,WHITE);
	generateQueenMoves(game,moveList,WHITE);
	generateKingMoves(game,moveList,WHITE);
    } else {
        generatePawnMoves(game, moveList, BLACK);
        generateKnightMoves(game, moveList, BLACK);
	generateBishopMoves(game,moveList,BLACK);
	generateRookMoves(game,moveList,BLACK);
	generateQueenMoves(game,moveList,BLACK);
	generateKingMoves(game,moveList,BLACK);
    }
}


void generateKnightMoves(const gameState& game, std::vector<Move>& moveList, Colour colour){
	uint64_t knights = (colour==WHITE)? game.whiteKnight : game.blackKnight;
	uint64_t friendlyPieces = (colour==WHITE)? game.whites : game.blacks;

	while(knights!=0){
		//Find the index of the first 1-bit -> find the first knight
		int pieceSquare = __builtin_ctzll(knights);
		//Construct an attack mask considering the friendly pieces
		uint64_t attacks = knightAttackMask[pieceSquare] & ~friendlyPieces;
		//Add all the singular attacks to a list
		while(attacks!=0){
			int targetSquare = __builtin_ctzll(attacks);
			moveList.push_back(Move(pieceSquare, targetSquare, KNIGHT));

			//Brian Kernighan's Algorithm!!!
			attacks &= (attacks - 1);
		}
	knights &= (knights - 1);
	}

}
//ACTUAL PAWN MOVEMENT
void generatePawnMoves(const gameState& game, std::vector<Move>& moveList, Colour colour){
	uint64_t pieces = (colour==WHITE)? game.whitePawns : game.blackPawns;
	uint64_t friendlyPieces = (colour==WHITE)? game.whites : game.blacks;
	uint64_t enemyPieces = (colour==WHITE)? game.blacks : game.whites;

	uint64_t attacks;	

	while(pieces!=0){
		int pieceSquare = __builtin_ctzll(pieces);
		
		if(colour==WHITE){

			attacks = whitePawnAttackMask[pieceSquare] & enemyPieces |
				   whitePawnMoveMask[pieceSquare] & ~game.allOccupied;
		}
		else{
			attacks = blackPawnAttackMask[pieceSquare] & enemyPieces |
				   blackPawnMoveMask[pieceSquare] & ~game.allOccupied;
		}
		//Add all the singular attacks to a list
		while(attacks!=0){
			int targetSquare = __builtin_ctzll(attacks);
			moveList.push_back(Move(pieceSquare, targetSquare, PAWN));
			//Brian Kernighan's Algorithm!!!
			attacks &= (attacks - 1);
		}
	pieces &= (pieces - 1);
	}
}

#if MAGIC_NUMBERS==0
void generateBishopMoves(const gameState& game, std::vector<Move>& moveList, Colour colour) {
    board bishops = (colour == WHITE) ? game.whiteBishop : game.blackBishop;
    board friendly = (colour == WHITE) ? game.whites : game.blacks;

    while (bishops != 0) {
        int bishopPos = __builtin_ctzll(bishops);
        board validMoves = 0;
        board blockers;

        // ==========================================
        // 1. NORTH-WEST (Positive Ray)
        // ==========================================
        blockers = game.allOccupied & NWMask[bishopPos];
        if (blockers != 0) {
            // ctzll finds the closest blocker going UP the board
            validMoves |= (NWMask[bishopPos] ^ NWMask[__builtin_ctzll(blockers)]);
        } else {
            validMoves |= NWMask[bishopPos];
        }

        // ==========================================
        // 2. NORTH-EAST (Positive Ray)
        // ==========================================
        blockers = game.allOccupied & NEMask[bishopPos];
        if (blockers != 0) {
            validMoves |= (NEMask[bishopPos] ^ NEMask[__builtin_ctzll(blockers)]);
        } else {
            validMoves |= NEMask[bishopPos]; // Fixed: Was previously NWMask
        }

        // ==========================================
        // 3. SOUTH-EAST (Negative Ray)
        // ==========================================
        blockers = game.allOccupied & SEMask[bishopPos];
        if (blockers != 0) {
            // clzll finds the closest blocker going DOWN the board
            int closestBlocker = 63 - __builtin_clzll(blockers);
            validMoves |= (SEMask[bishopPos] ^ SEMask[closestBlocker]); // Fixed: ^ instead of &
        } else {
            validMoves |= SEMask[bishopPos];
        }

        // ==========================================
        // 4. SOUTH-WEST (Negative Ray)
        // ==========================================
        blockers = game.allOccupied & SWMask[bishopPos];
        if (blockers != 0) {
            int closestBlocker = 63 - __builtin_clzll(blockers);
            validMoves |= (SWMask[bishopPos] ^ SWMask[closestBlocker]); // Fixed: ^ instead of &
        } else {
            validMoves |= SWMask[bishopPos];
        }

        // Filter out friendly pieces from the final merged mask
        validMoves &= ~friendly;

        // Push valid targets to the move list
        while (validMoves != 0) {
            int target = __builtin_ctzll(validMoves);
            moveList.push_back(Move(bishopPos, target, BISHOP));
            validMoves &= (validMoves - 1);
        }
        
        // Iterate to the next bishop
        bishops &= (bishops - 1);
    }
}

void generateRookMoves(const gameState& game, std::vector<Move>& moveList, Colour colour){
    board rooks = (colour == WHITE) ? game.whiteRook : game.blackRook;
    board friendly = (colour == WHITE) ? game.whites : game.blacks;
    int rookPos = __builtin_ctzll(rooks);
    
     while (rooks != 0) {
        int rookPos = __builtin_ctzll(rooks);
        board validMoves = 0;
        board blockers;

        // ==========================================
        // NORTH & EAST (Positive Rays: ctzll)
        // ==========================================
        blockers = game.allOccupied & NMask[rookPos];
        if (blockers != 0) validMoves |= (NMask[rookPos] ^ NMask[__builtin_ctzll(blockers)]);
        else               validMoves |= NMask[rookPos];

        blockers = game.allOccupied & EMask[rookPos];
        if (blockers != 0) validMoves |= (EMask[rookPos] ^ EMask[__builtin_ctzll(blockers)]);
        else               validMoves |= EMask[rookPos];

        // ==========================================
        // SOUTH & WEST (Negative Rays: 63 - clzll)
        // ==========================================
        blockers = game.allOccupied & SMask[rookPos];
        if (blockers != 0) validMoves |= (SMask[rookPos] ^ SMask[63 - __builtin_clzll(blockers)]);
        else               validMoves |= SMask[rookPos];

        blockers = game.allOccupied & WMask[rookPos];
        if (blockers != 0) validMoves |= (WMask[rookPos] ^ WMask[63 - __builtin_clzll(blockers)]);
        else               validMoves |= WMask[rookPos];

        // Filter friendly pieces
        validMoves &= ~friendly;

        // Extract moves
        while (validMoves != 0) {
            int target = __builtin_ctzll(validMoves);
            moveList.push_back(Move(rookPos, target, ROOK));
            validMoves &= (validMoves - 1);
        }
        
        rooks &= (rooks - 1);
    }
}



void generateQueenMoves(const gameState& game, std::vector<Move>& moveList, Colour colour) {
    board queens = (colour == WHITE) ? game.whiteQueen : game.blackQueen;
    board friendly = (colour == WHITE) ? game.whites : game.blacks;

    while (queens != 0) {
        int queenPos = __builtin_ctzll(queens);
        board validMoves = 0;
        board blockers;

        // --- POSITIVE RAYS (ctzll) ---
        // North
        blockers = game.allOccupied & NMask[queenPos];
        if (blockers != 0) validMoves |= (NMask[queenPos] ^ NMask[__builtin_ctzll(blockers)]);
        else               validMoves |= NMask[queenPos];
        
        // East
        blockers = game.allOccupied & EMask[queenPos];
        if (blockers != 0) validMoves |= (EMask[queenPos] ^ EMask[__builtin_ctzll(blockers)]);
        else               validMoves |= EMask[queenPos];

        // North-West
        blockers = game.allOccupied & NWMask[queenPos];
        if (blockers != 0) validMoves |= (NWMask[queenPos] ^ NWMask[__builtin_ctzll(blockers)]);
        else               validMoves |= NWMask[queenPos];

        // North-East
        blockers = game.allOccupied & NEMask[queenPos];
        if (blockers != 0) validMoves |= (NEMask[queenPos] ^ NEMask[__builtin_ctzll(blockers)]);
        else               validMoves |= NEMask[queenPos];


        // --- NEGATIVE RAYS (63 - clzll) ---
        // South
        blockers = game.allOccupied & SMask[queenPos];
        if (blockers != 0) validMoves |= (SMask[queenPos] ^ SMask[63 - __builtin_clzll(blockers)]);
        else               validMoves |= SMask[queenPos];

        // West
        blockers = game.allOccupied & WMask[queenPos];
        if (blockers != 0) validMoves |= (WMask[queenPos] ^ WMask[63 - __builtin_clzll(blockers)]);
        else               validMoves |= WMask[queenPos];

        // South-East
        blockers = game.allOccupied & SEMask[queenPos];
        if (blockers != 0) validMoves |= (SEMask[queenPos] ^ SEMask[63 - __builtin_clzll(blockers)]);
        else               validMoves |= SEMask[queenPos];

        // South-West
        blockers = game.allOccupied & SWMask[queenPos];
        if (blockers != 0) validMoves |= (SWMask[queenPos] ^ SWMask[63 - __builtin_clzll(blockers)]);
        else               validMoves |= SWMask[queenPos];

        // --- FILTER AND EXTRACT ---
        validMoves &= ~friendly;

        while (validMoves != 0) {
            int target = __builtin_ctzll(validMoves);
            moveList.push_back(Move(queenPos, target, QUEEN));
            validMoves &= (validMoves - 1);
        }
        
        queens &= (queens - 1);
    }
}

void generateKingMoves(const gameState& game, std::vector<Move>& moveList, Colour colour){
    board king = (colour == WHITE) ? game.whiteKing : game.blackKing;
    board friendly = (colour == WHITE) ? game.whites : game.blacks;
    int kingPos = __builtin_ctzll(king);

    board validMoves = kingAttackMask[kingPos] & ~friendly;


    while (validMoves != 0) {
	int target = __builtin_ctzll(validMoves);
	moveList.push_back(Move(kingPos, target, KING));
        validMoves &= (validMoves - 1);
        }
}
#endif

bool isSquareAttacked(const gameState& game, int index, Colour enemy){
	int closest; int piece;
	//Leapers
	board enemyPawn = (enemy==WHITE)? game.whitePawns : game.blackPawns;
	board enemyKing = (enemy==WHITE)? game.whiteKing : game.blackKing;
	board enemyKnight = (enemy==WHITE)? game.whiteKnight : game.blackKnight;
	//Sliders
	board enemyBishop = (enemy==WHITE)? game.whiteBishop : game.blackBishop;
	board enemyRook = (enemy==WHITE)? game.whiteRook : game.blackRook;
	board enemyQueen = (enemy==WHITE)? game.whiteQueen : game.blackQueen;
	//
	board pawnAttackMask = (enemy==WHITE)? blackPawnAttackMask[index] : whitePawnAttackMask[index];
	if((enemyPawn & pawnAttackMask) != 0) return true;

	
	//CHECK FOR ENPASSANT - if in a enPassant'ed square
	if(index == game.epSquare && game.epSquare!=0){
		if(pawnAttackMask & (1ULL<<index) != 0)
			return true;
	}


	if((enemyKing & kingAttackMask[index]) != 0) return true;
	if((enemyKnight & knightAttackMask[index]) != 0) return true;
	//NW
	board blockers = game.allOccupied & NWMask[index];
	if(blockers!=0){
		int closest = __builtin_ctzll(blockers);
		int piece = game.mailbox[closest];
		if(piece == (enemy|BISHOP) || piece == (enemy|QUEEN)) return true;
	}

	//NE
	blockers = game.allOccupied & NEMask[index];
	if(blockers!=0){
		closest = __builtin_ctzll(blockers);
		piece = game.mailbox[closest];
		if(piece == (enemy|BISHOP) || piece == (enemy|QUEEN)) return true;
	}

	//SW
	blockers = game.allOccupied & SWMask[index];
	if(blockers!=0){
		closest = __builtin_clzll(blockers);
		piece = game.mailbox[closest];
		if(piece == (enemy|BISHOP) || piece == (enemy|QUEEN)) return true;	
	}
	//SE
	blockers = game.allOccupied & SEMask[index];
	closest = __builtin_clzll(blockers);
	piece = game.mailbox[closest];
	if(piece == (enemy|BISHOP) || piece == (enemy|QUEEN)) return true;
	//W
	blockers = game.allOccupied & WMask[index];
	closest = __builtin_clzll(blockers);
	piece = game.mailbox[closest];
	if(piece == (enemy|ROOK) || piece == (enemy|QUEEN)) return true;
	//S
	blockers = game.allOccupied & SMask[index];
	closest = __builtin_clzll(blockers);
	piece = game.mailbox[closest];
	//N
	blockers = game.allOccupied & NMask[index];
	closest = __builtin_ctzll(blockers);
	piece = game.mailbox[closest];
	if(piece == (enemy|ROOK) || piece == (enemy|QUEEN)) return true;	
	//E
	blockers = game.allOccupied & EMask[index];
	closest = __builtin_ctzll(blockers);
	piece = game.mailbox[closest];
	if(piece == (enemy|ROOK) || piece == (enemy|QUEEN)) return true;	
	//if not
	return false;
}
