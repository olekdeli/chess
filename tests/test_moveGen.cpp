#include "../include/board.hpp"   //gameState and Colour
#include "../include/moveGen.hpp" //Move and generatePawnMoves

extern void initPawnAttack();

void test_moveGen_pawnMove(){
	
	gameState game;
	std::vector<Move> moveList;
	

	//initPawnAttack();
	//initPawnMove();

	game.whitePawns = (1ULL << 13); //F2
	game.allOccupied = game.whitePawns;

	generatePawnMoves(game,moveList,WHITE);
	//Without any enemies a pawn should only generate 1 move
	
	assert(moveList.size() == 1 && "F2 Pawn should have exactly 1 move");
	assert(moveList[0].getTarget() == 21 && "Target square must be F3 (index 21)");

	game.whitePawns = (1ULL << 15); //F2
	game.allOccupied = game.whitePawns;

	generatePawnMoves(game,moveList,WHITE);

	assert(moveList.size()==2 && "F2+H2 pawns doesn't have 2 moves");
	assert(moveList[0].getTarget() == 21 && "Second move added should not change the previous moves");
	assert(moveList[1].getTarget() == 23 && "Target square should be F5 (index 23)");
}

void test_moveGen_pawnAttack(){
	
	gameState game;
	std::vector<Move> moveList;

	//Checking for attack when unblocked (1move+1attack target)
	game.toggle_piece(WHITE, PAWN, 13);
	game.toggle_piece(BLACK, PAWN, 20);	
	generatePawnMoves(game,moveList,WHITE);
	assert(moveList.size()==2 && "while not blocked, F2 has only 2 moves to E3 and F3");
	assert(moveList[0].getTarget()==20 && "F2 moves to E3");

	moveList.clear();
	//Checking for moveList clearing
	game.toggle_piece(BLACK, PAWN, 20);	
	generatePawnMoves(game,moveList,WHITE);
	assert(moveList.size()==1 && "List does not clear");

	//Checking for attack recognision when 2 targets + 1move
	moveList.clear();
	game.toggle_piece(BLACK, PAWN, 20); //_XMX_
	game.toggle_piece(BLACK, PAWN, 22); //__P__ 
	generatePawnMoves(game,moveList,WHITE);
	assert(moveList.size()==3 && "Not enough pawn moves found");
	assert(moveList[0].getTarget()==20 && "Wrong target found");
	assert(moveList[1].getTarget()==21 && "Wrong target found");
	assert(moveList[2].getTarget()==22 && "Wrong target found");
	
	//Checking for attack recognision when 2 targets + no_move
	moveList.clear();
	game.toggle_piece(BLACK, PAWN, 21);
	generatePawnMoves(game,moveList,WHITE);
	assert(moveList.size()==2 && "Error at finding moves when blocked");
}

void test_moveGen_knight() {
    gameState game;
    std::vector<Move> moveList;

    // 1. Corner Knight on A1 (index 0) - Edge case testing
    game.toggle_piece(WHITE, KNIGHT, 0);
    generateKnightMoves(game, moveList, WHITE);
    assert(moveList.size() == 2 && "A1 Knight must have exactly 2 moves (B3, C2)");

    // 2. Central Knight on D4 (index 27) with blockers
    moveList.clear();
    game.toggle_piece(WHITE, KNIGHT, 0); // Remove A1 Knight
    game.toggle_piece(WHITE, KNIGHT, 27); 
    
    // Block one path with a friendly piece, allow one capture on an enemy piece
    game.toggle_piece(WHITE, PAWN, 42); // Friendly on C6
    game.toggle_piece(BLACK, PAWN, 44); // Enemy on E6
    
    generateKnightMoves(game, moveList, WHITE);
    assert(moveList.size() == 7 && "D4 Knight must have 7 moves when 1 of 8 is blocked by a friendly piece");
}

#include <../include/sliders.hpp>

extern void initCrossMask(); 

void test_moveGen_bishop() {
    gameState game;
    std::vector<Move> moveList;
    initCrossMask();

    // ==========================================
    // 1. UNBLOCKED CENTRAL BISHOP
    // ==========================================
    // D4 (index 27) allows maximum diagonal movement.
    game.toggle_piece(WHITE, BISHOP, 27);
    generateBishopMoves(game, moveList, WHITE);
    
    // A central bishop has exactly 13 valid squares on an empty board.

    

    assert(moveList.size() == 13 && "Unblocked central Bishop must have 13 moves");

    // ==========================================
    // 2. CORNER BOUNDARY WRAP TEST
    // ==========================================
    moveList.clear();
    game.toggle_piece(WHITE, BISHOP, 27); // Remove D4
    game.toggle_piece(WHITE, BISHOP, 0);  // Place on A1

    generateBishopMoves(game, moveList, WHITE);
    
    // A1 bishop can only travel North-East. 
    // This verifies your rays do not wrap around the H-file to the A-file.
    assert(moveList.size() == 7 && "A1 Bishop must have exactly 7 moves");

    // ==========================================
    // 3. 4-WAY OMNIDIRECTIONAL BLOCKING TEST
    // ==========================================
    moveList.clear();
    game.toggle_piece(WHITE, BISHOP, 0);  // Remove A1
    game.toggle_piece(WHITE, BISHOP, 27); // Place back on D4

    // North-East: Blocked by friendly piece at F6 (index 45) -> 1 valid move (E5)
    game.toggle_piece(WHITE, PAWN, 45); 
    
    // North-West: Blocked by friendly piece at B6 (index 41) -> 1 valid move (C5)
    game.toggle_piece(WHITE, PAWN, 41);

    // South-East: Blocked by enemy piece at F2 (index 13) -> 2 valid moves (E3, capture on F2)
    game.toggle_piece(BLACK, PAWN, 13);

    // South-West: Blocked by enemy piece at B2 (index 9) -> 2 valid moves (C3, capture on B2)
    game.toggle_piece(BLACK, PAWN, 9);

    generateBishopMoves(game, moveList, WHITE);

    // Total expected moves: 1 (NE) + 1 (NW) + 2 (SE) + 2 (SW) = 6
    assert(moveList.size() == 6 && "Bishop failed omnidirectional blocking test");

    std::cout << "Bishop move generation tests passed successfully.\n";
}

