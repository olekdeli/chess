#include "../include/board.hpp"

void gameState::toggle_mailbox(int index, PieceType piece, Colour colour) {
    if (mailbox[index] == 0) {
        // Instantly merge the 4 bits without any CPU branching
        mailbox[index] = piece | colour; 
    } else {
        mailbox[index] = 0;
    }
}

void gameState::toggle_piece(Colour colour, PieceType type, int square){

	board squareMask = 1ULL << square;

	//Delete from global occupation
	allOccupied ^= squareMask;
	//Delete from team occupation (white)
	if(colour==WHITE){
		whites ^= squareMask;
		switch (type) {
			//Delete from piece occupation (white)
			case PAWN:   whitePawns  ^= squareMask; break;
			case KNIGHT: whiteKnight ^= squareMask; break;
			case BISHOP: whiteBishop ^= squareMask; break;
			case ROOK:   whiteRook   ^= squareMask; break;
			case QUEEN:  whiteQueen  ^= squareMask; break;
			case KING:   whiteKing   ^= squareMask; break;
			}

	}
	if(colour==BLACK){
		blacks ^= squareMask;
		switch (type) {
			//Delete from piece occupation (black)
			case PAWN:   blackPawns  ^= squareMask;  break;
			case KNIGHT: blackKnight ^= squareMask;  break;
			case BISHOP: blackBishop ^= squareMask;  break;
			case ROOK:   blackRook   ^= squareMask;  break;
			case QUEEN:  blackQueen  ^= squareMask;  break;
			case KING:   blackKing   ^= squareMask;  break;
			}
	}
	toggle_mailbox(square, type, colour);

}



void gameState::loadFEN(const std::string& fen) {
    if (fen.empty()) return;

    int file = 0;
    int rank = 7; // Start at Rank 8 (which is rank index 7 in a 0-indexed system)

    for (size_t i = 0; i < fen.length(); i++) {
        char c = fen[i];

        // The first space marks the end of the piece placement field
        if (c == ' ') break; 

        if (c == '/') {
            rank--;   // Move down one rank
            file = 0; // Reset to the A-file
        } else if (c>= 48 && c<= 57) { //ASCII '0'->48, '9'->57
            file += (c - '0'); 
        } else {
            // Calculate exact 0-63 index based on current rank and file
            int square = rank * 8 + file;
            
            switch (c) {
		// Black Pieces (Lowercase)
                case 'p': toggle_piece(BLACK, PAWN, square); break;
                case 'n': toggle_piece(BLACK, KNIGHT, square); break;
                case 'b': toggle_piece(BLACK, BISHOP, square); break;
                case 'r': toggle_piece(BLACK, ROOK, square); break;
                case 'q': toggle_piece(BLACK, QUEEN, square); break;
                case 'k': toggle_piece(BLACK, KING, square); break;
                
                // White Pieces (Uppercase)
                case 'P': toggle_piece(WHITE, PAWN, square); break;
                case 'N': toggle_piece(WHITE, KNIGHT, square); break;
                case 'B': toggle_piece(WHITE, BISHOP, square); break;
                case 'R': toggle_piece(WHITE, ROOK, square); break;
                case 'Q': toggle_piece(WHITE, QUEEN, square); break;
                case 'K': toggle_piece(WHITE, KING, square); break;
            }
            file++;
        }
    }
}

