#pragma once
#include "bitboard.hpp"
#include "board.hpp"

void generateMoves(const gameState& game, std::vector<Move>& moveList);
void generatePawnMoves(const gameState& game, std::vector<Move>& moveList, Colour colour);
void generateKnightMoves(const gameState& game, std::vector<Move>& moveList, Colour colour);
void generateBishopMoves(const gameState& game, std::vector<Move>& moveList, Colour colour);
void generateRookMoves(const gameState& game, std::vector<Move>& moveList, Colour colour);
void generateQueenMoves(const gameState& game, std::vector<Move>& moveList, Colour colour);
void generateKingMoves(const gameState& game, std::vector<Move>& moveList, Colour colour);

bool isSquareAttacked(const gameState& game, int index, Colour enemy);

void initAllMasks();
