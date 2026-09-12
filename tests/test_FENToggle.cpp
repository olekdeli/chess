#include "../include/board.hpp"
#include <cassert>
#include <iostream>

void test_togglePiece() {
    gameState game; 

    // ==========================================
    // 1. SINGLE PIECE TOGGLE (ON)
    // ==========================================
    // Place a White Knight on E4 (index 28)
    

    game.toggle_piece(WHITE, KNIGHT, 28);	
    assert(game.whiteKnight == (1ULL << 28) && "White Knight missing from E4");
    assert(game.whites == (1ULL << 28) && "White occupancy missing E4");
    assert(game.allOccupied == (1ULL << 28) && "Global occupancy missing E4");
    assert(game.blacks == 0 && "Black occupancy should be empty");

    // ==========================================
    // 2. SINGLE PIECE TOGGLE (OFF)
    // ==========================================
    // Remove the White Knight from E4
    game.toggle_piece(WHITE, KNIGHT, 28);
    assert(game.whiteKnight == 0 && "White Knight failed to toggle off");
    assert(game.whites == 0 && "White occupancy failed to clear");
    assert(game.allOccupied == 0 && "Global occupancy failed to clear");

    // ==========================================
    // 3. BLACK PIECE TEST
    // ==========================================
    // Place a Black Rook on A8 (index 56)
    game.toggle_piece(BLACK, ROOK, 56);
    assert(game.blackRook == (1ULL << 56) && "Black Rook missing from A8");
    assert(game.blacks == (1ULL << 56) && "Black occupancy missing A8");
}

void test_loadFEN() {
    gameState game;
    
    // Load the standard chess starting position
    game.loadFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    // ==========================================
    // 1. VERIFY PAWN RANKS
    // ==========================================
    // White pawns must fill Rank 2 (indices 8-15)
    assert(game.whitePawns == 0x000000000000FF00ULL && "White pawns incorrectly placed");
    // Black pawns must fill Rank 7 (indices 48-55)
    assert(game.blackPawns == 0x00FF000000000000ULL && "Black pawns incorrectly placed");

    // ==========================================
    // 2. VERIFY KING POSITIONS
    // ==========================================
    assert(game.whiteKing == (1ULL << 4) && "White King must be on E1 (index 4)");
    assert(game.blackKing == (1ULL << 60) && "Black King must be on E8 (index 60)");

    // ==========================================
    // 3. VERIFY OCCUPANCY BITBOARDS
    // ==========================================
    // White pieces should completely fill Ranks 1 and 2
    assert(game.whites == 0x000000000000FFFFULL && "White piece occupancy is wrong");
    // Black pieces should completely fill Ranks 7 and 8
    assert(game.blacks == 0xFFFF000000000000ULL && "Black piece occupancy is wrong");
    // Global occupancy must be the exact combination of the two teams
    assert(game.allOccupied == (game.whites | game.blacks) && "Global occupancy mismatch");
}

