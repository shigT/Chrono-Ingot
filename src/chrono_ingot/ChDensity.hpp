#ifndef CHRONO_INGOT_CHDENSITY_HPP
#define CHRONO_INGOT_CHDENSITY_HPP

#include <chrono_ingot/ChDimensions.hpp>

namespace chrono {
namespace ingot {

class ChDensity {
public:
	ChDensity(double density) : m_dens(density) { }

	double get_density() const{
		return m_dens;
	}

	template<class ChEasyShape>
	double get_mass(ChDimensions<ChEasyShape> dim) const{
		return m_dens * dim.get_volume();
	}

private:
	double m_dens;
};

}
}

#endif //CHRONO_INGOT_CHDENSITY_HPP