#pragma once
#include "Utilities.h"
#include "Wheel.h"
#include "FL/Fl_Widget.H"
#include <vector>
#include <memory>
#include <cmath>
#include <iostream>


class Car : public Fl_Widget {
private:
	static const int maxSteeringAngle{ 30 };
	const double M; //Mass
	const double I; //Inertia
	double Length;
	double Width;
	Vec2d Cm; 
	KinData vehicleKinData;
	RecShape carBody;
	std::shared_ptr<Wheel> frontRight;
	std::shared_ptr<Wheel> frontLeft;
	std::shared_ptr<Wheel> rearRight;
	std::shared_ptr<Wheel> rearLeft;
	std::vector<std::shared_ptr<Wheel>> wheels; // to loop over wheels
	double getTorqueInput();
	int getSteeringInput();
	void handbrake();
public:
	Car(double M, double Length, double Width, double wheelRadius, double wheelWidth, Vec2d x0, int initialAngle = 0); //Constructing car with Cm in center
	virtual void draw() override final;

};

