#ifndef CHRONO_INGOT_CHMASS_HPP
#define CHRONO_INGOT_CHMASS_HPP

#include <chrono_ingot/ChDimensions.hpp>

namespace chrono {
namespace ingot {

class ChMass {
public:
	ChMass(double mass) : m_mass(mass){ }

	template <class ChEasyShape>
	double get_density(ChDimensions<ChEasyShape> dimension) {
		return  m_mass / dimension.get_volume();
	}

	double get_mass() const{
		return m_mass;
	}

private:
	double m_mass;
};

}
}

#endif //CHRONO_INGOT_CHMASS_HPP
