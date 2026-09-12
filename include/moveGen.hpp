#pragma once
#include "bitboard.hpp"
#include "board.hpp"

struct Move {
    uint16_t moveValue;

    Move(int source, int target, int flag = 0) {
        moveValue = (source & 0x3F) | ((target & 0x3F) << 6) | ((flag & 0xF) << 12);
    }

    inline int getSource() const { return moveValue & 0x3F; }
    inline int getTarget() const { return (moveValue >> 6) & 0x3F; }
    inline int getFlag() const { return (moveValue >> 12) & 0xF; }
};

void generateMoves(const gameState& game, std::vector<Move>& moveList);
void generatePawnMoves(const gameState& game, std::vector<Move>& moveList, Colour colour);
void generateKnightMoves(const gameState& game, std::vector<Move>& moveList, Colour colour);

void generateBishopMoves(const gameState& game, std::vector<Move>& moveList, Colour colour);

void generateRookMoves(const gameState& game, std::vector<Move>& moveList, Colour colour);
void generateQueenMoves(const gameState& game, std::vector<Move>& moveList, Colour colour);
void generateKingMoves(const gameState& game, std::vector<Move>& moveList, Colour colour);
