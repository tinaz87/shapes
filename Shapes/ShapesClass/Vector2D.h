#pragma once
#include <stdint.h>
#include <string>

class Vector2D
{
public:
	Vector2D();
	Vector2D(const float iX, const float iY );

	float mXCoordinate;
	float mYCoordinate;

	POINT getPoint();

	Vector2D operator+(const Vector2D& iOther)const;
	Vector2D operator-(const Vector2D& iOther)const;
	Vector2D operator*(float iNum)const;

	float Magnitude()const;
	float dotProduct(const Vector2D& iOther)const;

	std::string toString()const ;
};

