/*
 *  Chrono::Ingot
 *      Mass-based rigid body creation for Chrono::Engine
 *
 *  ingot_test.cpp
 */

#include <chrono_ingot/make_body.hpp>

using namespace chrono;
using namespace chrono::ingot;

namespace {
static const double eps = 1.e-10;
}

void ensure_mass(const std::shared_ptr<ChBody> body, const ChMass& mass) {
	assert(abs(body->GetMass() - mass.get_mass()) < eps);
}

void ensure_dens(const std::shared_ptr<ChBody> body, const ChDensity& dens) {
	assert(abs(body->GetDensity() - dens.get_density()) < eps);
}

int main(int , char* []) {
	const ChDensity dens(1000.);
	const ChMass mass(0.5);

	{
		const ChDimensions<ChBodyEasyBox> dim(0.5, 0.5, 0.5);
		ensure_mass(make_body(dim, mass), mass);
		ensure_dens(make_body(dim, dens), dens);
	}

	{
		const ChDimensions<ChBodyEasyCylinder> dim(0.5, 0.5);
		ensure_mass(make_body(dim, mass), mass);
		ensure_dens(make_body(dim, dens), dens);
	}

	{
		const ChDimensions<ChBodyEasySphere> dim(0.5);
		ensure_mass(make_body(dim, mass), mass);
		ensure_dens(make_body(dim, dens), dens);
	}

	{
		const ChDimensions<ChBodyEasyConvexHull> dim({ VNULL, ChVector<>(.5, 0., 0.), ChVector<>(0., .5, 0.), ChVector<>(0., 0., .5) });
		ensure_mass(make_body(dim, mass), mass);
		ensure_dens(make_body(dim, dens), dens);
	}

	{
		const ChDimensions<ChBodyEasyConvexHullAuxRef> dim({ VNULL, ChVector<>(.5, 0., 0.), ChVector<>(0., .5, 0.), ChVector<>(0., 0., .5) });
		ensure_mass(make_body(dim, mass), mass);
		ensure_dens(make_body(dim, dens), dens);
	}

	{
		const ChDimensions<ChBodyEasyClusterOfSpheres> dim({ VNULL, ChVector<>(.5, 0., 0.), ChVector<>(0., .5, 0.), ChVector<>(0., 0., .5) }, {.1, .2, .3, .4});
		ensure_mass(make_body(dim, mass), mass);
		ensure_dens(make_body(dim, dens), dens);
	}

	std::cout << "All assertions succeeded\n";
	return 0;
}
