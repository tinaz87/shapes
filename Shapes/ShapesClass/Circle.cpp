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
void PolyCircle::calcluateVertices() {
	
	this->mTopLeft.mXCoordinate = this->mCenter.mXCoordinate - this->mRadius*this->mScale;//max(0, iCenterX - this->mRadius / 2);
	this->mTopLeft.mYCoordinate = this->mCenter.mYCoordinate - this->mRadius*this->mScale;//max(0, iCenterY - this->mRadius / 2);

	this->mBottomRight.mXCoordinate = this->mCenter.mXCoordinate + this->mRadius*this->mScale;
	this->mBottomRight.mYCoordinate = this->mCenter.mYCoordinate + this->mRadius*this->mScale;

	this->mPointList.clear();

	this->addPoint(this->mTopLeft);
	this->addPoint(Vector2D(this->mTopLeft.mXCoordinate, this->mBottomRight.mYCoordinate));
	this->addPoint(this->mBottomRight);
	this->addPoint(Vector2D(this->mBottomRight.mXCoordinate, this->mTopLeft.mYCoordinate));

}
void PolyCircle::setPivotPoint(const int16_t iCenterX, const int16_t iCenterY) {

	this->mRadius = min( min(iCenterX,iCenterY), (int16_t)(BasePolygon::MIN_POINT_DISTANCE + rand() % BasePolygon::MAX_POINT_DISTANCE) );

	this->mCenter.mXCoordinate = iCenterX;
	this->mCenter.mYCoordinate = iCenterY;
	

	this->calcluateVertices();
}

bool PolyCircle::Scale(float iFactor) {
	if (iFactor <= 0) return false;
	this->mScale = iFactor;

	this->calcluateVertices();
}