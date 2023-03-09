#include "camera.hpp"
#include "../../Math/ray.hpp"

void Camera::setPerspective(float fov, float aspect, float near, float far)
{
	m_proj = math::createPerspectiveProjectionMatrix(fov, aspect, near, far);
	m_projInv = m_proj.inverse();

	m_matricesUpdateNeeded = true;
}

void Camera::addLocalPosition(const math::Vec3f& position)
{
	updateBasis();

	m_viewInv.row(3).head<3>() += getRightVector() * position.x() + getUpVector() * position.y() + getForwardVector() * position.z();

	m_matricesUpdateNeeded = true;
}

void Camera::addWorldPosition(const math::Vec3f position)
{
	m_viewInv.row(3).head<3>() += position;

	m_matricesUpdateNeeded = true;
}

void Camera::setWorldPosition(const math::Vec3f position)
{
	m_viewInv.row(3).head<3>() = position;

	m_matricesUpdateNeeded = true;
}

void Camera::addLocalRotation(const math::Quat& rotation)
{
	math::EulerAngles ang = (math::Vec3f)rotation.toRotationMatrix().eulerAngles(0, 1, 2);
	if (!m_canRoll)
	{
		ang.roll() = 0.0f;
	}

	m_rotation *= math::eulerAnglesToQuat(ang, getRightVector(), getUpVector(), getForwardVector());

	m_basisUpdateNeeded = true;
	m_matricesUpdateNeeded = true;
}

void Camera::addLocalRotation(const math::EulerAngles& angles)
{
	math::EulerAngles ang = angles;
	if (!m_canRoll)
	{
		ang.roll() = 0.0f;
	}
	
	m_rotation *= math::eulerAnglesToQuat(ang, getRightVector(), getUpVector(), getForwardVector());

	m_basisUpdateNeeded = true;
	m_matricesUpdateNeeded = true;
}

void Camera::addWorldRotation(const math::Quat& rotation)
{
	math::EulerAngles ang = (math::Vec3f)rotation.toRotationMatrix().eulerAngles(0, 1, 2);
	if (!m_canRoll)
	{
		ang.roll() = 0.0f;
	}

	m_rotation *= math::eulerAnglesToQuat(ang, math::Vec3f(1.0f, 0.0f, 0.0f), math::Vec3f(0.0f, 1.0f, 0.0f), math::Vec3f(0.0f, 0.0f, 1.0f));

	m_basisUpdateNeeded = true;
	m_matricesUpdateNeeded = true;
}

void Camera::addWorldRotation(const math::EulerAngles& angles)
{
	math::EulerAngles ang = angles;
	if (!m_canRoll)
	{
		ang.roll() = 0.0f;
	}

	m_rotation *= math::eulerAnglesToQuat(ang, math::Vec3f(1.0f, 0.0f, 0.0f), math::Vec3f(0.0f, 1.0f, 0.0f), math::Vec3f(0.0f, 0.0f, 1.0f));

	m_basisUpdateNeeded = true;
	m_matricesUpdateNeeded = true;
}

void Camera::setWorldRotation(const math::Quat& rotation)
{
	m_rotation = rotation;

	m_basisUpdateNeeded = true;
	m_matricesUpdateNeeded = true;
}

void Camera::setWorldRotation(const math::EulerAngles& angles)
{
	m_rotation = math::eulerAnglesToQuat(angles, math::Vec3f(1.0f, 0.0f, 0.0f), math::Vec3f(0.0f, 1.0f, 0.0f), math::Vec3f(0.0f, 0.0f, 1.0f));

	m_basisUpdateNeeded = true;
	m_matricesUpdateNeeded = true;
}

void Camera::update()
{
	m_rotation.normalize();

	updateBasis();
	updateMatrices();
	updateNearPlane();
}

math::Ray Camera::generateRay(const math::Vec2i& pixelCoordinate, const math::Vec2i windowSize) const
{
	math::Vec2f position{
		(pixelCoordinate.x() + 0.5f) / windowSize.x(),
		(pixelCoordinate.y() + 0.5f) / windowSize.y()
	};

	math::Vec3f rightDir = m_nearPlane.bottomRight - m_nearPlane.bottomLeft;
	math::Vec3f upDir = m_nearPlane.topLeft - m_nearPlane.bottomLeft;

	math::Vec3f pixelPosition = m_nearPlane.bottomLeft + position.x() * rightDir + position.y() * upDir;
	math::Vec3f direction = (pixelPosition - getPosition()).normalized();

	return { getPosition(), direction };
}

void Camera::updateBasis()
{
	if (m_basisUpdateNeeded)
	{
		m_basisUpdateNeeded = false;
		
		math::Mat3f rotationMatrix = m_rotation.toRotationMatrix();
		m_viewInv.block(0, 0, 3, 3) = rotationMatrix;
	}
}

void Camera::updateMatrices()
{
	if (m_matricesUpdateNeeded)
	{
		m_matricesUpdateNeeded = false;

		updateBasis();
	}

	math::invertRTMatrix(m_viewInv, m_view);
	m_viewProj = m_view * m_proj;
	m_viewProjInv = m_projInv * m_viewInv;
}

void Camera::updateNearPlane()
{
	math::Vec3f BL(-1.0f, -1.0f, 1.0f);
	transformClipToWorld(BL, 1.0f);
	
	math::Vec3f TL(-1.0f, 1.0f, 1.0f);
	transformClipToWorld(TL, 1.0f);

	math::Vec3f BR(1.0f, -1.0f, 1.0f);
	transformClipToWorld(BR, 1.0f);

	m_nearPlane = {BL, TL, BR};
}
