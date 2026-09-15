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



void gameState::makeMove(Move move) {
    int source = move.getSource();
    int target = move.getTarget();
    
    int movingPieceRaw = mailbox[source];
    Colour us          = static_cast<Colour>(movingPieceRaw & 0b1000);
    PieceType piece    = static_cast<PieceType>(movingPieceRaw & 0b0111);
    
    int capturedPieceRaw = mailbox[target];
    PieceType captured   = static_cast<PieceType>(capturedPieceRaw & 0b0111);
    
    // 2. Save the irreversible state to the history stack
    this->history[currentPly] = UndoInfo(captured, epSquare, castlingRights, halfMoveClock);
    
    // 3. Remove the captured enemy piece from the bitboards (if there is one)
    if (captured != 0) {
        Colour them = (us == WHITE) ? BLACK : WHITE;
        toggle_piece(them, captured, target);
    }
    
    // 4. Move our piece: Toggle it OFF the source, and ON the target
    toggle_piece(us, piece, source);
    toggle_piece(us, piece, target);
    
    // 5. Update state variables (Half-move clock, En Passant, Castling)
    // You will need to write the logic here later to update castling rights if a King or Rook moves,
    // and reset the halfMoveClock if a pawn moves or a capture happens.
    
    // 6. Go one layer deeper in the tree
    currentPly++;
}


void gameState::unmakeMove(Move move){

    currentPly--;

    UndoInfo undo = history[currentPly];

    int source = move.getSource();
    int target = move.getTarget();
    
    int movingPieceRaw = mailbox[target];
    Colour us          = static_cast<Colour>(movingPieceRaw & 0b1000);
    Colour enemyColour = (us == WHITE)? BLACK : WHITE; 
    PieceType piece    = static_cast<PieceType>(movingPieceRaw & 0b0111);
    
    toggle_piece(us, piece, source);
    toggle_piece(us, piece, target);

    PieceType captured = undo.getCapturedPiece();
    
    if(captured!=0) toggle_piece(enemyColour, history[currentPly].getCapturedPiece(),target);

    epSquare       = undo.getEpSquare();
    castlingRights = undo.getCastlingRights();
    halfMoveClock  = undo.getHalfMoveClock();
}
