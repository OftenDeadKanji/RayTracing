#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__
#include "../../Math/mathUtils.hpp"

namespace math
{
	struct Ray;
}
class Camera
{
public:
	Camera() = default;

	void setPerspective(float fov, float aspect, float near, float far);

	void addLocalPosition(const math::Vec3f& position);
	void addWorldPosition(const math::Vec3f position);
	void setWorldPosition(const math::Vec3f position);

	void addLocalRotation(const math::Quat& rotation);
	void addLocalRotation(const math::EulerAngles& angles);
	void addWorldRotation(const math::Quat& rotation);
	void addWorldRotation(const math::EulerAngles& angles);
	void setWorldRotation(const math::Quat& rotation);
	void setWorldRotation(const math::EulerAngles& angles);

	math::Vec3f getPosition() const;
	math::Vec3f getRightVector() const;
	math::Vec3f getUpVector() const;
	math::Vec3f getForwardVector() const;

	void setRollState(bool enabled);

	void update();

	void transformWorldToView(math::Vec3f& v, float w) const;
	void transformWorldToView(math::Vec4f& v) const;
	void transformViewToWorld(math::Vec3f& v, float w) const;
	void transformViewToWorld(math::Vec4f& v) const;

	void transformViewToClip(math::Vec3f& v, float w) const;
	void transformViewToClip(math::Vec4f& v) const;
	void transformClipToView(math::Vec3f& v, float w) const;
	void transformClipToView(math::Vec4f& v) const;

	void transformWorldToClip(math::Vec3f& v, float w) const;
	void transformWorldToClip(math::Vec4f& v) const;
	void transformClipToWorld(math::Vec3f& v, float w) const;
	void transformClipToWorld(math::Vec4f& v) const;

	math::Ray generateRay(const math::Vec2i& pixelCoordinate, const math::Vec2i windowSize) const;
private:
	math::Mat4f m_view = math::Mat4f::Identity();
	math::Mat4f m_viewInv = math::Mat4f::Identity();

	math::Mat4f m_proj = math::Mat4f::Identity();
	math::Mat4f m_projInv = math::Mat4f::Identity();

	math::Mat4f m_viewProj = math::Mat4f::Identity();
	math::Mat4f m_viewProjInv = math::Mat4f::Identity();

	math::Quat m_rotation = math::Quat::Identity();

	bool m_canRoll = false;

	bool m_matricesUpdateNeeded = false;
	bool m_basisUpdateNeeded = false;

	struct {
		math::Vec3f bottomLeft, topLeft, bottomRight;
	} m_nearPlane;

	void updateBasis();
	void updateMatrices();
	void updateNearPlane();
};

#pragma region Inline methods definitions
inline math::Vec3f Camera::getPosition() const
{
	return m_viewInv.row(3).head<3>();
}
inline math::Vec3f Camera::getRightVector() const
{
	return m_viewInv.row(0).head<3>();
}
inline math::Vec3f Camera::getUpVector() const
{
	return m_viewInv.row(1).head<3>();
}
inline math::Vec3f Camera::getForwardVector() const
{
	return m_viewInv.row(2).head<3>();
}

inline void Camera::setRollState(bool enabled)
{
	m_canRoll = enabled;
}

inline void Camera::transformWorldToView(math::Vec3f& v, float w) const
{
	math::Vec4f vec = math::Vec4f(v.x(), v.y(), v.z(), w);
	transformWorldToView(vec);
	v = vec.head<3>();
}
inline void Camera::transformWorldToView(math::Vec4f& v) const
{
	v *= m_view;
}
inline void Camera::transformViewToWorld(math::Vec3f& v, float w) const
{
	math::Vec4f vec = math::Vec4f(v.x(), v.y(), v.z(), w);
	transformViewToWorld(vec);
	v = vec.head<3>();
}
inline void Camera::transformViewToWorld(math::Vec4f& v) const
{
	v *= m_viewInv;
}
inline void Camera::transformViewToClip(math::Vec3f& v, float w) const
{
	math::Vec4f vec = math::Vec4f(v.x(), v.y(), v.z(), w);
	transformViewToClip(vec);
	v = vec.head<3>();
}
inline void Camera::transformViewToClip(math::Vec4f& v) const
{
	v *= m_proj;
	v /= v.w();
}
inline void Camera::transformClipToView(math::Vec3f& v, float w) const
{
	math::Vec4f vec = math::Vec4f(v.x(), v.y(), v.z(), w);
	transformClipToView(vec);
	v = vec.head<3>();
}
inline void Camera::transformClipToView(math::Vec4f& v) const
{
	v *= m_projInv;
	v /= v.w();
}
inline void Camera::transformWorldToClip(math::Vec3f& v, float w) const
{
	math::Vec4f vec = math::Vec4f(v.x(), v.y(), v.z(), w);
	transformWorldToClip(vec);
	v = vec.head<3>();
}
inline void Camera::transformWorldToClip(math::Vec4f& v) const
{
	v *= m_viewProj;
	v /= v.w();
}
inline void Camera::transformClipToWorld(math::Vec3f& v, float w) const
{
	math::Vec4f vec = math::Vec4f(v.x(), v.y(), v.z(), w);
	transformClipToWorld(vec);
	v = vec.head<3>();
}
inline void Camera::transformClipToWorld(math::Vec4f& v) const
{
	v *= m_viewProjInv;
	v /= v.w();

}
#pragma endregion

#endif
