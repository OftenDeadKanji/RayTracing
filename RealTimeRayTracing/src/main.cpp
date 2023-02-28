#include <iostream>
#include "Application/application.hpp"
#include "math/mathUtils.hpp"

#ifdef _DIST
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main()
{
#ifdef _DEBUG
	std::cout << "Hello there!" << std::endl;
#endif
	
	glfwInit();
	{
		Application app;
		app.run();
	}
	glfwTerminate();

	return 0;
}