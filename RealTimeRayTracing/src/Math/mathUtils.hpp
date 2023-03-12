#ifndef __MATH_UTILS_HPP__
#define __MATH_UTILS_HPP__
#include "Eigen/Dense"
#include <cmath>

namespace math
{
	using Vec2i = Eigen::Matrix<int32_t, 1, 2, Eigen::RowMajor>;

	using Vec2f = Eigen::Matrix<float, 1, 2, Eigen::RowMajor>;
	using Vec3f = Eigen::Matrix<float, 1, 3, Eigen::RowMajor>;
	using Vec4f = Eigen::Matrix<float, 1, 4, Eigen::RowMajor>;

	using Mat3f = Eigen::Matrix<float, 3, 3, Eigen::RowMajor>;
	using Mat4f = Eigen::Matrix<float, 4, 4, Eigen::RowMajor>;

	using Quat = Eigen::Quaternionf;

	struct EulerAngles
		: public Vec3f
	{
		auto& pitch()
		{
			return x();
		}

		const auto& pitch() const
		{
			return x();
		}

		auto& yaw()
		{
			return y();
		}

		const auto& yaw() const
		{
			return y();
		}

		auto& roll()
		{
			return z();
		}

		const auto& roll() const
		{
			return z();
		}

		EulerAngles(const Vec3f& v)
		{
			x() = v.x();
			y() = v.y();
			z() = v.z();
		}

		EulerAngles& operator=(const Vec3f& v)
		{
			x() = v.x();
			y() = v.y();
			z() = v.z();

			return *this;
		}
	};

	constexpr float PI = 3.141592;

	constexpr float deg2rad(float deg);
	Quat eulerAnglesToQuat(const EulerAngles& angles, const Vec3f& xAxis, const Vec3f& yAxis, const Vec3f& zAxis);
	Mat4f createPerspectiveProjectionMatrix(float fov, float aspect, float near, float far);
	void invertRTMatrix(const Mat4f& src, Mat4f& dst);
	

	constexpr float deg2rad(float deg)
	{
		return (deg * PI) / 180.0f;
	}
	inline Quat eulerAnglesToQuat(const EulerAngles& angles, const Vec3f& xAxis, const Vec3f& yAxis, const Vec3f& zAxis)
	{
		return { Eigen::AngleAxisf(angles.roll(), zAxis) * Eigen::AngleAxisf(angles.pitch(), xAxis) * Eigen::AngleAxisf(angles.yaw(), yAxis) };
	}
	inline Mat4f createPerspectiveProjectionMatrix(float fov, float aspect, float near, float far)
	{
		float ctg = 1.0f / tanf(deg2rad(fov * 0.5f));

		math::Mat4f mat;
		mat << (ctg / aspect), 0.0f, 0.0f, 0.0f,
			0.0f, (ctg), 0.0f, 0.0f,
			0.0f, 0.0f, (near / (near - far)), 1.0f,
			0.0f, 0.0f, (-far * near / (near - far)), 0.0f;

		return mat;
	}
	inline void invertRTMatrix(const Mat4f& src, Mat4f& dst)
	{
		dst.block(0, 0, 3, 3) = src.block(0, 0, 3, 3).transpose();
		dst.col(3) = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);

		const Mat3f& R = dst.block(0, 0, 3, 3);
		dst.row(3).head<3>() = src.row(3).head<3>() * -R;
	}
}

#endif
