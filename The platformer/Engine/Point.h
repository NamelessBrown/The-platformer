#pragma once

class Point
{
public:
	Point(float x = 0.f, float y = 0.f);
	Point(const Point& p);
	Point operator+(const Point& p) const;
	Point operator-(const Point& p) const;
	Point operator*(float scalar) const;
	Point& operator=(const Point& p);
	Point& operator+=(const Point& p);
	Point& operator-=(const Point& p);
	~Point();
public:
	float x;
	float y;
};

