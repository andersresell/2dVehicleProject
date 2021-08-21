#pragma once

#include <ostream>
#include <math.h>
#include <iomanip> 

struct Vec2d {
	//Two dimensional vector datatype
	Vec2d() : x1{ 0 }, x2{ 0 } {}
	Vec2d(double x1, double x2) : x1{ x1 }, x2{ x2 } {}
	Vec2d(int x1, int x2): x1{double(x1)}, x2{double(x2)} {}
	double x1;
	double x2;
	Vec2d operator+(const Vec2d& rhs) const;
	void operator+=(const Vec2d& rhs);
	Vec2d operator-(const Vec2d& rhs) const;
	Vec2d operator*(double rhs) const;
	Vec2d operator*(const Vec2d& rhs) const; //elementwise multiplication
	void operator*=(double rhs);
	Vec2d operator/(double rhs) const;
	Vec2d cross(double zComp) const;
	double cross(const Vec2d& rhs) const;
	double norm() const;
	double sum() const;
	double dot(const Vec2d& rhs) const;
	friend std::ostream& operator<<(std::ostream& os, const Vec2d& rhs);
};

struct Mat2d {
	double a11, a12, a21, a22;
	Mat2d(double a11, double a12, double a21, double a22) :a11{a11}, a12{a12}, a21{a21}, a22{a22} {}
	Mat2d() {}
	Vec2d operator*(const Vec2d& rhs) const;
	friend std::ostream& operator<<(std::ostream& os, const Mat2d& rhs);
};

struct RotMat2d : public Mat2d {
	RotMat2d(double theta) : Mat2d{cos(theta), -sin(theta), sin(theta), cos(theta)} {}
};