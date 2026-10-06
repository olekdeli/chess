#include "../include/GUI.hpp"

void printBoard(gameState game){


	std::cerr<<"\n    AA--BB--CC--DD--EE--FF--GG--HH ";
for(int rank=7;rank>=0 ;rank--){
	
	if(rank!=7) std::cout<<" |"<<rank+1;

	std::cout<<"\n"<< rank << " |";
	for(int file = 0; file!=8; file++){


	int i = file + rank*8;
	

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
		case 0b0000: std::cerr<< " "<<i<<" ";if(i<=9) std::cerr<<" "; break;
	} 
		
	}
}
std::cerr<<" |0\n   -AA--BB--CC--DD--EE--FF--GG--HH \n";

}

void checkState(const gameState& game, const std::vector<Move>& moveList){
	printBoard(game);
	std::cout<<"Poss Moves:\n";
	for(int i=0;i!=moveList.size();i++){
		std::cout<<moveList[i].getSource()<<"->"<<moveList[i].getTarget()<<"\n";
	}
	std::cerr<<"\n";
}



/*
♔ ♕ ♖ ♗ ♘ ♙
♚ ♛ ♜ ♝ ♞ ♟
*/
