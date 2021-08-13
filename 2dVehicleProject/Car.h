#pragma once
#include "Utilities.h"
#include "Wheel.h"
#include "FL/Fl_Widget.H"
#include <vector>
#include <memory>


class Car : public Fl_Widget {
protected:
	const double M; //Mass
	const double I; //Inertia
	const int horsePower;
	int Length;
	int Width;
	Vec2d Cm; 
	KinData vehicleKinData;
	RecShape carBody;
	std::vector<std::unique_ptr<Wheel>> wheels;
public:
	Car(double M, int Length, int Width, Vec2d x0); //Constructing car with Cm in center
	virtual void draw() override final;
	//double calcTorque() const; //Calculates the torque from wheelspeeds and horsepower.
};