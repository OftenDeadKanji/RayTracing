#include <iostream>

int main(int argc, char** argv)
{
#ifdef _DEBUG
	std::cout << "Hello there!" << std::endl;

	std::cout << "Received " << argc - 1 << " additional arguments:" << std::endl;

	for(int i =1; i < argc; ++i)
	{
		std::cout << '\t' << argv[i] << "\n";
	}
	std::cout << std::endl;
#endif
	
}