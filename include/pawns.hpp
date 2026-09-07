#pragma once
#include "bitboard.hpp"

//Attack Masks
inline std::vector<board> whitePawnAttackMask; 
inline std::vector<board> whitePawnMoveMask;
inline std::vector<board> blackPawnAttackMask;
inline std::vector<board> blackPawnMoveMask;

void initPawnMove();
void initPawnAttack();