void test_moveGen_rook() {
    gameState game;
    std::vector<Move> moveList;
    initPlusMask();
    // ==========================================
    // 1. UNBLOCKED CENTRAL ROOK
    // ==========================================
    game.toggle_piece(WHITE, ROOK, 27); // D4
    generateRookMoves(game, moveList, WHITE);
    // A central rook always has exactly 14 valid squares on an empty board.
    assert(moveList.size() == 14 && "Unblocked central Rook must have 14 moves");

    // ==========================================
    // 2. 4-WAY ORTHOGONAL BLOCKING TEST
    // ==========================================
    moveList.clear();
    
    // North: Blocked immediately by friendly piece at D5 (index 35) -> 0 moves
    game.toggle_piece(WHITE, PAWN, 35); 
    
    // South: Blocked immediately by enemy piece at D3 (index 19) -> 1 move (capture on D3)
    game.toggle_piece(BLACK, PAWN, 19);

    // East: Blocked by friendly piece at F4 (index 29) -> 1 move (E4)
    game.toggle_piece(WHITE, PAWN, 29);

    // West: Blocked by enemy piece at B4 (index 25) -> 2 moves (C4, capture on B4)
    game.toggle_piece(BLACK, PAWN, 25);

    generateRookMoves(game, moveList, WHITE);

    // Total expected moves: 0 (N) + 1 (S) + 1 (E) + 2 (W) = 4
    assert(moveList.size() == 4 && "Rook failed orthogonal blocking test");
    std::cout << "Rook tests passed.\n";
}

void test_moveGen_queen() {
    gameState game;
    std::vector<Move> moveList;
    initPlusMask();
    initCrossMask();

    // ==========================================
    // 1. UNBLOCKED CENTRAL QUEEN
    // ==========================================
    game.toggle_piece(WHITE, QUEEN, 27); // D4
    generateQueenMoves(game, moveList, WHITE);
    
    // 14 orthogonal + 13 diagonal = 27 total moves.
    assert(moveList.size() == 27 && "Unblocked central Queen must have 27 moves");

    // ==========================================
    // 2. 8-WAY CLAUSTROPHOBIA TEST
    // ==========================================
    moveList.clear();
    
    // Block all 4 orthogonal directions with friendly pieces (0 moves generated)
    game.toggle_piece(WHITE, PAWN, 35); // N
    game.toggle_piece(WHITE, PAWN, 19); // S
    game.toggle_piece(WHITE, PAWN, 28); // E
    game.toggle_piece(WHITE, PAWN, 26); // W

    // Block all 4 diagonal directions with immediate enemy pieces (4 captures generated)
    game.toggle_piece(BLACK, PAWN, 36); // NE
    game.toggle_piece(BLACK, PAWN, 18); // SW
    game.toggle_piece(BLACK, PAWN, 20); // SE
    game.toggle_piece(BLACK, PAWN, 34); // NW

    generateQueenMoves(game, moveList, WHITE);

    assert(moveList.size() == 4 && "Queen completely surrounded should only have the 4 diagonal captures");
    std::cout << "Queen tests passed.\n";
}

void test_moveGen_king() {
    gameState game;
    std::vector<Move> moveList;

    // ==========================================
    // 1. UNBLOCKED CENTRAL KING
    // ==========================================
    game.toggle_piece(WHITE, KING, 27); // D4
    generateKingMoves(game, moveList, WHITE);
    
    assert(moveList.size() == 8 && "Unblocked central King must have 8 moves");

    // ==========================================
    // 2. CORNER BOUNDARY WRAP TEST
    // ==========================================
    moveList.clear();
    game.toggle_piece(WHITE, KING, 27); // Remove from D4
    game.toggle_piece(WHITE, KING, 7);  // Place on H1 (index 7)

    generateKingMoves(game, moveList, WHITE);
    
    // If your king move generation relies on bit-shifting (e.g., kingPos << 1), 
    // it must be masked with ~FILE_A to prevent wrapping from H1 to A2.
    assert(moveList.size() == 3 && "Corner King on H1 must have exactly 3 moves");
    std::cout << "King tests passed.\n";
}
