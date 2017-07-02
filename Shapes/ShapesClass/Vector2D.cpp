#include <stdafx.h>
#include "Vector2D.h"
#include <math.h>
#include <sstream>

Vector2D::Vector2D():mXCoordinate(-1), mYCoordinate(-1) {}
Vector2D::Vector2D(const float iX, const float iY) :mXCoordinate(iX), mYCoordinate(iY){}

POINT Vector2D::getPoint()
{
	POINT pPoint;
	pPoint.x = this->mXCoordinate;
	pPoint.y = this->mYCoordinate;
	return pPoint;
}


Vector2D Vector2D::operator+(const Vector2D& iOther)const {

	Vector2D pSumVect(this->mXCoordinate + iOther.mXCoordinate, this->mYCoordinate + iOther.mYCoordinate);
	return pSumVect;
}

Vector2D Vector2D::operator-(const Vector2D& iOther)const {

	Vector2D pSumVect(this->mXCoordinate - iOther.mXCoordinate, this->mYCoordinate - iOther.mYCoordinate);
	return pSumVect;
}
Vector2D Vector2D::operator*(float iNum)const {

	Vector2D pVect(this->mXCoordinate*iNum, this->mYCoordinate *iNum);
	return pVect;
}

float Vector2D::Magnitude()const {
	return sqrt(this->mXCoordinate * this->mXCoordinate + this->mYCoordinate*this->mYCoordinate);
}
float Vector2D::dotProduct(const Vector2D & iOther)const
{
	float pResult = this->mXCoordinate * iOther.mXCoordinate + this->mYCoordinate * iOther.mYCoordinate;
	return pResult;
}

std::string Vector2D::toString() const{
	std::stringstream pOut;
	pOut << "X: " << this->mXCoordinate << ", Y: " << this->mYCoordinate;
	return pOut.str();
}