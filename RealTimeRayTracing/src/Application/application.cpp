#include "application.hpp"
#include "EventSystem/eventManager.hpp"
#include "../RenderingSystem/Renderer/renderer.hpp"
#include "../ResourceManagers/meshManager.hpp"
#include <thread>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "../Utils/FileWriter/fileWriter.hpp"
#include "../RenderingSystem/TransformSystem/transformManager.hpp"

Application::Application()
{
	m_window.init(WindowProperties(
		math::Vec2i(1600, 900), WindowMode::Windowed, "Real-time ray tracing", true
	));

	auto* renderer = Renderer::createInstance();
	renderer->initScreenTexture(m_window.getSize() / 2);
	
	renderer->setSceneToRender(&m_scene);

	auto* transformManager = TransformManager::createInstance();

	auto* meshManager = MeshManager::createInstance();
	//meshManager->init();
	
	auto* materialManager = MaterialManager::createInstance();

	auto* eventManager = EventManager::createInstance();
	eventManager->addWindowListener(this);

	//setupMaterials();
	//setupScene();

	loadAppData();

	camera.setPerspective(45.0f, static_cast<float>(m_window.getSize().x()) / m_window.getSize().y(), 0.1f, 1000.0f);
}

Application::~Application()
{
	saveAppData();

	m_scene.clear();
	EventManager::deleteInstance();
	MeshManager::deleteInstance();
	Renderer::deleteInstance();
}

void Application::run()
{
	auto* eventManager = EventManager::getInstance();
	auto* renderer = Renderer::getInstance();

	while (m_mainLoopCondition)
	{
		timer.stop();
		m_deltaTime = timer.getTimeInSec();
		if (m_deltaTime >= (1.0f / 60.0f))
		{
			m_window.setTitle("Real-time ray tracing    " + std::to_string(m_deltaTime) + "    " + std::to_string(static_cast<int>(1.0f / m_deltaTime)) + " FPS");

			timer.start();
			eventManager->checkForEvents();
			processInput();

			renderer->render(m_window, camera);
			m_window.flush();
		}

		std::this_thread::yield();
	}
}

void Application::onWindowResize(const math::Vec2i& newSize)
{
	m_window.setSize(newSize);
	camera.setPerspective(45.0f, static_cast<float>(m_window.getSize().x()) / m_window.getSize().y(), 0.1f, 1000.0f);
	Renderer::getInstance()->initScreenTexture(m_window.getSize() / 2);
}

void Application::onMouseMove(const math::Vec2i& newPos)
{
	m_mousePreviousPosition = m_mousePosition;
	m_mousePosition = newPos;

	m_mousePositionDelta = m_mousePosition - m_mousePreviousPosition;
	if (m_leftMouseButtonState)
	{
		m_leftMouseButtonHoldPositionDelta = m_mousePosition - m_mousePositionOnLeftClick;
	}
	if (m_rightMouseButtonState)
	{
		m_rightMouseButtonHoldPositionDelta = m_mousePosition - m_mousePositionOnRightClick;
	}
}

void Application::processCameraControl()
{
	math::Vec3f movement{ 0.0f, 0.0f, 0.0f };
	math::EulerAngles rotation{ math::Vec3f{0.0f, 0.0f, 0.0f} };

	if (m_keyStates[GLFW_KEY_W])
	{
		movement.z() += m_cameraMovementSpeed;
	}
	if (m_keyStates[GLFW_KEY_S])
	{
		movement.z() -= m_cameraMovementSpeed;
	}

	if (m_keyStates[GLFW_KEY_D])
	{
		movement.x() += m_cameraMovementSpeed;
	}
	if (m_keyStates[GLFW_KEY_A])
	{
		movement.x() -= m_cameraMovementSpeed;
	}

	if (m_keyStates[GLFW_KEY_LEFT_CONTROL])
	{
		movement.y() -= m_cameraMovementSpeed;
	}
	if (m_keyStates[GLFW_KEY_SPACE])
	{
		movement.y() += m_cameraMovementSpeed;
	}

	if (m_keyStates[GLFW_KEY_LEFT_SHIFT])
	{
		movement *= m_cameraMovementSpeedup;
	}

	if (m_leftMouseButtonState)
	{
		rotation.pitch() -= m_leftMouseButtonHoldPositionDelta.y();
		rotation.yaw() -= m_leftMouseButtonHoldPositionDelta.x();
	}

	movement *= m_deltaTime;
	rotation *= m_cameraRotationSpeed * m_deltaTime;

	camera.addLocalPosition(movement);
	camera.addLocalRotation(math::EulerAngles({ rotation.pitch(), 0.0f, 0.0f }));
	camera.addWorldRotation(math::EulerAngles({0.0f, rotation.yaw(), 0.0f}));
	camera.update();
}

