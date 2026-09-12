#pragma once
#include <vector>
#include <cstdint>
#include "bitboard.hpp"

inline std::vector<board> crossMask;
inline std::vector<board> plusMask;
inline std::vector<board> queenMask;

//Only for the prototype (before doing magic numbers )
#if MAGIC_NUMBERS == 0
inline std::vector<board> NWMask;
inline std::vector<board> NEMask;
inline std::vector<board> SEMask;
inline std::vector<board> SWMask;
//
inline std::vector<board> NMask;
inline std::vector<board> EMask;
inline std::vector<board> SMask;
inline std::vector<board> WMask;
#endif
//---------------------------------------------------

void initCrossMask();
void initPlusMask();
void initQueenMask();//INITIALIZE AT THE END
