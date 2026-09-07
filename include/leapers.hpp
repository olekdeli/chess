#pragma once
#include "bitboard.hpp"

//Attack/Move masks
inline std::vector<board> knightAttackMask;
inline std::vector<board> kingAttackMask;

void initKnightAttack();
void initKingAttack();
