#ifndef RLENVS_TYPES_V2_H
#define RLENVS_TYPES_V2_H

#include "rlenvs/rlenvscpp_config.h"
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>

#ifdef USE_PYTORCH
#include <torch/torch.h>
#endif

#include <string>
#include <cstddef>
#include <vector>


namespace rlenvscpp {

///
/// \brief real_t
///
typedef double real_t;

///
/// \brief float
///
typedef float float_t;

///
/// \brief integer type
///
typedef int int_t;

///
/// \brief long int type
///
typedef long int lint_t;

///
/// \brief uint_t
///
typedef std::size_t uint_t;


template<typename T>
using DynMat = Eigen::MatrixX<T>;

///
/// \brief Dynamic×3 matrix of type double. 
/// 
using RealMat3d = Eigen::Matrix3<real_t>;

using FloatMat3d = Eigen::Matrix3<float_t>;


template<typename T>
using DynVec = Eigen::RowVectorX<T>;

///
/// \brief single precision floating point vector 
///
using FloatVec = DynVec<float_t>;

///
/// \brief double precision floating point vector
///
using RealVec = DynVec<real_t>;

///
/// \brief single precision std::vector
///
using STD_FloatVec = std::vector<float_t>;

///
/// \brief double precision std::vector
///
using STD_RealVec = std::vector<real_t>;

///
/// \brief Column vector. Some maths operations
/// are easier using column vectors rather than DynVec
///
template<typename T>
using ColVec = Eigen::VectorX<T>;


using RealColVec = ColVec<real_t>;
using FoatColVec = ColVec<float_t>;

///

using RealColVec3d = Eigen::Vector3d;
using FloatColVec3d = Eigen::Vector3f;


///
/// \brief A range of double precision floating point values
///
template<uint_t s, uint_t e>
struct IntegralRange
{
	typedef uint_t value_type;
	static constexpr uint_t S = s;
	static constexpr uint_t E = e;
	static constexpr uint_t size = e - s;
};

///
/// \brief A range of double precision floating point values
///
template<real_t s, real_t e>
struct RealRange
{
	typedef real_t value_type;
	static constexpr real_t S = s;
	static constexpr real_t E = e;
	static constexpr real_t size = e - s;
};


///
/// \brief Null placeholder
///
struct Null{};

///
/// \brief Device type
///
enum class DeviceType {INVALID_TYPE=0, CPU=1, GPU=2} ;

}

#endif // TYPES_H

