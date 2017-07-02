#include <stdafx.h>
#include "Rectangle.h"
#include <algorithm>

PolyRectangle::PolyRectangle() {
	this->mPolygonType = RECTANGLE;
}
PolyRectangle::PolyRectangle(const Vector2D& iTopLeft, const Vector2D& iBottomRight) {
	this->mBottomRight = iBottomRight;
	this->mTopLeft = iTopLeft;
	this->mPolygonType = RECTANGLE;
}
PolyRectangle::~PolyRectangle() {}

void PolyRectangle::calcluateVertices() {

	float pWidth = this->mWidth * mScale;
	float pHeight = this->mHeight * mScale;
	this->mTopLeft.mXCoordinate = max(0, this->mCenter.mXCoordinate - pWidth / 2);
	this->mTopLeft.mYCoordinate = max(0, this->mCenter.mYCoordinate - pHeight / 2);


	this->mBottomRight.mXCoordinate = this->mTopLeft.mXCoordinate + pWidth;
	this->mBottomRight.mYCoordinate = this->mTopLeft.mYCoordinate + pHeight;

	this->mPointList.clear();

	this->addPoint(this->mTopLeft);
	this->addPoint(Vector2D(this->mTopLeft.mXCoordinate, this->mBottomRight.mYCoordinate));
	this->addPoint(this->mBottomRight);
	this->addPoint(Vector2D(this->mBottomRight.mXCoordinate, this->mTopLeft.mYCoordinate));

}


void PolyRectangle::setPivotPoint(const int16_t iCenterX, const int16_t iCenterY) {

	this->mCenter.mXCoordinate = iCenterX;
	this->mCenter.mYCoordinate = iCenterY;


	this->mWidth = BasePolygon::MIN_POINT_DISTANCE + rand() % BasePolygon::MAX_POINT_DISTANCE;
	this->mWidth = min(iCenterX, this->mWidth);
	this->mHeight = BasePolygon::MIN_POINT_DISTANCE + rand() % BasePolygon::MAX_POINT_DISTANCE;
	this->mHeight =  min(iCenterY, this->mHeight);

	this->calcluateVertices();

}


bool PolyRectangle::Scale(float iFactor)
{
	if (iFactor <= 0) return false;

	this->mScale = iFactor;
	
	this->calcluateVertices();

	return true;
}
