
#include "Utilities.h"

double deg2rad(int theta) {
	return theta * M_PI / 180;
}

Vec2d angle2tangent(double angleRad) {
	return { cos(angleRad) , sin(angleRad) };
}

Vec2d angle2normal(double angleRad) {
	return { sin(angleRad) , -cos(angleRad) };
}

KinData KinData::calcOffsetKinData(const Vec2d& offset) const {
	return { x + offset, v + offset.cross(omega), theta, omega };
}

Vec2d calcOffsetPoint(const Vec2d& x, double theta, const Vec2d& localOffset) {
	return x + RotMat2d(theta) * localOffset;
}

double calcMoment(const Vec2d& force, const Vec2d& arm) {return arm.cross(force); }

RecShape::RecShape(int Width, int Length, Fl_Color c) : loc1{ Width / 2,-Length / 2 }, 
loc2{Width/2,Length/2}, loc3{-Width/2,Length/2}, loc4{-Width/2,-Length/2}, c{c}
{
}

void RecShape::drawRectangle(const Vec2d& x, const double theta) {
	Vec2d glob1{ calcOffsetPoint(x, theta, loc1) };
	Vec2d glob2{ calcOffsetPoint(x, theta, loc2) };
	Vec2d glob3{ calcOffsetPoint(x, theta, loc3) };
	Vec2d glob4{ calcOffsetPoint(x, theta, loc4) };
	fl_color(c);
	fl_begin_polygon();
	fl_polygon(glob1.x1, glob1.x2, glob2.x1, glob2.x2, glob3.x1, glob3.x2, glob4.x1, glob4.x2);
	fl_end_polygon();
}