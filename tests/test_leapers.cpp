#include <cassert>
#include <cstdint>

extern std::vector<uint64_t> knightAttackMask;
extern void initKnightAttack();
extern void printBoardFormation(uint64_t object);

void test_leapers_knightAttackMask() {

    initKnightAttack();
    uint64_t d4 = knightAttackMask[27];

    assert(__builtin_popcountll(d4) == 8 && "D4 Knight must have 8 attacks");

    uint64_t b4 = knightAttackMask[25];
    assert(__builtin_popcountll(b4) == 6 && "B4 Knight must have 6 attacks");

    uint64_t d7 = knightAttackMask[51];
    assert(__builtin_popcountll(d7) == 6 && "D7 Knight must have 6 attacks");

    uint64_t d2 = knightAttackMask[11];
    assert(__builtin_popcountll(d2) == 6 && "D2 Knight must have 6 attacks");

    uint64_t a1 = knightAttackMask[0];
    assert(__builtin_popcountll(a1) == 2 && "A1 Knight must have exactly 2 attacks");
    
    assert(a1 == ((1ULL << 17) | (1ULL << 10)) && "A1 Knight attack mask is incorrect");
}

extern std::vector<uint64_t> kingAttackMask;
extern void initKingAttack();

void test_leapers_kingAttackMask() {
    initKingAttack();

    uint64_t d4 = kingAttackMask[27];
    assert(__builtin_popcountll(d4) == 8 && "D4 King must have 8 attacks");

    uint64_t a4 = kingAttackMask[24];
    assert(__builtin_popcountll(a4) == 5 && "A4 King must have 5 attacks");

    uint64_t d1 = kingAttackMask[3];
    assert(__builtin_popcountll(d1) == 5 && "D1 King must have 5 attacks");

    uint64_t h8 = kingAttackMask[63];
    assert(__builtin_popcountll(h8) == 3 && "H8 King must have exactly 3 attacks");
    
    assert(h8 == ((1ULL << 62) | (1ULL << 55) | (1ULL << 54)) && "H8 King attack mask is incorrect");
}


extern std::vector<uint64_t> whitePawnAttackMask;
extern std::vector<uint64_t> blackPawnAttackMask;
extern void initPawnAttack();

void test_leapers_pawnAttackMask(){

    initPawnAttack();

    // ==========================================
    // 1. WHITE PAWN TESTS (Attacks UP: +7, +9)
    // ==========================================

    // Central pawn: D4 (index 27) -> attacks C5 (34) and E5 (36)
    {
        uint64_t d4 = whitePawnAttackMask[27];
        assert(__builtin_popcountll(d4) == 2 && "White D4 pawn must have exactly 2 attacks");
        assert(d4 == ((1ULL << 34) | (1ULL << 36)) && "White D4 pawn attack coordinates mismatch");
    }

    // Left wall: A4 (index 24) -> attacks only B5 (33); left attack (+7) must be masked out
    {
        uint64_t a4 = whitePawnAttackMask[24];
        assert(__builtin_popcountll(a4) == 1 && "White A-file pawn must have exactly 1 attack");
        assert(a4 == (1ULL << 33) && "White A4 pawn must attack only B5");
    }

    // Right wall: H4 (index 31) -> attacks only G5 (38); right attack (+9) must be masked out
    {
        uint64_t h4 = whitePawnAttackMask[31];
        assert(__builtin_popcountll(h4) == 1 && "White H-file pawn must have exactly 1 attack");
        assert(h4 == (1ULL << 38) && "White H4 pawn must attack only G5");
    }

    // Bottom rank: A1 (index 0) -> attacks only B2 (9)
    {
        uint64_t a1 = whitePawnAttackMask[0];
        assert(__builtin_popcountll(a1) == 1 && "White A1 pawn must have exactly 1 attack");
        assert(a1 == (1ULL << 9) && "White A1 pawn must attack B2");
    }

    // Top rank boundary: E8 (index 60) -> shifts overflow 64-bit integer, mask must be 0
    {
        uint64_t e8 = whitePawnAttackMask[60];
        assert(__builtin_popcountll(e8) == 0 && "White pawn on Rank 8 cannot attack outside board");
    }

    // ==========================================
    // 2. BLACK PAWN TESTS (Attacks DOWN: -7, -9)
    // ==========================================

    // Central pawn: D5 (index 35) -> attacks C4 (26) and E4 (28)
    {
        uint64_t d5 = blackPawnAttackMask[35];
        assert(__builtin_popcountll(d5) == 2 && "Black D5 pawn must have exactly 2 attacks");
        assert(d5 == ((1ULL << 26) | (1ULL << 28)) && "Black D5 pawn attack coordinates mismatch");
    }

    // Left wall: A5 (index 32) -> attacks only B4 (25); rightward drop (-7) must be masked out
    {
        uint64_t a5 = blackPawnAttackMask[32];
        assert(__builtin_popcountll(a5) == 1 && "Black A-file pawn must have exactly 1 attack");
        assert(a5 == (1ULL << 25) && "Black A5 pawn must attack only B4");
    }

    // Right wall: H5 (index 39) -> attacks only G4 (30); leftward drop (-9) must be masked out
    {
        uint64_t h5 = blackPawnAttackMask[39];
        assert(__builtin_popcountll(h5) == 1 && "Black H-file pawn must have exactly 1 attack");
        assert(h5 == (1ULL << 30) && "Black H5 pawn must attack only G4");
    }

    // Top rank: H8 (index 63) -> attacks only G7 (54)
    {
        uint64_t h8 = blackPawnAttackMask[63];
        assert(__builtin_popcountll(h8) == 1 && "Black H8 pawn must have exactly 1 attack");
        assert(h8 == (1ULL << 54) && "Black H8 pawn must attack G7");
    }

    // Bottom rank boundary: E1 (index 4) -> underflow shifts discard bits, mask must be 0
    {
        uint64_t e1 = blackPawnAttackMask[4];
        assert(__builtin_popcountll(e1) == 0 && "Black pawn on Rank 1 cannot attack outside board");
    }
}

