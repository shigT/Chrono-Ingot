/*
 *  Chrono::Ingot
 *      Mass-based rigid body creation for Chrono::Engine
 *
 *  make_body.hpp
 */

#ifndef CHRONO_INGOT_MAKE_BODY_HPP
#define CHRONO_INGOT_MAKE_BODY_HPP

#include <chrono_ingot/ChMass.hpp>
#include <chrono_ingot/ChDensity.hpp>
#include <chrono_ingot/ChDimensions.hpp>

namespace chrono {
namespace ingot {

namespace detail{

template<int ...>
struct unpacker { };

template<int N, int ...S>
struct gens : gens<N - 1, N - 1, S...> { };

template<int ...S>
struct gens<0, S...> {
	using type =  unpacker<S...>;
};

template <class ChEasyShape, int ...S>
std::shared_ptr<ChEasyShape> make_body_impl(unpacker<S...>, ChDimensions<ChEasyShape>dimensions, double dens, bool collide, bool visual_asset) {
	return std::make_shared<ChEasyShape>(std::get<S>(dimensions.get_params())..., dens, collide, visual_asset);
}

} // end namespace detail

template <class ChEasyShape> 
std::shared_ptr<ChEasyShape> make_body(ChDimensions<ChEasyShape>dimensions, ChDensity dens, bool collide = false, bool visual_asset = true) {
	return detail::make_body_impl<ChEasyShape>(typename detail::gens<std::tuple_size<decltype(dimensions.get_params())>::value>::type(), dimensions, dens.get_density(), collide, visual_asset);
}

template <class ChEasyShape>
std::shared_ptr<ChEasyShape> make_body(ChDimensions<ChEasyShape>dimensions, ChMass mass, bool collide = false, bool visual_asset = true) {
	return detail::make_body_impl<ChEasyShape>(typename detail::gens<std::tuple_size<decltype(dimensions.get_params())>::value>::type(), dimensions, mass.get_density(dimensions), collide, visual_asset);
}


} // end namespace ingot
} // end namespace chrono


#endif //CHRONO_INGOT_MAKE_BODY_HPP