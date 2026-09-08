#pragma once
#include <iostream>
#include <vector>
#include <cstdint>

/*
Board indexing convention as follows:

  | A  B  C  D  E  F  G  H
  | --|--|--|--|--|--|--|--| 
7 | 56 57 58 59 60 61 62 63
6 | 48 49 50 51 52 53 54 55
5 | 40 41 42 43 44 45 46 47
4 | 32 33 34 35 36 37 38 39
3 | 24 25 26 27 28 29 30 31
2 | 16 17 18 19 20 21 22 23
1 | 08 09 10 11 12 13 14 15 
0 | 00 01 02 03 04 05 06 07
*/

typedef std::uint64_t board;

constexpr uint64_t FILE_A  = 0x0101010101010101ULL;
constexpr uint64_t FILE_H  = 0x8080808080808080ULL;
constexpr uint64_t FILE_AB = 0x0303030303030303ULL;
constexpr uint64_t FILE_GH = 0xC0C0C0C0C0C0C0C0ULL;
constexpr uint64_t RANK_1 =  0x00000000000000FFULL;
constexpr uint64_t RANK_8 =  0xFF00000000000000ULL;
void printBoardFormation(board object);
