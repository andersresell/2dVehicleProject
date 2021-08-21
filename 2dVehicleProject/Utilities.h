#pragma once
#include "Vec2d.h"
#include <vector>
#include "FL/fl_draw.H"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>



constexpr double deltaTime = 0.016;

constexpr unsigned int screenWidth{ 1000 };
constexpr unsigned int screenHeight{ 600 };


constexpr unsigned int realScreenWidth{ 60 }; //meter
constexpr double conversionFactor = screenWidth / realScreenWidth;
//constexpr unsigned int realScreenHeight = screenHeight / conversionFactor;

constexpr double carLength = 4;
constexpr double carWidth = 2;
constexpr double wheelRadius = 0.5;
constexpr double wheelWidth = 0.25;

constexpr unsigned int carMass = 1000;
/*
constexpr unsigned int visualCarLength = realCarLength * conversionFactor;
constexpr unsigned int visualCarWidth = realCarWidth * conversionFactor;
constexpr unsigned int VisualWheelRadius = realWheelRadius * conversionFactor;
*/



double deg2rad(int theta);

Vec2d angle2tangent(double angleRad);
//Vec2d angle2normal(double angleRad);

struct KinData { 
	//Kinematic data
	Vec2d x; //position
	Vec2d v; //velocity
	double theta; //angle
	double omega; //angular velocity
	KinData(Vec2d x, Vec2d v, double theta, double omega) : 
		x{x}, v{v}, theta{theta}, omega{omega} {}
	
	//Calculates the kinematic data at a rigid point from itself
	KinData calcOffsetKinData(const Vec2d& offset) const;
};

std::ostream& operator<<(std::ostream& os, const KinData& rhs);

//Finds global coordinates of a point offset from another point on a rigid body
Vec2d calcOffsetPoint(const Vec2d& x, double theta, const Vec2d& localOffset);

Vec2d localToGlobalVec(const Vec2d& localOffset, double theta); // transforms a local vector to its global direction

double calcMoment(const Vec2d& globalForce, const Vec2d& localArm, double theta); //Calculates the moment from a global force on a
//body rotated theta with a localArm defined when theta = 0

struct RecShape { 
	//Contains vertices for drawing 
	Fl_Color c;
	Vec2d loc1, loc2, loc3, loc4; //Local vertices
	RecShape(double Width, double Length, Fl_Color c); //Rectangle centered around centroid
	void drawRectangle(const Vec2d& x, const double theta); //Draws and converts to screen format by conversion factor
};

//Converts a Vec2d point from normal carthesian system to the flipped screen format and scales it 
void convertPointToScreenFormat(Vec2d& x); 

