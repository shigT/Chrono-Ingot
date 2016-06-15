# Chrono::Ingot
Chrono::Ingot lets you to create objects of arbitrary mass without explicitly giving relevant density in *Chrono::Engine*, an open source physics engine library which is a core module of *[Project Chrono](http://projectchrono.org/)*.This library supports creation of rigid bodies on the following list:
- ChBodyEasyBox
- ChBodyEasyCylinder
- ChBodyEasySphere
- ChBodyEasyConvexHull
- ChBodyEasyConvexHullAuxRef
- ChBodyEasyClusterOfSpheres

**Chrono::Ingot is not a part of Project Chrono. Please take care not to ask Chrono team about this library.**

## Motivation
Chrono::Engine provides easy ways to create rigid bodies of uniform density (ChEasyBox, ChEasyCylinder, etc.).
They are helpful enough when you know certain densities of objects, however things will be a bit troublesome if you want an object with an actual mass; you must calculate a density on your own in such a case.

## Usage

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

## Acknowledgements
This library was made while research activities of Electronic System Control Engineering Laboratory at Muroran Institute of Technology.