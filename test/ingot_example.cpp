#include <chrono_ingot/make_body.hpp>

int main(int, char*[]){
    using namespace chrono;
    
    // Dimensions of the box.
    // The shape can be other ChBodyEasy such as ChBodyEasyCylinder, ChBodyEasySphere, etc.
    const chrono::ingot::ChDimensions<ChBodyEasyBox> dim(0.5, 0.5, 0.5);
    
    // Mass based creation
    const chrono::ingot::ChMass mass(0.5);
    std::shared_ptr<ChBodyEasyBox> body1 = chrono::ingot::make_body(dim, mass /* [, collide, visual_assets] */);
    
    // Density based creation
    const chrono::ingot::ChDensity dens(1000.);
    std::shared_ptr<ChBodyEasyBox> body2 = chrono::ingot::make_body(dim, dens /* [, collide, visual_assets] */);
}