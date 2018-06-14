#pragma once



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
	double x, y;

	PointInt() {
		x = 0;
		y = 0;
	}
	PointInt(int _x, int _y) {
		x = _x;
		y = _y;
	}
};



















