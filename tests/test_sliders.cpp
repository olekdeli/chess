#include <cassert>
#include <cstdint>
#include <vector>

extern std::vector<uint64_t> plusMask;
extern std::vector<uint64_t> crossMask;
extern std::vector<uint64_t> queenMask;

extern void initPlusMask();
extern void initCrossMask();
extern void initQueenMask();

void test_sliders_plus(){
    initPlusMask();
    {
        uint64_t d4_rook = plusMask[27];
        // 7 squares on the D-file, 7 squares on Rank 4.
        assert(__builtin_popcountll(d4_rook) == 14 && "D4 Rook must have exactly 14 attacks");
        // Verify it does NOT attack its own square
        assert((d4_rook & (1ULL << 27)) == 0 && "Rook must not attack its own square");
    }

    // Corner: A1 (index 0).
    {
        uint64_t a1_rook = plusMask[0];
        // 7 squares on the A-file, 7 squares on Rank 1.
        assert(__builtin_popcountll(a1_rook) == 14 && "A1 Rook must have exactly 14 attacks");
    }
}

void test_sliders_cross(){
    initCrossMask();
    // Center: D4 (index 27).
    {
        uint64_t d4_bishop = crossMask[27];
        // Longest diagonal has 7 squares, the intersecting one has 6 (excluding the bishop).
        assert(__builtin_popcountll(d4_bishop) == 13 && "D4 Bishop must have exactly 13 attacks");
    }

    // Corner: A1 (index 0).
    {
        uint64_t a1_bishop = crossMask[0];
        // Can only traverse the main diagonal (A1 to H8).
        assert(__builtin_popcountll(a1_bishop) == 7 && "A1 Bishop must have exactly 7 attacks");
        // Explicitly check H8 (index 63)
        assert((a1_bishop & (1ULL << 63)) && "A1 Bishop must reach H8");
    }
}

void test_sliders_queen(){
	initCrossMask();
	initPlusMask();
	initQueenMask();
    // Center: D4 (index 27).
    {
        uint64_t d4_queen = queenMask[27];
        // 14 (Rook) + 13 (Bishop) = 27 total squares.
        assert(__builtin_popcountll(d4_queen) == 27 && "D4 Queen must have exactly 27 attacks");
    }

    // Corner: A1 (index 0).
    {
        uint64_t a1_queen = queenMask[0];
        // 14 (Rook) + 7 (Bishop) = 21 total squares.
        assert(__builtin_popcountll(a1_queen) == 21 && "A1 Queen must have exactly 21 attacks");
    }
}
