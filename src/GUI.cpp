#include "../include/GUI.hpp"

void printBoard(gameState game){
		
for(int i=0;i!=64;i++){
	if(i%8==0){
		char file = 'A'+ i/8;  ;std::cerr<<"\n"<<file<<"|";
	}
	switch(game.mailbox[i]){
		case 0b0001: std::cerr<< " ♟  " ;break;
		case 0b1001: std::cerr<< " ♙  " ;break;
		case 0b0010: std::cerr<< " ♞  "  ;break;
		case 0b1010: std::cerr<< " ♘  "  ;break;
		case 0b0011: std::cerr<< " ♝  "  ;break;
		case 0b1011: std::cerr<< " ♗  "  ;break;
		case 0b0100: std::cerr<< " ♜  "  ;break;
		case 0b1100: std::cerr<< " ♖  "  ;break;
		case 0b0101: std::cerr<< " ♛  "  ;break;
		case 0b1101: std::cerr<< " ♕  " ;break;
		case 0b0110: std::cerr<< " ♚  " ;break;
		case 0b1110: std::cerr<< " ♔  " ;break;
		case 0b0000: std::cerr<< " "<<i<<" "; break;
	} 
	
}
std::cerr<<"\n";
}



/*
♔ ♕ ♖ ♗ ♘ ♙
♚ ♛ ♜ ♝ ♞ ♟
*/
