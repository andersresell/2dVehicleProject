
#include "Wheel.h"

double Wheel::calcWheelAcc(double theta, Vec2d force) { //return angular acceleration of the wheel
	return (torque - force.dot(angle2tangent(calcTotalAngle(theta))) * R) / I;
}


Wheel::Wheel(double R, double wheelWidth, Vec2d offset, double theta, std::string wheelLoc) : R{ R }, 
wheelWidth{ wheelWidth }, offset{ offset }, steeringAngle{ 0 }, torque{0}, force{0,0}, wheelLoc{wheelLoc},
I{ 0.5 * wheelMass * R * R }, wheelBody{ wheelWidth , 2 * R , FL_BLACK }
{
	wheelState = {0,{0,0}, theta};
}

void Wheel::update( double dt, const KinData& vehicleKinData, Vec2d force) {
	wheelState.omegaWh += dt * calcWheelAcc(vehicleKinData.theta, force);
	wheelState.speed = vehicleKinData.v + localToGlobalVec(offset, vehicleKinData.theta).cross(vehicleKinData.omega);
	wheelState.theta = vehicleKinData.theta;
}

void Wheel::drawWheel(Vec2d wheelCenter) {
	wheelBody.drawRectangle(wheelCenter, calcTotalAngle(wheelState.theta));
}

Vec2d Wheel::calcForce() {
	Vec2d vGround = calcRelativeGroundSpeed(wheelState.speed, angle2tangent(calcTotalAngle(wheelState.theta)), wheelState.omegaWh, R);
	Vec2d force = vGround * 1000; //2 is a randomly selected number
	if (force.norm() > maxForce) {
		force = vGround / vGround.norm() * maxForce;
	}
	return force;
}


Vec2d calcRelativeGroundSpeed(Vec2d v, Vec2d t, double omega, double R) {
	return { t * (omega * R) - v };
}

std::ostream& operator<<(std::ostream& os, const Wheel& rhs) {//for debuging
	Vec2d f{ rhs.getForce() };
	return os << rhs.wheelLoc << ": f = " << f << " m = " << calcMoment(f, rhs.getOffset(), rhs.wheelState.theta)
		<< " omega = " << rhs.wheelState.omegaWh << " relGrndSpeed = "
		<< calcRelativeGroundSpeed(rhs.wheelState.speed, angle2tangent(rhs.wheelState.theta), rhs.wheelState.omegaWh, rhs.R) << std::endl;
}