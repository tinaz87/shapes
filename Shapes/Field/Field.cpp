#include <stdafx.h>
#include "Field.h"

Field::Field()
{
}

Field::~Field()
{
	for(auto it= this->mPolyList.begin();it!= this->mPolyList.end();++it){
		delete *it;
	}
	this->mPolyList.clear();
}

Field::Field(const int16_t iWidth, const int16_t iHeight) :mWidth(iWidth), mHeight(iHeight) {}

void Field::addPoly(BasePolygon* iPoly) {
	if (iPoly)
		this->mPolyList.push_back(iPoly);
}

void Field::setWidth(int16_t iWidth)
{
	this->mWidth = iWidth;
}

void Field::setHeight(int16_t iHeight)
{
	this->mHeight = iHeight;
}
const std::vector<BasePolygon*>& Field::getPolyList()const {
	return this->mPolyList;
}