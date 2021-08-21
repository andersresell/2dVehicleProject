#pragma once


//*This engine is set to deliver a fixed amount of horsepower
//No redline or gears at this point. 
class Engine { 
private:
	//static double inertia; //Inertia of engine components, crankshaft and axles
	double power; // [watt]
public:
	Engine(int horsePower) : power{horsePower * 745.7} {}
	double lookupTorque(double crankshaftSpeed) {
		double torque = power / crankshaftSpeed;
		if (torque < 0 || torque > 5000) {
			torque = 5000;
		}
		return torque;
	}
};