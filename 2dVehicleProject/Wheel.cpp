
#include "Wheel.h"

Wheel::Wheel(unsigned int R, unsigned int wheelWidth, Vec2d offset, const KinData& vehicleKinData) : R{ R }, 
wheelWidth{ wheelWidth }, offset{ offset }, omegaWh{ 0 }, steeringAngle{0}, 
 I{0.5 * wheelMass * R * R}, wheelKinData{vehicleKinData.calcOffsetKinData(offset)},
	wheelBody{wheelWidth, 2*R, FL_BLACK}
{

}

void Wheel::drawWheel() {
	wheelBody.drawRectangle(wheelKinData.x, calcTotalAngle());
}

void Wheel::updateForce(){
	Vec2d vGround = calcGroundSpeed(wheelKinData.v, angle2tangent(calcTotalAngle()), omegaWh, R);
	force = vGround * 2; //2 is a randomly selected number
	if (force.abs() > maxForce) {
		force = vGround.norm() * maxForce;
	}
}

void Wheel::updateWheelState(const KinData& vehicleKinData) {
	wheelKinData = vehicleKinData.calcOffsetKinData(offset);
	omegaWh += (torque - force.dot(angle2tangent(calcTotalAngle())) * R) * deltaTime; //explicit euler for the wheel speed
}

SteeringWheel::SteeringWheel(unsigned int R, unsigned int wheelWidth, Vec2d offset, const KinData& vehicleKinData) :
	Wheel(R, wheelWidth, offset, vehicleKinData)
{
}

void SteeringWheel::userInput() {
	if (Fl::event_key(FL_Right)) {
		steeringAngle = maxSteeringAngle;//Simple steering model for now
	}
	else if (Fl::event_key(FL_Left)) {
		steeringAngle = -maxSteeringAngle;
	}
	else {
		steeringAngle = 0;
	}
}

DriveWheel::DriveWheel(unsigned int R, unsigned int wheelWidth, Vec2d offset, const KinData& vehicleKinData) : 
	Wheel(R, wheelWidth, offset, vehicleKinData)
{
}
void DriveWheel::userInput() {
	if(Fl::event_key(FL_Up)) { 
		torque = 100; //simple torque model for now
	}
	else if (Fl::event_key(FL_Down)) {
		torque = -100;
	}
	else {
		torque = 0;
	}
}


Vec2d calcGroundSpeed(Vec2d v, Vec2d t, double omega, int R) {
	return { v - t * (omega * R) };
}

