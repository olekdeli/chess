int main(){



	std::cerr<<"Testing leaper attack masks:\n";
	
	extern void test_leapers_knightAttackMask();
	extern void test_leapers_kingAttackMask();
	extern void test_leapers_pawnAttackMask();
	extern void test_leapers_pawnMoveMask();
	try{
		test_leapers_knightAttackMask();
		test_leapers_kingAttackMask();
		test_leapers_pawnAttackMask();
		test_leapers_pawnMoveMask();
		std::cout<<"=====Leaper attack masks passed=====\n";
	}
	catch(const std::runtime_error& e){
		std::cerr<<"\nRuntime Error: "<< e.what()<<"\n";
	}

		



}
