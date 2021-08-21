#pragma once
#include "Utilities.h"
#include "FL/Fl.H"
#include <iostream>
#include <iomanip> 
#include "Car.h"

constexpr double mu{ 0.8 };
constexpr double maxForce = mu * 9.81 * carMass / 4; 
constexpr int wheelMass{ 20 }; //only used for calculating inertia, doesnt contribute to vehicle mass

struct WheelStateVec { 
	double omegaWh;
	Vec2d velocity;
	double theta;
};

class Wheel { 
private:
	const double R; //Wheel radius
	const double wheelWidth;
	const double I; //second moment of inertia
	const Vec2d offset; //Local offset
	//KinData wheelKinData; //at t_n. does not include the steering angle
	//double omegaWh; //Wheel rotation speed at t_n
	WheelStateVec wheelState;
	int steeringAngle; //constant during entire timestep
	double torque; //constant during entire timestep
	Vec2d force; //constant during entire timestep
	RecShape wheelBody;
	double calcTotalAngle(double theta) { return theta + deg2rad(steeringAngle); }
	double calcWheelAcc(double theta, Vec2d force);
public:
	const std::string wheelLoc;
	Wheel(double R, double wheelWidth, Vec2d offset, double theta, std::string wheelLoc);
	void setSteeringAngle(int angle) { steeringAngle = angle; }
	void setTorque(double torqueInput) { torque = torqueInput; }
	void addTorque(double torqueInput) { torque += torqueInput; }
	void setForce(Vec2d inputForce) { force = inputForce; }
	Vec2d getForce() const { return force; }
	void update( double dt, const KinData& vehicleKinData, Vec2d force);
	void drawWheel(Vec2d wheelCenter);
	Vec2d calcForce();
	Vec2d getOffset() const { return offset; }
	void lockWheel() { wheelState.omegaWh = 0; }
	double getWheelRotation() { return wheelState.omegaWh; }

	friend std::ostream& operator<<(std::ostream& os, const Wheel& rhs);
};

Vec2d calcRelativeGroundSpeed(Vec2d v, Vec2d t, double omega, double R);