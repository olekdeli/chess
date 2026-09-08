int main(){



	std::cerr<<"Testing leaper attack masks:\n";
	
	extern void test_leapers_knightAttackMask();
	extern void test_leapers_kingAttackMask();
	extern void test_leapers_pawnAttackMask();
	extern void test_leapers_pawnMoveMask();
	extern void test_sliders_plus();
	extern void test_sliders_cross();
	extern void test_sliders_queen();

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
	}
	catch(const std::runtime_error& e){
		std::cerr<<"\nRuntime Error: "<< e.what()<<"\n";
	}
	

		



}
