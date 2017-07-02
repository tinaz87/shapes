#pragma once
#include "Polygon.h"

class PolyRectangle :public BasePolygon {
public:
	PolyRectangle();
	PolyRectangle(const Vector2D& iTopLeft, const Vector2D& iBottomRight);
	virtual void setPivotPoint(const int16_t iCenterX, const int16_t iCenterY);
	virtual ~PolyRectangle();

	virtual bool Scale(float iFactor);

private:
	float mHeight;
	float mWidth;
	void calcluateVertices();

};
