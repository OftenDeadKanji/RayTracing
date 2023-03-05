#include <iostream>
#include "Application/application.hpp"
#include "Math/mathUtils.hpp"

#ifdef _DIST
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main()
{
#ifdef _DEBUG
	std::cout << "Hello there!" << std::endl;
#endif
	
	if (!glfwInit())
	{
		const char* info;
		int error = glfwGetError(&info);
		std::cout << "Error: " << error << '\t' << info << std::endl;

		return 0;
	}
	{
		Application app;
		app.run();
	}
	glfwTerminate();

	return 0;
}