extern std::vector<uint64_t> whitePawnMoveMask;
extern std::vector<uint64_t> blackPawnMoveMask;
extern void initPawnMove(); 

//IMPORTANT NOTICE:
//This does not test pawn features(en passant, double push) as they are dynamic moves. 
//Second mask keeps track of those moves, and they are tested in a different file

void test_leapers_pawnMoveMask() {
    initPawnMove();

    // ==========================================
    // 1. WHITE PAWN TESTS (Pushes UP: +8 only)
    // ==========================================

    // Starting Rank: E2 (index 12) -> MUST only push to E3 (20) now
    {
        uint64_t e2 = whitePawnMoveMask[12];
        assert(__builtin_popcountll(e2) == 1 && "White E2 pawn must have exactly 1 push mask");
        assert(e2 == (1ULL << 20) && "White E2 pawn must push to E3");
    }

    // Normal Rank: E3 (index 20) -> Can only push to E4 (28)
    {
        uint64_t e3 = whitePawnMoveMask[20];
        assert(__builtin_popcountll(e3) == 1 && "White E3 pawn must have exactly 1 push mask");
        assert(e3 == (1ULL << 28) && "White E3 pawn must push to E4");
    }

    // Pre-Promotion Rank: A7 (index 48) -> Can only push to A8 (56)
    {
        uint64_t a7 = whitePawnMoveMask[48];
        assert(__builtin_popcountll(a7) == 1 && "White A7 pawn must have exactly 1 push mask");
        assert(a7 == (1ULL << 56) && "White A7 pawn must push to A8");
    }

    // ==========================================
    // 2. BLACK PAWN TESTS (Pushes DOWN: -8 only)
    // ==========================================

    // Starting Rank: D7 (index 51) -> MUST only push to D6 (43) now
    {
        uint64_t d7 = blackPawnMoveMask[51];
        assert(__builtin_popcountll(d7) == 1 && "Black D7 pawn must have exactly 1 push mask");
        assert(d7 == (1ULL << 43) && "Black D7 pawn must push to D6");
    }

    // Normal Rank: D6 (index 43) -> Can only push to D5 (35)
    {
        uint64_t d6 = blackPawnMoveMask[43];
        assert(__builtin_popcountll(d6) == 1 && "Black D6 pawn must have exactly 1 push mask");
        assert(d6 == (1ULL << 35) && "Black D6 pawn must push to D5");
    }

    // Pre-Promotion Rank: H2 (index 15) -> Can only push to H1 (7)
    {
        uint64_t h2 = blackPawnMoveMask[15];
        assert(__builtin_popcountll(h2) == 1 && "Black H2 pawn must have exactly 1 push mask");
        assert(h2 == (1ULL << 7) && "Black H2 pawn must push to H1");
    }
}
