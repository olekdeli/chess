#include "../include/sliders.hpp"
#include "../include/bitboard.hpp"

void initPlusMask() {
    board sourcePos = 0x0000000000000001;
    plusMask.resize(64,0);

    #if MAGIC_NUMBERS == 0
	WMask.resize(64,0);
	EMask.resize(64,0);   
	NMask.resize(64,0);
	SMask.resize(64,0);
    #endif
    for(int pos = 0; pos != 64; pos++) {
        int rank = pos / 8;
        int file = pos % 8;
        
        // Shift the Rank 1 and File A constants to the current square
        board rankMask = RANK_1 << (rank * 8);
        board fileMask = FILE_A << file;
        
        // Combine them and mask out the starting square
        plusMask[pos] = (rankMask | fileMask) & ~sourcePos;
        
        
	#if MAGIC_NUMBERS == 0
		// (sourcePos - 1) gives all bits lower than the current square.
		board lowerBits = sourcePos - 1;

		// West/South are just the rank/file intersected with the lower bits
		WMask[pos] = rankMask & lowerBits;
		SMask[pos] = fileMask & lowerBits;

		// East/North are the rank/file intersected with everything EXCEPT lower bits and the source square
		EMask[pos] = rankMask & ~(lowerBits | sourcePos);
		NMask[pos] = fileMask & ~(lowerBits | sourcePos);
	#endif
	sourcePos <<= 1;
    }
}

void initCrossMask() {
    board sourcePos = 0x0000000000000001;
    crossMask.resize(64,0);

    #if MAGIC_NUMBERS == 0
	NWMask.resize(64,0);
	NEMask.resize(64,0);
	SEMask.resize(64,0);
	SWMask.resize(64,0);
    #endif

    for(int pos = 0; pos != 64; pos++) {
        board mask = 0;
        board current;



        // NORTH-EAST (+9) : Stop if on H-file or Rank 8
        current = sourcePos;
        while ((current & FILE_H) == 0 && (current & RANK_8) == 0) { 
            current <<= 9; 
            mask |= current;

	    #if MAGIC_NUMBERS == 0
		NEMask[pos] |= current;
	    #endif

        }
        
        // NORTH-WEST (+7) : Stop if on A-file or Rank 8
        current = sourcePos;
        while ((current & FILE_A) == 0 && (current & RANK_8) == 0) { 
            current <<= 7; 
            mask |= current; 

	    #if MAGIC_NUMBERS == 0
	   	 NWMask[pos] |= current;
            #endif
	}
        
        // SOUTH-EAST (-7) : Stop if on H-file or Rank 1
        current = sourcePos;
        while ((current & FILE_H) == 0 && (current & RANK_1) == 0) { 
            current >>= 7; 
            mask |= current;

	    #if MAGIC_NUMBERS == 0
	    	SEMask[pos] |= current;
	    #endif
        }
        
        // SOUTH-WEST (-9) : Stop if on A-file or Rank 1
        current = sourcePos;
        while ((current & FILE_A) == 0 && (current & RANK_1) == 0) { 
            current >>= 9; 
            mask |= current; 

	    #if MAGIC_NUMBERS == 0
	    	SWMask[pos] |= current;
	    #endif
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
