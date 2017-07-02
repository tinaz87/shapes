#include <stdafx.h>
#include "Polygon.h"


BasePolygon::BasePolygon():mPolygonType(POLYGON_TYPE::NONE), mScale(1.0)
{
	this->mColor.mRed = rand() % 256;
	this->mColor.mGreen = rand() % 256;
	this->mColor.mBlue = rand() % 256;
}

BasePolygon::~BasePolygon()
{
}
void BasePolygon::setPivotPoint(const int16_t iCenterX, const int16_t iCenterY) {

}
BasePolygon::POLYGON_TYPE BasePolygon::getType()const {
	return this->mPolygonType;
}
void BasePolygon::addPoint(const Vector2D& iPoint) {
	this->mPointList.push_back(iPoint);
}
const BasePolygon::points_list& BasePolygon::getPointList()const {
	return this->mPointList;
}

const Vector2D & BasePolygon::getTopLeft() const
{
	return this->mTopLeft;
}

const Vector2D & BasePolygon::getBottomRight() const
{
	return this->mBottomRight;
}
const Vector2D & BasePolygon::getCenter() const
{
	return this->mCenter;
}
const Color& BasePolygon::getColor() const
{
	return this->mColor;
}

const BasePolygon::points_list& BasePolygon::getEdgesNormal(bool iRecalc)const
{
	if (iRecalc || !this->mEdgesNormal.size()) {
		this->mEdgesNormal.clear();
		int pNumVertices = this->mPointList.size();
		for (int i = 0; i < pNumVertices; ++i) {
			
			Vector2D pPoint1 = this->mPointList[i];
			
			Vector2D pPoint2 = this->mPointList[ ((i + 1 == pNumVertices) ? 0 : i + 1)];
			
			Vector2D pEdge = pPoint1 - pPoint2 ;
			
			Vector2D pNormal(pEdge.mYCoordinate,pEdge.mXCoordinate * -1);

			this->mEdgesNormal.push_back(pNormal);
		}
	}
	return this->mEdgesNormal;
}
