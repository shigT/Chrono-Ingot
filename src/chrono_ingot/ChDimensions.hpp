// Chrono::Ingot
// 


#ifndef CHRONO_INGOT_CHDIMENSIONS_HPP
#define CHRONO_INGOT_CHDIMENSIONS_HPP

#include <chrono/physics/ChBodyEasy.h>

namespace chrono {
namespace ingot {

template <class ChEasyShape>
class ChDimensions {
	static_assert(sizeof(ChEasyShape) == 0, "ChDimensions: Bad template argument");
};


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
class ChDimensions<chrono::ChBodyEasyConvexHull> {
public:
	ChDimensions(std::vector<ChVector<>> points) : m_params(points) {
		auto vshape = std::make_shared<ChTriangleMeshShape>();
		collision::ChConvexHullLibraryWrapper lh;
		lh.ComputeHull(points, vshape->GetMesh());

		ChVector<> baricenter;
		ChMatrix33<> inertia;
		vshape->GetMesh().ComputeMassProperties(true, m_volume, baricenter, inertia);
	}

	auto get_params() const {
		return m_params;
	}

	double get_volume() const {
		return m_volume;
	}

private:
	std::tuple<std::vector<ChVector<>>> m_params;
	double m_volume;
};

/**
* Class defining Dimensions of a convex hull that has auxiliary reference (nodes).
*/
template<>
class ChDimensions<chrono::ChBodyEasyConvexHullAuxRef> : public ChDimensions<ChBodyEasyConvexHull> {
	using ChDimensions<ChBodyEasyConvexHull>::ChDimensions;
};

/**
* Class defining Dimensions of cluster of spheres (positions and radii of each sphere).
*/
template<>
class ChDimensions<chrono::ChBodyEasyClusterOfSpheres> {
public:
	ChDimensions(std::vector<ChVector<>> positions, std::vector<double> radii) : m_params(positions, radii) {
		m_volume = 0.;
		for (const auto& radius : radii) {
			m_volume += (4.0 / 3.0) * CH_C_PI * pow(radius, 3);
		}
	}

	auto get_params() const {
		return m_params;
	}

	double get_volume() const {
		return m_volume;
	}

private:
	std::tuple<std::vector<ChVector<>>, std::vector<double>> m_params;
	double m_volume;
};


} // end namespace ingot
} // end namespace chrono

#endif //CHRONO_INGOT_CHDIMENSIONS_HPP