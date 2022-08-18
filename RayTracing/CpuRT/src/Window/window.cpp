#include "window.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#pragma region GLFW callback functions
void framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);
	auto* userWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	if (userWindow)
	{
		userWindow->windowResizeCallback({ width, height });
	}
}

void window_close_callback(GLFWwindow* window)
{
	auto* userWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	if (userWindow)
	{
		userWindow->windowCloseCallback(glfwWindowShouldClose(window));
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	auto* userWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	if (userWindow)
	{
		userWindow->keyboardKeyCallback(convertToKeyboardKey(key), convertToKeyboardKeyAction(action));
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	ImGuiIO& io = ImGui::GetIO();
	io.AddMouseButtonEvent(button, action);

	if (!io.WantCaptureMouse)
	{
		auto* userWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		if (userWindow)
		{
			userWindow->mouseButtonCallback(convertToMouseButton(button), convertToMouseButtonAction(action));
		}
	}
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	auto* userWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	if (userWindow)
	{
		userWindow->cursorPositionCallback({ xpos, ypos });
	}
}
#pragma endregion


Window::Window(WindowProperties properties)
	: m_properties(std::move(properties))
{
	glfwInit();

	this->createGLFWWindow();
	this->initializeOpenGL();
	this->initImGUI();

	glfwSetInputMode(this->m_glfwWindowPtr, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetCursorPos(this->m_glfwWindowPtr, this->m_properties.width / 2.0, this->m_properties.height / 2.0);
}

Window::Window(Window&& other) noexcept
	: m_properties(std::move(other.m_properties)), m_glfwWindowPtr(other.m_glfwWindowPtr)
{
	other.m_glfwWindowPtr = nullptr;
}

Window::~Window()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	if (this->m_glfwWindowPtr)
	{
		glfwDestroyWindow(this->m_glfwWindowPtr);
	}

	glfwTerminate();
}

Window& Window::operator=(Window&& other) noexcept
{
	if (this != &other)
	{
		this->m_properties = other.m_properties;
		this->m_glfwWindowPtr = other.m_glfwWindowPtr;
		other.m_glfwWindowPtr = nullptr;
	}

	return *this;
}

void Window::setSize(const Size& size)
{
	this->m_properties.width = size.x;
	this->m_properties.height = size.y;

	glfwSetWindowSize(this->m_glfwWindowPtr, this->m_properties.width, this->m_properties.height);
}

Size Window::getSize()
{
	return { this->m_properties.width, this->m_properties.height };
}

void Window::setTitle(const std::string& title)
{
	this->m_properties.title = title;
	glfwSetWindowTitle(this->m_glfwWindowPtr, this->m_properties.title.c_str());
}
const std::string& Window::getTitle()
{
	return this->m_properties.title;
}

void Window::setIcon(const std::string& iconFilePath)
{
	//this->properties.IconFilePath = iconFilePath;
	//??
}

constexpr float colorNormalizeFactor()
{
	return 1.0f / 255.0f;
}

void Window::fillWithColorRGB(const vec3& color)
{
	constexpr float normalizeFactor = colorNormalizeFactor();
	glClearColor(color.r * normalizeFactor, color.g * normalizeFactor, color.b * normalizeFactor, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Window::fillWithColorRGBf(const vec3& color)
{
	glClearColor(color.r, color.g, color.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Window::swapBuffers()
{
	//ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(this->m_glfwWindowPtr);
}

void Window::attachEventManager(EventManager& manager)
{
	this->m_eventManagerPtr = &manager;

	glfwSetWindowCloseCallback(m_glfwWindowPtr, window_close_callback);
	glfwSetFramebufferSizeCallback(m_glfwWindowPtr, framebuffer_size_callback);
	glfwSetKeyCallback(m_glfwWindowPtr, key_callback);
	glfwSetMouseButtonCallback(m_glfwWindowPtr, mouse_button_callback);
	glfwSetCursorPosCallback(m_glfwWindowPtr, cursor_position_callback);

	glfwSetWindowUserPointer(this->m_glfwWindowPtr, this);
}

void Window::windowCloseCallback(bool shouldWindowClose) const
{
	this->m_eventManagerPtr->windowCloseCallback(shouldWindowClose);
}

void Window::windowResizeCallback(vec2 size) const
{
	this->m_eventManagerPtr->windowResizeCallback(size);
}

void Window::keyboardKeyCallback(KeyboardKey key, KeyboardKeyAction action) const
{
	this->m_eventManagerPtr->keyboardKeyCallback(key, action);
}

void Window::mouseButtonCallback(MouseButton button, MouseButtonAction action) const
{
	this->m_eventManagerPtr->mouseButtonCallback(button, action);
}

void Window::cursorPositionCallback(vec2 position) const
{
	this->m_eventManagerPtr->cursorPositionCallback(position);
}

void Window::resetCursorPos()
{
	glfwSetCursorPos(this->m_glfwWindowPtr, this->m_properties.width / 2.0, this->m_properties.height / 2.0);
}

GLFWwindow* Window::getGLFWWindow() const
{
	return this->m_glfwWindowPtr;
}

void Window::createGLFWWindow()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	this->m_glfwWindowPtr = glfwCreateWindow(
		this->m_properties.width,
		this->m_properties.height,
		this->m_properties.title.c_str(),
		nullptr,
		nullptr
	);

	glfwSetWindowAttrib(this->m_glfwWindowPtr, GLFW_RESIZABLE, GLFW_FALSE);
	glfwMakeContextCurrent(this->m_glfwWindowPtr);
}

void Window::centerWindow() const
{
	if (const auto monitor = glfwGetPrimaryMonitor())
	{
		if (const auto mode = glfwGetVideoMode(monitor))
		{
			int windowWidth, windowHeight;
			glfwGetWindowSize(this->m_glfwWindowPtr, &windowWidth, &windowHeight);

			glfwSetWindowPos(this->m_glfwWindowPtr, (mode->width - windowWidth) / 2, (mode->height - windowHeight) / 2);
		}
	}
}

void Window::initializeOpenGL()
{
	if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		glViewport(0, 0, this->getSize().x, this->getSize().y);
	}
	else
	{
		//TODO: exception
	}

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_MULTISAMPLE);
}

void Window::initImGUI()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	auto& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(this->m_glfwWindowPtr, false);
	ImGui_ImplOpenGL3_Init("#version 430");
}
