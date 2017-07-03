#pragma once
#include "Polygon.h"

class PolyRectangle :public BasePolygon {
public:
	PolyRectangle();
	virtual void setPivotPoint(const int16_t iCenterX, const int16_t iCenterY);
	virtual ~PolyRectangle();

	virtual bool Scale(float iFactor);

private:
	float mHeight;
	float mWidth;
	void calcluateVertices();

};
