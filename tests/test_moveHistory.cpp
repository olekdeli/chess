#include "../include/board.hpp"
#include <cassert>
#include <iostream>

void test_makeMove_and_unmake() {

gameState game;

    // ==========================================
    // 1. QUIET MOVE & STATE RESTORATION TEST
    // ==========================================
    // Setup: White Knight on B1 (index 1)
    game.toggle_piece(WHITE, KNIGHT, 1);
    Move quietMove(1, 18, KNIGHT); // Move B1 to C3

    // Manually inject dummy irreversible states before the move
    game.epSquare = 42; 
    game.castlingRights = 0b1010; 
    game.halfMoveClock = 15;

    // Execute
    game.makeMove(quietMove);

    // Verify Forward State
    assert((game.whiteKnight & (1ULL << 1)) == 0 && "B1 must be empty after move");
    assert((game.whiteKnight & (1ULL << 18)) != 0 && "C3 must contain the Knight");
    assert(game.mailbox[1] == 0 && "Mailbox must clear B1");
    assert(game.mailbox[18] == (WHITE | KNIGHT) && "Mailbox must update to C3");
    assert(game.currentPly == 1 && "Ply must increment to 1");

    // Let's pretend the move completely wiped out the state variables
    game.epSquare = 0;
    game.castlingRights = 0;
    game.halfMoveClock = 16;

    // Reversal
    game.unmakeMove(quietMove);

    // Verify Board Reversal
    assert((game.whiteKnight & (1ULL << 1)) != 0 && "Knight must return to B1");
    assert((game.whiteKnight & (1ULL << 18)) == 0 && "C3 must be empty again");
    assert(game.mailbox[1] == (WHITE | KNIGHT) && "Mailbox must restore B1");
    assert(game.currentPly == 0 && "Ply must decrement to 0");

    // Verify Irreversible State Restoration
    assert(game.epSquare == 42 && "En Passant square must be restored from history");
    assert(game.castlingRights == 0b1010 && "Castling rights must be restored from history");
    assert(game.halfMoveClock == 15 && "Half-move clock must be restored from history");

    // ==========================================
    // 2. CAPTURE TEST
    // ==========================================
    // Setup: White Knight on C3 (18), Black Pawn on D5 (35)
    game.toggle_piece(WHITE, KNIGHT, 18);
    game.toggle_piece(BLACK, PAWN, 35);
    
    // Knight captures Pawn on D5
    Move captureMove(18, 35, KNIGHT); 

    // Execute
    game.makeMove(captureMove);

    // Verify Forward Capture State
    assert((game.blackPawns & (1ULL << 35)) == 0 && "Black Pawn bitboard must clear D5");
    assert((game.blacks & (1ULL << 35)) == 0 && "Black occupancy must clear D5");
    assert(game.mailbox[35] == (WHITE | KNIGHT) && "Mailbox on D5 must be overwritten by White Knight");

    // Reversal
    game.unmakeMove(captureMove);

    // Verify Reversal Capture State
    assert((game.whiteKnight & (1ULL << 18)) != 0 && "Knight must return to C3");
    assert((game.blackPawns & (1ULL << 35)) != 0 && "Black Pawn must RESPAWN on D5");
    assert((game.blacks & (1ULL << 35)) != 0 && "Black occupancy must RESPAWN on D5");
    assert(game.mailbox[35] == (BLACK | PAWN) && "Mailbox must restore the Black Pawn identity");

    std::cout << "makeMove and unmakeMove tests passed successfully.\n";
}
