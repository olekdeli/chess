#pragma once
#include <vector>
#include <cstdint>
#include "bitboard.hpp"

std::vector<board> crossMask;
std::vector<board> plusMask;
std::vector<board> queenMask;

void initCrossMask();
void initPlusMask();
void initQueenMask();//INITIALIZE AT THE END
