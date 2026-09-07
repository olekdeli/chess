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
