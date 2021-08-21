#pragma once
#include "Utilities.h"
#include "Vec2d.h"
#include "FL/Fl_Widget.H"
#include <vector>
#include <memory>
#include <cmath>
#include <iostream>
#include "Engine.h"
#include "Wheel.h"


class Car : public Fl_Widget {
protected:
	Engine engine;
	static const int maxSteeringAngle{ 30 };
	const double M; //Mass
	const double I; //Inertia
	double Length;
	double Width;
	Vec2d Cm; 
	KinData vehicleKinData;
	RecShape carBody;
	std::vector<std::shared_ptr<Wheel>> wheels; // to loop over wheels
	std::shared_ptr<Wheel> frontRight;
	std::shared_ptr<Wheel> frontLeft;
	std::shared_ptr<Wheel> rearRight;
	std::shared_ptr<Wheel> rearLeft;


	void steer();
	virtual void accelerate() = 0; //Defined based on the drivetrain of the car
	void brake();
	void handbrake();
public:
	Car(double M, double Length, double Width, double wheelRadius, double wheelWidth, Vec2d x0, int initialAngle = 0); //Constructing car with Cm in center
	virtual void draw() override final;
};

class RWD_Car : public Car {
private:

public:
	RWD_Car(double M, double Length, double Width, double wheelRadius, double wheelWidth, Vec2d x0, int initialAngle = 0);
	void accelerate() override final;
};

