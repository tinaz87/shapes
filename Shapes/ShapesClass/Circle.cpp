#include <stdafx.h>
#include "Circle.h"
#include <math.h>
#include <algorithm>

PolyCircle::PolyCircle() { this->mPolygonType = CIRCLE; }
PolyCircle::PolyCircle(const Vector2D& iCenterPoint) {
	this->mCenter = iCenterPoint;
	this->mPolygonType = CIRCLE;

	this->mRadius = min(min(iCenterPoint.mXCoordinate, iCenterPoint.mYCoordinate), (int16_t)(Configs::MIN_WIDTH_HEIGHT + rand() % Configs::MAX_WIDTH_HEIGHT));

	this->calcluateVertices();
}

PolyCircle::~PolyCircle() {}
float PolyCircle::getRadius()const {
	return this->mRadius * mScale;
}
void PolyCircle::calcluateVertices() {
	
	this->mTopLeft.mXCoordinate = this->mCenter.mXCoordinate - this->mRadius*this->mScale;
	this->mTopLeft.mYCoordinate = this->mCenter.mYCoordinate - this->mRadius*this->mScale;

	this->mBottomRight.mXCoordinate = this->mCenter.mXCoordinate + this->mRadius*this->mScale;
	this->mBottomRight.mYCoordinate = this->mCenter.mYCoordinate + this->mRadius*this->mScale;

	this->mPointList.clear();

	this->addPoint(this->mTopLeft);
	this->addPoint(Vector2D(this->mTopLeft.mXCoordinate, this->mBottomRight.mYCoordinate));
	this->addPoint(this->mBottomRight);
	this->addPoint(Vector2D(this->mBottomRight.mXCoordinate, this->mTopLeft.mYCoordinate));

}
void PolyCircle::setPivotPoint(const int16_t iCenterX, const int16_t iCenterY) {

	this->mRadius = min( min(iCenterX,iCenterY), (int16_t)(Configs::MIN_WIDTH_HEIGHT + rand() % Configs::MAX_WIDTH_HEIGHT) );

	this->mCenter.mXCoordinate = iCenterX;
	this->mCenter.mYCoordinate = iCenterY;
	

	this->calcluateVertices();
}

bool PolyCircle::Scale(float iFactor) {
	if (iFactor <= 0) return false;
	this->mScale = iFactor;

	this->calcluateVertices();

	return true;
}