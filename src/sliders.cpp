#include "../include/sliders.hpp"
#include "../include/bitboard.hpp"

void initPlusMask() {
    board sourcePos = 0x0000000000000001;
    plusMask.resize(64,0);

    for(int pos = 0; pos != 64; pos++) {
        int rank = pos / 8;
        int file = pos % 8;
        
        // Shift the Rank 1 and File A constants to the current square
        board rankMask = RANK_1 << (rank * 8);
        board fileMask = FILE_A << file;
        
        // Combine them and mask out the starting square
        plusMask[pos] = (rankMask | fileMask) & ~sourcePos;
        
        sourcePos <<= 1;
    }
}

void initCrossMask() {
    board sourcePos = 0x0000000000000001;
    crossMask.resize(64,0);
    for(int pos = 0; pos != 64; pos++) {
        board mask = 0;
        board current;
        
        // NORTH-EAST (+9) : Stop if on H-file or Rank 8
        current = sourcePos;
        while ((current & FILE_H) == 0 && (current & RANK_8) == 0) { 
            current <<= 9; 
            mask |= current; 
        }
        
        // NORTH-WEST (+7) : Stop if on A-file or Rank 8
        current = sourcePos;
        while ((current & FILE_A) == 0 && (current & RANK_8) == 0) { 
            current <<= 7; 
            mask |= current; 
        }
        
        // SOUTH-EAST (-7) : Stop if on H-file or Rank 1
        current = sourcePos;
        while ((current & FILE_H) == 0 && (current & RANK_1) == 0) { 
            current >>= 7; 
            mask |= current; 
        }
        
        // SOUTH-WEST (-9) : Stop if on A-file or Rank 1
        current = sourcePos;
        while ((current & FILE_A) == 0 && (current & RANK_1) == 0) { 
            current >>= 9; 
            mask |= current; 
        }
        
        crossMask[pos] = mask;
        sourcePos <<= 1;
    }
}

void initQueenMask() {
	queenMask.resize(64,0);
    for(int pos = 0; pos != 64; pos++) {
        queenMask[pos] = crossMask[pos] | plusMask[pos];
    }
}
