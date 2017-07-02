#include <stdafx.h>
#include "Circle.h"
#include <math.h>
#include <algorithm>

PolyCircle::PolyCircle() { this->mPolygonType = CIRCLE; }
PolyCircle::PolyCircle(const Vector2D& iCenterPoint) {
	this->mCenter = iCenterPoint;
	this->mPolygonType = CIRCLE;
}

PolyCircle::~PolyCircle() {}
float PolyCircle::getRadius()const {
	return this->mRadius * mScale;
}
void PolyCircle::setPivotPoint(const int16_t iCenterX, const int16_t iCenterY) {

	this->mRadius = min( min(iCenterX,iCenterY), (int16_t)(BasePolygon::MIN_POINT_DISTANCE + rand() % BasePolygon::MAX_POINT_DISTANCE) );


	this->mCenter.mXCoordinate = iCenterX;
	this->mCenter.mYCoordinate = iCenterY;

	this->mTopLeft.mXCoordinate = iCenterX - this->mRadius;//max(0, iCenterX - this->mRadius / 2);
	this->mTopLeft.mYCoordinate = iCenterY - this->mRadius;//max(0, iCenterY - this->mRadius / 2);
	this->mBottomRight.mXCoordinate = iCenterX + this->mRadius;
	this->mBottomRight.mYCoordinate = iCenterY + this->mRadius;
}

bool PolyCircle::Scale(float iFactor) {
	if (iFactor <= 0) return false;
	this->mScale = iFactor;

	this->mTopLeft.mXCoordinate = this->mCenter.mXCoordinate - this->mRadius*this->mScale;//max(0, iCenterX - this->mRadius / 2);
	this->mTopLeft.mYCoordinate = this->mCenter.mYCoordinate - this->mRadius*this->mScale;//max(0, iCenterY - this->mRadius / 2);

	this->mBottomRight.mXCoordinate = this->mCenter.mXCoordinate + this->mRadius*this->mScale;
	this->mBottomRight.mYCoordinate = this->mCenter.mYCoordinate + this->mRadius*this->mScale;
}