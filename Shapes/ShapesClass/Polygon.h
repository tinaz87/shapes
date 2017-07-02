#pragma once
#include "Vector2D.h"
#include "Color.h"
#include <vector>

class BasePolygon
{
public:

	enum POLYGON_TYPE{NONE=0,RECTANGLE=1,CIRCLE=2,TRIANGLE=3,POLYGON_COUNT=2};
	typedef std::vector<Vector2D> points_list;
	
	BasePolygon();
	virtual ~BasePolygon();
	virtual void setPivotPoint(const int16_t iCenterX, const int16_t iCenterY) = 0;
	POLYGON_TYPE getType()const;
	const points_list& getPointList()const;
	const Vector2D& getTopLeft()const;
	const Vector2D& getBottomRight()const;
	const Vector2D& getCenter()const;
	const Color& getColor()const;
	const points_list& getEdgesNormal(bool iRecalc = false)const ;
	virtual bool Scale(float iFactor) = 0;

protected:

	void addPoint(const Vector2D& iPoint);
	

	static const int16_t MAX_POINT_DISTANCE = 80;
	static const int16_t MIN_POINT_DISTANCE = 20;


	mutable points_list mEdgesNormal;
	points_list mPointList;
	POLYGON_TYPE mPolygonType;

	Vector2D mCenter;
	Vector2D mTopLeft;
	Vector2D mBottomRight;
	Color mColor;

	float mScale;
};
