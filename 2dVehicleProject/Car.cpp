
#include "Car.h"
Car::Car(double M, int Length, int Width, Vec2d x0) : M{ M }, Length{ Length }, Width{ Width },
Cm{ 0, 0 }, vehicleKinData{ x0, Vec2d{0, 0}, 0, 0 }, I{ M / 12 * (Length * Length + Width * Width) }, 
Fl_Widget{ 10,10,10,10 }, carBody{Width, Length, FL_BLUE}, horsePower{100}
{
	wheels.push_back(std::make_unique<SteeringWheel>( wheelRadius, wheelWidth, Vec2d{Width / 2,Length / 3}, vehicleKinData ));
	wheels.push_back(std::make_unique<SteeringWheel>( wheelRadius, wheelWidth, Vec2d{ -Width / 2,Length / 3 }, vehicleKinData ));
	wheels.push_back(std::make_unique<DriveWheel>( wheelRadius, wheelWidth, Vec2d{ Width / 2,-Length / 3 }, vehicleKinData ));
	wheels.push_back(std::make_unique<DriveWheel>( wheelRadius, wheelWidth, Vec2d{ -Width / 2,-Length / 3 }, vehicleKinData ));
}

void Car::draw() {
	Vec2d totalForce;
	double totalMoment{ 0 };
	for (auto& wheel : wheels) {
		wheel->userInput();
		wheel->updateForce();
		totalForce += wheel->getForce();
		totalMoment += calcMoment(wheel->getForce(), wheel->getOffset());
	}


	for (auto& wheel : wheels) {
		wheel->drawWheel();
	}
	carBody.drawRectangle(vehicleKinData.x, vehicleKinData.theta);
}
/*
double Car::calcTorque() const {

}*/


