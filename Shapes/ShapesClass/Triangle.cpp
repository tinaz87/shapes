#include <stdafx.h>
#include "Triangle.h"
#include <math.h>
#include <algorithm>

PolyTriangle::PolyTriangle() { this->mPolygonType = TRIANGLE; }
PolyTriangle::PolyTriangle(const Vector2D& iCenterPoint) {
	this->mCenter = iCenterPoint;
	this->mPolygonType = TRIANGLE;
	
	this->mHeight = Configs::MIN_WIDTH_HEIGHT + rand() % Configs::MAX_WIDTH_HEIGHT;;
	this->mWidth = Configs::MIN_WIDTH_HEIGHT + rand() % Configs::MAX_WIDTH_HEIGHT;

	this->calcluateVertices();
}

PolyTriangle::~PolyTriangle() {}

void PolyTriangle::calcluateVertices() {

	Vector2D pPointUp(this->mCenter.mXCoordinate, this->mCenter.mYCoordinate - this->mHeight / 2 * this->mScale);

	Vector2D pPointDR(this->mCenter.mXCoordinate + this->mWidth / 2 * this->mScale, this->mCenter.mYCoordinate + this->mHeight / 2 * this->mScale);

	Vector2D pPointDL(this->mCenter.mXCoordinate - this->mWidth / 2 * this->mScale, this->mCenter.mYCoordinate + this->mHeight / 2 * this->mScale);


	this->mPointList.clear();

	this->addPoint(pPointUp);
	this->addPoint(pPointDR);
	this->addPoint(pPointDL);

}
void PolyTriangle::setPivotPoint(const int16_t iCenterX, const int16_t iCenterY) {


	this->mHeight = Configs::MIN_WIDTH_HEIGHT + rand() % Configs::MAX_WIDTH_HEIGHT;;
	this->mWidth = Configs::MIN_WIDTH_HEIGHT + rand() % Configs::MAX_WIDTH_HEIGHT;


	this->mCenter.mXCoordinate = iCenterX;
	this->mCenter.mYCoordinate = iCenterY;


	this->calcluateVertices();
}

bool PolyTriangle::Scale(float iFactor) {
	if (iFactor <= 0) return false;
	this->mScale = iFactor;

	this->calcluateVertices();

	return true;
}