void Application::processImGui()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Scene objects");
	ImGui::Text("Objects:");
	ImGui::End();
}

void Application::setupMaterials()
{
	auto* materialManager = MaterialManager::getInstance();

	auto redMat = std::make_shared<Material>();
	redMat->color = { 1.0f, 0.0f, 0.0f };
	redMat->shininess = 32.0f;
	redMat->isEmmisive = false;
	
	materialManager->addMaterial(redMat, "RedMaterial");
	
	auto greenMat = std::make_shared<Material>();
	greenMat->color = { 0.0f, 1.0f, 0.0f };
	greenMat->shininess = 64.0f;
	greenMat->isEmmisive = false;
	
	materialManager->addMaterial(greenMat, "GreenMaterial");
}

void Application::setupScene()
{
	auto* meshManager = MeshManager::getInstance();
	auto* materialManager = MaterialManager::getInstance();

	m_scene.setBackgroundColor({ 1.0f, 0.9f, 0.15f });
	m_scene.setAmbientLight({ 0.05f, 0.05f, 0.05f });
	
	m_scene.addDirectionalLight({ 0.2f, 0.2f, 0.2f }, { 1.0f, -1.0f, 1.0f });
	
	m_scene.addPointLight({ 10.0f, 10.0f, 100.0f }, { 0.0f, 15.0f, 100.0f });
	m_scene.addPointLight({ 10.0f, 100.0f, 100.0f }, { 0.0f, 11.0f, 50.0f });
	
	m_scene.addSphereObject({ 0.0f, 0.0f, 100.0f }, 10.0f, materialManager->getMaterial("RedMaterial"));
	
	m_scene.addMeshObject(meshManager->getUnitCube(), math::Transform({ 0.0f, -10.0f, 50.0f }, math::Quat::Identity(), { 10.0f, 10.0f, 10.0f }), materialManager->getMaterial("GreenMaterial"));
}

void Application::saveAppData()
{
	FileWriter writer;

	std::ofstream fileMaterials("materials.bin", std::ios::out | std::ios::binary | std::ios::trunc);
	writer.saveToBinaryFile(fileMaterials, *MaterialManager::getInstance());

	std::ofstream fileTransforms("transforms.bin", std::ios::out | std::ios::binary | std::ios::trunc);
	writer.saveToBinaryFile(fileTransforms, *TransformManager::getInstance());

	std::ofstream fileMeshes("meshes.bin", std::ios::out | std::ios::binary | std::ios::trunc);
	writer.saveToBinaryFile(fileMeshes, *MeshManager::getInstance());

	std::ofstream fileScene("scene.bin", std::ios::out | std::ios::binary | std::ios::trunc);
	writer.saveToBinaryFile(fileScene, m_scene);
}

void Application::loadAppData()
{
	FileWriter writer;

	std::ifstream fileMaterials("materials.bin", std::ios::in | std::ios::binary);
	if (fileMaterials.is_open())
	{
		writer.loadFromBinaryFile(fileMaterials, *MaterialManager::getInstance());
	}

	std::ifstream fileTransforms("transforms.bin", std::ios::in | std::ios::binary);
	if (fileTransforms.is_open())
	{
		writer.loadFromBinaryFile(fileTransforms, *TransformManager::getInstance());
	}

	std::ifstream fileMeshes("meshes.bin", std::ios::in | std::ios::binary);
	if (fileMeshes.is_open())
	{
		writer.loadFromBinaryFile(fileMeshes, *MeshManager::getInstance());
	}

	std::ifstream fileScene("scene.bin", std::ios::in | std::ios::binary);
	if (fileScene.is_open())
	{
		writer.loadFromBinaryFile(fileScene, m_scene);
	}
}
