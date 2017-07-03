#pragma once
#include "Polygon.h"


class PolyTriangle :public BasePolygon {
public:
	PolyTriangle();
	PolyTriangle(const Vector2D& iCenterPoint);
	virtual void setPivotPoint(const int16_t iCenterX, const int16_t iCenterY);
	virtual ~PolyTriangle();
	bool Scale(float iFactor);

private:
	void calcluateVertices();
	float mHeight;
	float mWidth;
};

