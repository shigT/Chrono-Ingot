// Chrono::Ingot
// 


#ifndef CHRONO_INGOT_CHDIMENSIONS_HPP
#define CHRONO_INGOT_CHDIMENSIONS_HPP

#include <chrono/physics/ChBodyEasy.h>
#include <numeric>

namespace chrono {
namespace ingot {

namespace detail {

class dim_convex_hull_impl {
public:
	dim_convex_hull_impl(const std::vector<ChVector<>>& points) : m_params(points) {
		set_volume();
	}

	dim_convex_hull_impl(std::vector<ChVector<>>&& points) : m_params(points) {
		set_volume();
	}

	virtual ~dim_convex_hull_impl() = default;

	auto get_params() const {
		return m_params;
	}

	double get_volume() const {
		return m_volume;
	}

private:
	std::tuple<std::vector<ChVector<>>> m_params;
	double m_volume;

	void set_volume() {
		auto vshape = std::make_shared<ChTriangleMeshShape>();
		collision::ChConvexHullLibraryWrapper().ComputeHull(std::get<0>(m_params), vshape->GetMesh());
		vshape->GetMesh().ComputeMassProperties(true, m_volume, ChVector<>(), ChMatrix33<>());
	}
};

} // end namespace detail



template <class ChEasyShape>
class ChDimensions {
	static_assert(sizeof(ChEasyShape) == 0, "ChDimensions: Bad template argument");
};

using ChDimensionsEasyBox = ChDimensions<ChBodyEasyBox>;
using ChDimensionsEasyCylinder = ChDimensions<ChBodyEasyCylinder>;
using ChDimensionsEasySphere = ChDimensions<ChBodyEasySphere>;
using ChDimensionsEasyConvexHull = ChDimensions<ChBodyEasyConvexHull>;
using ChDimensionsEasyConvexHullAuxRef = ChDimensions<ChBodyEasyConvexHullAuxRef>;
using ChDimensionsEasyClusterOfSpheres = ChDimensions<ChBodyEasyClusterOfSpheres>;

/**
* Class defining Dimensions of a box (width, depth and height).
*/
template<>
class ChDimensions<chrono::ChBodyEasyBox> {
public:
	ChDimensions(double x, double y, double z) : m_params(x, y, z), m_volume(x * y * z){ }

	auto get_params() const{
		return m_params;
	}

	double get_volume() const{
		return m_volume;
	}

private:
	std::tuple<double, double, double> m_params;
	double m_volume;
};

/**
* Class defining Dimensions of a cylinder (radius and height).
*/
template<>
class ChDimensions<chrono::ChBodyEasyCylinder> {
public:
	ChDimensions(double radius, double height) : m_params(radius, height), m_volume(CH_C_PI * pow(radius, 2) * height) { }

	auto get_params() const {
		return m_params;
	}

	double get_volume() const {
		return m_volume;
	}

private:
	std::tuple<double, double> m_params;
	double m_volume;
};

/**
* Class defining Dimensions of a sphere (radius).
*/
template<>
class ChDimensions<chrono::ChBodyEasySphere> {
public:
	ChDimensions(double radius) : m_params(radius), m_volume( 4. / 3. * CH_C_PI * pow(radius, 3)) { }

	auto get_params() const {
		return m_params;
	}

	double get_volume() const {
		return m_volume;
	}

private:
	std::tuple<double> m_params;
	double m_volume;
};

/**
* Class defining Dimensions of a convex hull (nodes).
*/
template<>
class ChDimensions<chrono::ChBodyEasyConvexHull> : public detail::dim_convex_hull_impl {
public:
	using detail::dim_convex_hull_impl::dim_convex_hull_impl;

};

/**
* Class defining Dimensions of a convex hull that has auxiliary reference (nodes).
*/
template<>
class ChDimensions<chrono::ChBodyEasyConvexHullAuxRef> : public detail::dim_convex_hull_impl {
public:
	using detail::dim_convex_hull_impl::dim_convex_hull_impl;
};

/**
* Class defining Dimensions of cluster of spheres (positions and radii of each sphere).
*/
template<>
class ChDimensions<chrono::ChBodyEasyClusterOfSpheres> {
public:
	ChDimensions(const std::vector<ChVector<>>& positions, const std::vector<double>& radii)
		: m_params(positions, radii)
		, m_volume(get_total_volume(radii.cbegin(), radii.cend())) 
	{ }

	ChDimensions(std::vector<ChVector<>>&& positions, std::vector<double>&& radii)
		: m_params(positions, radii)
		, m_volume(get_total_volume(radii.cbegin(), radii.cend()))
	{ }

	auto get_params() const {
		return m_params;
	}

	double get_volume() const {
		return m_volume;
	}

private:
	std::tuple<std::vector<ChVector<>>, std::vector<double>> m_params;
	double m_volume;

	template<class iter_begin_t, class iter_end_t>
	double get_total_volume(iter_begin_t begin, iter_end_t end) {
		return std::accumulate(
			begin, end, 0.
			, [](double vols, double radius) {
				return vols += (4.0 / 3.0) * CH_C_PI * pow(radius, 3);
			}
		);
	}
};


} // end namespace ingot
} // end namespace chrono

#endif //CHRONO_INGOT_CHDIMENSIONS_HPP