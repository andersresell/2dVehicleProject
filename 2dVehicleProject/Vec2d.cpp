
#include "Vec2d.h"

std::ostream& operator<<(std::ostream& os, const Vec2d& rhs) {
	return os << "[" << rhs.x1 << ", " << rhs.x2 << "]";
}

Vec2d Vec2d::operator+(const Vec2d& rhs) const {
	return { x1 + rhs.x1, x2 + rhs.x2 };
}

void Vec2d::operator+=(const Vec2d& rhs) {
	x1 += rhs.x1;
	x2 += rhs.x2;
}

Vec2d Vec2d::operator-(const Vec2d& rhs) const {
	return { x1 - rhs.x1, x2 - rhs.x2 };
}

Vec2d Vec2d::operator*(double rhs) const {
	return { x1 * rhs, x2 * rhs };
}

Vec2d Vec2d::operator*(const Vec2d& rhs) const {
	return { x1 * rhs.x1, x2 * rhs.x2 };
}

Vec2d Vec2d::operator/(double rhs) const {
	return { x1 / rhs, x2 / rhs };
}

Vec2d Vec2d::cross(double zComp) const {
	return { -x2 * zComp, x1 * zComp };
}

double Vec2d::cross(const Vec2d& rhs) const {
	// a x b = [x1a*x2b - x2a*x1b]
	return x1 * rhs.x2 - x2 * rhs.x1;
}

double Vec2d::abs() const {
	return sqrt(x1 * x1 + x2 * x2);
}

Vec2d Vec2d::norm() const {
	//
	return *this / this->abs();
}

Vec2d Mat2d::operator*(const Vec2d& rhs) const {
	return { a11 * rhs.x1 + a12 * rhs.x2, a21 * rhs.x1 + a22 * rhs.x2 };
}

double Vec2d::sum() const {
	return x1 + x2;
}
double Vec2d::dot(const Vec2d& rhs) const {
	return x1 * rhs.x1 + x2 * rhs.x2;
}

std::ostream& operator<<(std::ostream& os, const Mat2d& rhs) {
	return os << "[" << rhs.a11 << ", " << rhs.a12 << std::endl
		<< rhs.a21 << ", " << rhs.a22 << "]";
}