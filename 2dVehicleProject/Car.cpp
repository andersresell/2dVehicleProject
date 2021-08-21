
#include "Car.h"

 
Car::Car(double M, double Length, double Width, double wheelRadius, double wheelWidth, Vec2d x0, int initialAngle) : 
	engine{ 300 }, M {M}, Length{ Length }, Width{ Width },
	Cm{ 0, 0 }, vehicleKinData{ x0, Vec2d{0, 0}, deg2rad(initialAngle), 0 }, I{ M / 12 * (Length * Length + Width * Width) },
Fl_Widget{ 10,10,10,10 }, carBody{Width, Length, FL_BLUE}, 
frontRight{ std::make_shared<Wheel>(wheelRadius, wheelWidth, Vec2d{Width * 0.6,Length / 3}, vehicleKinData.theta, "FR")},
frontLeft{ std::make_unique<Wheel>(wheelRadius, wheelWidth, Vec2d{ -Width * 0.6,Length / 3 }, vehicleKinData.theta, "FL")},
rearRight{ std::make_unique<Wheel>(wheelRadius, wheelWidth, Vec2d{ Width * 0.6,-Length / 3 }, vehicleKinData.theta, "RR")},
rearLeft{ std::make_unique<Wheel>(wheelRadius, wheelWidth, Vec2d{ -Width * 0.6,-Length / 3 }, vehicleKinData.theta, "RL")}
{
	wheels = { frontRight,frontLeft,rearRight,rearLeft };
}

void Car::brake() { //The car will oly apply brakes to wheels that has positive wheel 
	if (Fl::event_key(FL_Down)) {
		using namespace std;
		cout << 1;
		double totalBrakeTorque{ -19620 }; //Based on the required force to get -1g retardation if M = 1000kg and wheel radius = 0.5m
		if (frontRight->getWheelRotation() > 0) {
			frontRight->addTorque(totalBrakeTorque * 0.35);
		}
		if (frontLeft->getWheelRotation() > 0) {
			frontLeft->addTorque(totalBrakeTorque * 0.35);
		}
		if (rearRight->getWheelRotation() > 0) {
			rearRight->addTorque(totalBrakeTorque * 0.15);
		}
		if (rearLeft->getWheelRotation() > 0) {
			rearLeft->addTorque(totalBrakeTorque * 0.15);
		}
	}
}


void Car::steer() {
	int steeringAngle;
	if (Fl::event_key(FL_Right)) {
		steeringAngle = -maxSteeringAngle;//Simple steering model for now
	}
	else if (Fl::event_key(FL_Left)) {
		steeringAngle = maxSteeringAngle;
	}
	else {
		steeringAngle = 0;
	}
	frontLeft->setSteeringAngle(steeringAngle);
	frontRight->setSteeringAngle(steeringAngle);
}

void Car::handbrake() {
	if (Fl::event_key(FL_Control_L)) {
		rearRight->lockWheel();
		rearLeft->lockWheel();
	}
}


void Car::draw() {
	using namespace std;

	steer();
	handbrake();
	accelerate();
	brake();
	
	/*
	double torque = 0;
	if (Fl::event_key(FL_Up)) {
		torque = 1000;
	}
	if (Fl::event_key(FL_Down)) {
		torque -= 1000;
	}
	rearLeft->setTorque(torque);
	rearRight->setTorque(torque);*/
	

	Vec2d tmpForce, totalForce{ 0,0 };
	double totalMoment{ 0 };
	for (auto& wheel : wheels) {
		tmpForce = wheel->calcForce();
		wheel->setForce(tmpForce);
		totalForce += tmpForce;
		totalMoment += calcMoment(tmpForce, wheel->getOffset(), vehicleKinData.theta);

	}
	cout << endl;
	vehicleKinData.x += vehicleKinData.v * deltaTime;
	vehicleKinData.v += totalForce * deltaTime / M;
	vehicleKinData.theta = fmod(vehicleKinData.theta + vehicleKinData.omega * deltaTime, 2*M_PI);
	vehicleKinData.omega += totalMoment * deltaTime / I;
	for (auto& wheel : wheels) {
		wheel->update(deltaTime, vehicleKinData, wheel->getForce());
		wheel->drawWheel(calcOffsetPoint(vehicleKinData.x, vehicleKinData.theta, wheel->getOffset()));
		wheel->setTorque(0);
	}
	carBody.drawRectangle(vehicleKinData.x , vehicleKinData.theta);
}


RWD_Car::RWD_Car(double M, double Length, double Width, double wheelRadius, double wheelWidth, Vec2d x0, int initialAngle) : 
	Car( M,Length,Width,wheelRadius,wheelWidth,x0,initialAngle )
{
}

void RWD_Car::accelerate() {
	double totalTorque{ 0 };
	double crankShaftSpeed{ rearLeft->getWheelRotation() + rearRight->getWheelRotation() };
	if (Fl::event_key(FL_Up)) {
		totalTorque = engine.lookupTorque(crankShaftSpeed);
	}
	else if (Fl::event_key(FL_Down)) { 
		if (crankShaftSpeed <= 0 ){ //in the opposite case the brakes will be applied instead
			totalTorque = -0.2*engine.lookupTorque(crankShaftSpeed);
		}
	}
	rearLeft->addTorque(totalTorque / 2);
	rearRight->addTorque(totalTorque / 2);
}