int main(){



	std::cerr<<"Testing leaper attack masks:\n";
	
	extern void test_leapers_knightAttackMask();
	extern void test_leapers_kingAttackMask();
	try{
		test_leapers_knightAttackMask();
		test_leapers_kingAttackMask();
		std::cout<<"=====Leaper attack masks passed=====\n";
	}
	catch(const std::runtime_error& e){
		std::cerr<<"\nRuntime Error: "<< e.what()<<"\n";
	}



}
