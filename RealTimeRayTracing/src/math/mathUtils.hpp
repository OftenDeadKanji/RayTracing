#ifndef __MATH_UTILS_HPP__
#define __MATH_UTILS_HPP__

#include "Eigen/Dense"
#include <cstdint>

namespace math
{
	using Vec2i = Eigen::Matrix<int32_t, 1, 2, Eigen::RowMajor>;

	using Vec3f = Eigen::Matrix<float, 1, 3, Eigen::RowMajor>;
	using Vec4f = Eigen::Matrix<float, 1, 4, Eigen::RowMajor>;

	using Mat4f = Eigen::Matrix<float, 4, 4, Eigen::RowMajor>;



}

#endif