#pragma once
#include "Vec2d.h"
#include <vector>
#include "FL/fl_draw.H"
#define _USE_MATH_DEFINES
#include <math.h>


constexpr double deltaTime = 0.016;

constexpr unsigned int screenWidth{ 1000 };
constexpr unsigned int screenHeight{ 600 };

constexpr unsigned int carLength = screenWidth / 20;
constexpr unsigned int carWidth = carLength / 2;
constexpr unsigned int wheelRadius = carLength / 8;
constexpr unsigned int wheelWidth = wheelRadius;

double deg2rad(int theta);

Vec2d angle2tangent(double angleRad);
Vec2d angle2normal(double angleRad);

struct KinData { 
	//Kinematic data
	Vec2d x; //position
	Vec2d v; //velocity
	double theta; //angle
	double omega; //angular velocity
	KinData(Vec2d x, Vec2d v, double theta, double omega) : 
		x{x}, v{v}, theta{theta}, omega{omega} {}
	
	//Calculates the kinematic data  at point offset from itself
	KinData calcOffsetKinData(const Vec2d& offset) const;
};

//Finds global coordinates of a point offset from the centroid of a rigid body
Vec2d calcOffsetPoint(const Vec2d& x, double theta, const Vec2d& localOffset);

double calcMoment(const Vec2d& force, const Vec2d& arm);

struct RecShape { 
	//Contains vertices for drawing 
	Fl_Color c;
	Vec2d loc1, loc2, loc3, loc4; //Local vertices
	/*
	RecShape(Vec2d loc1, Vec2d loc2, Vec2d loc3, Vec2d loc4) : loc1{ loc1 }, loc2{ loc2 }, loc3{ loc3 }, loc4{ loc4 },
		c{ FL_BLACK } {}*/
	RecShape(int Width, int Length, Fl_Color c); //Rectangle centered around centroid
	void drawRectangle(const Vec2d& x, const double theta);
};
