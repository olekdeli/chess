int main(){



	std::cerr<<"Testing leaper attack masks:\n";
	
	extern void test_leapers_knightAttackMask();
	extern void test_leapers_kingAttackMask();
	extern void test_leapers_pawnAttackMask();
	extern void test_leapers_pawnMoveMask();
	
	extern void test_sliders_plus();
	extern void test_sliders_cross();
	extern void test_sliders_queen();

	extern void test_togglePiece();
	extern void test_loadFEN();

	extern void test_moveGen_pawnAttack();
	extern void test_moveGen_pawnMove();
	extern void test_moveGen_pawnPromotion();
	extern void test_moveGen_knight();
	extern void test_moveGen_bishop();
	extern void test_moveGen_queen();
	extern void test_moveGen_rook();
	extern void test_moveGen_king();

	extern void test_moveGen_isSquareAttacked();

	extern void test_makeMove_and_unmake();

	try{
		test_leapers_knightAttackMask();
		test_leapers_kingAttackMask();
		test_leapers_pawnAttackMask();
		test_leapers_pawnMoveMask();
		std::cout<<"=====Leaper attack masks passed=====\n";
		
		test_sliders_cross();
		test_sliders_plus();
		test_sliders_queen();
		std::cout<<"=====Slider attack masks passed=====\n";


		test_togglePiece();
		test_loadFEN();
		std::cout<<"=====Toggle/FEN tests passed=====\n";

		test_moveGen_pawnAttack();
		test_moveGen_pawnMove();
		test_moveGen_pawnPromotion();
		test_moveGen_knight();
		test_moveGen_bishop();

		test_moveGen_rook();
		test_moveGen_queen();
		test_moveGen_king();
		std::cout<<"=====MoveGen tests passed========\n";

		test_moveGen_isSquareAttacked();
		std::cout<<"=====attackDetection tests passed========\n";

		void test_makeMove_and_unmake();
		std::cout<<"=====move history tests passed========\n";


	}
	catch(const std::runtime_error& e){
		std::cerr<<"\nRuntime Error: "<< e.what()<<"\n";
	}
}
