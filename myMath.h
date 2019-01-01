#pragma once
#ifndef _MYMATH_H
#define _MYMATH_H

#include <utility> 



struct PointFloat {
	float x, y;

	PointFloat() {
		x = 0;
		y = 0;
	}
};

struct PointDouble {
	double x, y;

	PointDouble() {
		x = 0;
		y = 0;
	}
	PointDouble(double _x, double _y) {
		x = _x;
		y = _y;
	}
};

struct PointInt {
	int x, y;

	PointInt() {
		x = 0;
		y = 0;
	}
	PointInt(int _x, int _y) {
		x = _x;
		y = _y;
	}
	PointInt(const PointDouble& pointD) : x((int)pointD.x), y((int)pointD.y) {}
		
	bool const operator== (const PointInt &p) const {
		return x == p.x && y == p.y;
	}
	bool const operator< (const PointInt &p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
};

struct PointInt_cmp {
	bool operator() (PointInt a, PointInt b) const {
		return std::make_pair(a.x, a.y) > std::make_pair(b.x, b.y);
	}
};

class LineSegment {
	double aParam, bParam;
	const PointInt p1, p2;
public:
	double y(double x) {
		return aParam * x + bParam;
	}

	double x(double y) {
		return (y - bParam) / aParam;
	}

	bool checkInserction(int x3, int y3, int x4, int y4) {
		double divider = ((y4 - y3)*(p2.x - p1.x) - (x4 - x3)*(p2.y - p1.y));
		if (divider == 0)
			return false;

		double uA = ((x4 - x3)*(p1.y - y3) - (y4 - y3)*(p1.x - x3)) / divider;
		double uB = ((p2.x - p1.x)*(p1.y - y3) - (p2.y - p1.y)*(p1.x - x3)) / divider;

		if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
			return true;
		return false;
	}

	LineSegment(const PointDouble& p1, const PointDouble& p2) : p1(p1), p2(p2) {
		aParam = (p1.y - p2.y) / (p1.x - p2.x);
		bParam = p1.y - (p1.y - p2.y) * (p1.x) / (p1.x - p2.x);
	}
};

struct RectInt {
	int x = 0, y = 0, w = 0, h = 0;

};















#endif // !_MYMATH_H