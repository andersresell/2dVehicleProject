
#include "Utilities.h"

double deg2rad(int theta) {
	return theta * M_PI / 180;
}

Vec2d angle2tangent(double angleRad) {
	return { -sin(angleRad) , cos(angleRad) };
}

//Vec2d angle2normal(double angleRad) {
//	return { cos(angleRad) , sin(angleRad) };
//}

KinData KinData::calcOffsetKinData(const Vec2d& offset) const {
	return { x + offset, v + offset.cross(omega), theta, omega };
}

std::ostream& operator<<(std::ostream& os, const KinData& rhs) {
	return os << "x = " << rhs.x << " v = " << rhs.v << " theta = " <<
		rhs.theta << " omega = " << rhs.omega;
}

Vec2d calcOffsetPoint(const Vec2d& x, double theta, const Vec2d& localOffset) {
	return x + RotMat2d(theta) * localOffset;
}

Vec2d localToGlobalVec(const Vec2d& localOffset, double theta) {
	return RotMat2d(theta) * localOffset;
}

double calcMoment(const Vec2d& force, const Vec2d& arm, double theta) { 
	return localToGlobalVec(arm, theta).cross(force); 
}

RecShape::RecShape(double Width, double Length, Fl_Color c) : loc1{ Width / 2,-Length / 2 }, 
loc2{Width/2,Length/2}, loc3{-Width/2,Length/2}, loc4{-Width/2,-Length/2}, c{c}
{
}

void RecShape::drawRectangle(const Vec2d& x, const double theta) {
	Vec2d p1{ calcOffsetPoint(x, theta, loc1) };
	Vec2d p2{ calcOffsetPoint(x, theta, loc2) };
	Vec2d p3{ calcOffsetPoint(x, theta, loc3) };
	Vec2d p4{ calcOffsetPoint(x, theta, loc4) };
	convertPointToScreenFormat(p1);
	convertPointToScreenFormat(p2);
	convertPointToScreenFormat(p3);
	convertPointToScreenFormat(p4);
	//using namespace std;
	//cout << p1 << endl;
	fl_color(c);
	fl_begin_polygon();
	fl_polygon(p1.x1, p1.x2, p2.x1, p2.x2, p3.x1, p3.x2, p4.x1, p4.x2);
	fl_end_polygon();
}

void convertPointToScreenFormat(Vec2d& x) {
	x *= conversionFactor;
	x.x2 = screenHeight - x.x2;
}