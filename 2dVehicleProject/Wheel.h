#pragma once
#include "Utilities.h"
#include "FL/Fl.H"

constexpr int maxForce = 100; //random
constexpr int wheelMass{ 20 }; //only used for calculating inertia, doesnt contribute to vehicle mass

class Wheel { 
protected:
	const unsigned int R; //Wheel radius
	const unsigned int wheelWidth;
	const double I; //inertia
	const Vec2d offset; //Local offset
	KinData wheelKinData; //does not include the steering angle
	Vec2d force; //Force from ground to wheels
	double omegaWh; //Wheel rotation speed
	double torque; //Applied torque
	int steeringAngle;
	RecShape wheelBody;
	double calcTotalAngle() { return wheelKinData.theta + deg2rad(steeringAngle); }
	Wheel(unsigned int R, unsigned int wheelWidth, Vec2d offset, const KinData& vehicleKinData);
public:
	virtual void userInput() = 0;
	void drawWheel();
	void updateForce();
	void updateWheelState(const KinData& vehicleKinData);//updates kinamtic data and wheel speed
	Vec2d getForce() const { return force; }
	Vec2d getOffset() const { return offset; }
};

class SteeringWheel : public Wheel {
	static const int maxSteeringAngle{ 15 };
public :
	SteeringWheel(unsigned int R, unsigned int wheelWidth, Vec2d offset, const KinData& vehicleKinData);
	void userInput() override final;
};

class DriveWheel : public Wheel {
public:
	DriveWheel(unsigned int R, unsigned int wheelWidth, Vec2d offset, const KinData& vehicleKinData);
	void userInput() override final;
};

Vec2d calcGroundSpeed(Vec2d v, Vec2d t, double omega, int R);