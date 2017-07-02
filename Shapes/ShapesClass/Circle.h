#pragma once
#include "Polygon.h"

class PolyCircle :public BasePolygon {
public:
	PolyCircle();
	PolyCircle(const Vector2D& iCenterPoint);
	virtual void setPivotPoint(const int16_t iCenterX, const int16_t iCenterY);
	virtual ~PolyCircle();
	bool Scale(float iFactor);
	float getRadius()const;

private:
	void calcluateVertices();
	float mRadius;
};
