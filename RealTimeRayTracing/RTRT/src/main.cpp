#include <iostream>
#include "Application/application.hpp"

#ifdef _DIST
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main()
{
#ifdef _DEBUG
	std::cout << "Hello there!" << std::endl;
#endif

	{
		RT::Application app;
		app.run();
	}

	return 0;
}