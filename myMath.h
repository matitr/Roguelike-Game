#pragma once
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

















