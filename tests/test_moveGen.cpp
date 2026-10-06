#include "../include/board.hpp"   //gameState and Colour
#include "../include/moveGen.hpp" //Move and generatePawnMoves

//#include <../include/GUI.hpp> //For debuging with "checkState(game,moveList);"

extern void initPawnAttack();

bool containsMove(const std::vector<Move>& moveList, int source, int target, int flag) {
    for (const Move& m : moveList) {
        if (m.getSource() == source && m.getTarget() == target && m.getFlag() == flag) {
            return true;
        }
    }
    return false;
}

void test_moveGen_pawnMove(){
    gameState game; 
    std::vector<Move> moveList;

    // A2 (Index 8) - Completely free
    game.toggle_piece(WHITE, PAWN, 8); 
    
    // B2 (Index 9) - Blocked from double pushing by a piece on B4 (Index 25)
    game.toggle_piece(WHITE, PAWN, 9);
    game.toggle_piece(BLACK, ROOK, 25); 

    // C2 (Index 10) - Completely blocked by a piece on C3 (Index 18)
    game.toggle_piece(WHITE, PAWN, 10);
    game.toggle_piece(BLACK, KNIGHT, 18);

    generatePawnMoves(game, moveList, WHITE);


    // A2 should generate a single and double push
    assert(containsMove(moveList, 8, 16, QUIET_MOVE_FLAG)); 
    assert(containsMove(moveList, 8, 24, DOUBLE_PUSH_FLAG)); 

    // B2 should ONLY generate a single push
    assert(containsMove(moveList, 9, 17, QUIET_MOVE_FLAG));
    assert(!containsMove(moveList, 9, 25, DOUBLE_PUSH_FLAG));

    // C2 should generate absolutely nothing
    assert(!containsMove(moveList, 10, 18, QUIET_MOVE_FLAG));
    assert(!containsMove(moveList, 10, 26, DOUBLE_PUSH_FLAG));
}




void test_moveGen_pawnAttack(){

	gameState game;
	std::vector<Move> moveList;

	game.toggle_piece(WHITE, PAWN, 31);
	game.toggle_piece(BLACK, KNIGHT, 38); 
	// Place a phantom piece on the A-file (Index 40) to ensure wrap-around capture is blocked by ~FILE_A
	game.toggle_piece(BLACK, ROOK, 40); 

	// D5 (Index 35) - Positioned for an En Passant capture to C6 (Index 42)
	game.toggle_piece(WHITE, PAWN, 35);
	game.toggle_piece(BLACK, PAWN, 34); // The Black pawn just double pushed to C5
	game.epSquare = 42; // The En Passant target square on C6

	generatePawnMoves(game, moveList, WHITE);

	// H4 should capture G5, but NOT capture A5 (Index 40)


	assert(containsMove(moveList, 31, 38, NORMAL_CAPTURE_FLAG));
	assert(!containsMove(moveList, 31, 40, NORMAL_CAPTURE_FLAG));

	// D5 should generate an En Passant capture to C6
	assert(containsMove(moveList, 35, 42, EN_PASS_FLAG));

}

void test_moveGen_pawnPromotion(){
	gameState game;

	game.toggle_piece(WHITE, PAWN, 48);
	game.toggle_piece(BLACK, ROOK, 57); // Target for right capture promotion

	std::vector<Move> moveList;
	generatePawnMoves(game, moveList, WHITE);

	// A7 Single Push Promotions (Index 56)
	assert(containsMove(moveList, 48, 56, KNIGHT_PROMOTION_FLAG));
	assert(containsMove(moveList, 48, 56, BISHOP_PROMOTION_FLAG));
	assert(containsMove(moveList, 48, 56, ROOK_PROMOTION_FLAG));
	assert(containsMove(moveList, 48, 56, QUEEN_PROMOTION_FLAG));

	// A7 Right Capture Promotions (Index 57)
	assert(containsMove(moveList, 48, 57, KNIGHT_PROMOTION_CAPTURE_FLAG));
	assert(containsMove(moveList, 48, 57, BISHOP_PROMOTION_CAPTURE_FLAG));
	assert(containsMove(moveList, 48, 57, ROOK_PROMOTION_CAPTURE_FLAG));
	assert(containsMove(moveList, 48, 57, QUEEN_PROMOTION_CAPTURE_FLAG));

	// Ensure it did NOT accidentally push a standard quiet move or normal capture to Rank 8
	assert(!containsMove(moveList, 48, 56, QUIET_MOVE_FLAG));
	assert(!containsMove(moveList, 48, 57, NORMAL_CAPTURE_FLAG));
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

void test_moveGen_isSquareAttacked(){
	gameState game;
	initAllMasks();
    // ==========================================
    // 1. EMPTY BOARD (Safe Square)
    // ==========================================
    // E4 is index 28. It should not be attacked by Black.
    assert(isSquareAttacked(game, 28, BLACK) == false && "E4 must be safe on an empty board");
	
    // ==========================================
    // 2. PAWN ASYMMETRY
    // ==========================================
    // Place a Black Pawn on D5 (index 35). It attacks South-East to E4 (28).
    game.toggle_piece(BLACK, PAWN, 35);
    assert(isSquareAttacked(game, 28, BLACK) == true && "E4 must be attacked by Black Pawn on D5");
    game.toggle_piece(BLACK, PAWN, 35); // Remove it

    // Place a White Pawn on D5 (index 35). It attacks North-East. 
    // It should NOT attack E4 (28).
    game.toggle_piece(WHITE, PAWN, 35);
    assert(isSquareAttacked(game, 28, BLACK) == false && "E4 must NOT be attacked by a White Pawn on D5");
    game.toggle_piece(WHITE, PAWN, 35); // Remove it

    // ==========================================
    // 3. LEAPER ATTACK (Knight)
    // ==========================================
    // Place Black Knight on F6 (index 45).
    game.toggle_piece(BLACK, KNIGHT, 45);
    assert(isSquareAttacked(game, 28, BLACK) == true && "E4 must be attacked by Black Knight on F6");
    game.toggle_piece(BLACK, KNIGHT, 45); // Remove it

    // ==========================================
    // 4. UNBLOCKED SLIDER (Rook)
    // ==========================================
    // Place Black Rook on E8 (index 60). It looks directly down the E-file.
    game.toggle_piece(BLACK, ROOK, 60);
    assert(isSquareAttacked(game, 28, BLACK) == true && "E4 must be attacked by unblocked Black Rook on E8");

    // ==========================================
    // 5. BLOCKED SLIDER
    // ==========================================
    // Place a White Pawn on E6 (index 44) to block the Black Rook's ray.
    game.toggle_piece(WHITE, PAWN, 44);
    
    // The mailbox lookup should see the White Pawn first and return false.
    assert(isSquareAttacked(game, 28, BLACK) == false && "E4 must be safe when the Black Rook is blocked");

    // Change the blocking piece to a Black Pawn. The square should STILL be safe.
    // (A piece cannot attack THROUGH its own friendly pieces).
    game.toggle_piece(WHITE, PAWN, 44); // Remove White Pawn
    game.toggle_piece(BLACK, PAWN, 44); // Add Black Pawn
    assert(isSquareAttacked(game, 28, BLACK) == false && "E4 must be safe when the Black Rook is blocked by its own Pawn");
    std::cout << "isSquareAttacked tests passed successfully.\n";
    
}
