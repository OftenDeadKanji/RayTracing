#ifndef __TRANSFORM_HPP__
#define __TRANSFORM_HPP__
#include "mathUtils.hpp"

namespace math
{
	class Transform
	{
	public:
		Transform() = default;
		Transform(const math::Vec3f& translation, const math::Quat& rotation = math::Quat::Identity(), const math::Vec3f& scale = math::Vec3f(1.0f, 1.0f, 1.0f));

		void setTranslation(const math::Vec3f& translation);
		const math::Vec3f& getTranslation() const;

		void setRotation(const math::Quat& rotation);
		const math::Quat& getRotation() const;

		void setScale(const math::Vec3f& scale);
		const math::Vec3f& getScale() const;

		void localToGlobal(math::Vec3f& v, float w) const;
		void localToGlobal(math::Vec4f& v) const;

		void globalToLocal(math::Vec3f& v, float w) const;
		void globalToLocal(math::Vec4f& v) const;

		const math::Mat4f& getMatrix() const;
		const math::Mat4f& getInvMatrix() const;
	private:
		math::Vec3f m_scale;
		math::Quat m_rotation;

		math::Mat4f m_transform = math::Mat4f::Identity();
		math::Mat4f m_transformInv = math::Mat4f::Identity();

		static constexpr bool UPDATE_QUAT_WITH_INTERVALS = false;
		static constexpr int maxNoQuatUpdate = 20;
		int currentNoQuatUpdate = 0;
	};

#pragma region Inline methods definitions

	inline Transform::Transform(const math::Vec3f& translation, const math::Quat& rotation, const math::Vec3f& scale)
	{
		m_transform.row(3).head<3>() = translation;
		m_rotation = rotation;
		m_scale = scale;
		m_transform.block(0, 0, 3, 3) = rotation.toRotationMatrix() * m_scale.asDiagonal();
		m_transformInv = m_transform.inverse();
	}

	inline void Transform::setTranslation(const math::Vec3f& translation)
	{
		m_transform.row(3).head<3>() = translation;
		m_transformInv = m_transform.inverse();
	}
	inline const math::Vec3f& Transform::getTranslation() const
	{
		return m_transform.row(3).head<3>();
	}

	inline void Transform::setRotation(const math::Quat& rotation)
	{
		m_rotation = rotation;

		if (UPDATE_QUAT_WITH_INTERVALS || currentNoQuatUpdate++ == maxNoQuatUpdate)
		{
			currentNoQuatUpdate = 0;
			m_rotation.normalize();
		}

		m_transform.block(0, 0, 3, 3) = m_rotation.toRotationMatrix() * m_scale.asDiagonal();
		m_transformInv = m_transform.inverse();

	}
	inline const math::Quat& Transform::getRotation() const
	{
		return m_rotation;
	}

	inline void Transform::setScale(const math::Vec3f& scale)
	{
		m_scale = scale;
		m_transform.block(0, 0, 3, 3) = m_rotation.toRotationMatrix() * m_scale.asDiagonal();
		m_transformInv = m_transform.inverse();
	}
	inline const math::Vec3f& Transform::getScale() const
	{
		return m_scale;
	}

	inline void Transform::localToGlobal(math::Vec3f& v, float w) const
	{
		math::Vec4f v4 = { v[0], v[1], v[2], w };
		localToGlobal(v4);
		v = { v4[0], v4[1], v4[2] };
	}
	inline void Transform::localToGlobal(math::Vec4f& v) const
	{
		v *= m_transform;
	}

	inline void Transform::globalToLocal(math::Vec3f& v, float w) const
	{
		math::Vec4f v4 = { v[0], v[1], v[2], w };
		globalToLocal(v4);
		v = { v4[0], v4[1], v4[2] };
	}
	inline void Transform::globalToLocal(math::Vec4f& v) const
	{
		v *= m_transformInv;
	}

	inline const math::Mat4f& Transform::getMatrix() const
	{
		return m_transform;
	}
	inline const math::Mat4f& Transform::getInvMatrix() const
	{
		return m_transformInv;
	}
#pragma endregion

}
#endif
