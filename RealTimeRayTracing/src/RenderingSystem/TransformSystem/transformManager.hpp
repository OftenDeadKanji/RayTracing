#ifndef __TRANSFORM_MANAGER__
#define __TRANSFORM_MANAGER__
#include "../../Utils/nonCopyable.hpp"
#include <memory>
#include <unordered_map>
#include <queue>
#include "../../Math/transform.hpp"

class TransformManager
	: public NonCopyable
{
	friend class FileWriter;
public:
	using TransformID = unsigned int;
public:
	static TransformManager* createInstance();
	static TransformManager* getInstance();
	static void deleteInstance();

	TransformID addTransform(math::Transform& transform);
	std::pair<TransformID, math::Transform&> getNewTransform();
	math::Transform& getTransform(TransformID ID);

private:
	static std::unique_ptr<TransformManager> s_instance;

	std::unordered_map<TransformID, math::Transform> m_transforms;
	TransformID m_nextID = 0;
	std::queue<TransformID> m_freeIDs;

	TransformID getNextID();
};

#pragma region Inline methods definitions

inline TransformManager* TransformManager::createInstance()
{
	s_instance = std::unique_ptr<TransformManager>(new TransformManager());
	return s_instance.get();
}
inline TransformManager* TransformManager::getInstance()
{
	return s_instance.get();
}
inline void TransformManager::deleteInstance()
{
	s_instance.release();
}

inline TransformManager::TransformID TransformManager::addTransform(math::Transform& transform)
{
	TransformID id = getNextID();

	m_transforms[id] = transform;

	return id;
}
inline std::pair<TransformManager::TransformID, math::Transform&> TransformManager::getNewTransform()
{
	TransformID id = getNextID();

	math::Transform transform(math::Vec3f(0.0f, 0.0f, 0.0f));
	m_transforms[id] = transform;

	return std::pair<TransformID, math::Transform&>(id, m_transforms[id]);
}

inline math::Transform& TransformManager::getTransform(TransformManager::TransformID ID)
{
	return m_transforms[ID];
}

inline TransformManager::TransformID TransformManager::getNextID()
{
	TransformID id;
	if (m_freeIDs.empty())
	{
		id = m_nextID++;
	}
	else
	{
		id = m_freeIDs.front();
		m_freeIDs.pop();
	}

	return id;
}


#pragma endregion

inline std::unique_ptr<TransformManager> TransformManager::s_instance = nullptr;

#endif
