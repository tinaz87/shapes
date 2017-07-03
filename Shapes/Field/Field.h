#pragma once
#include "../ShapesClass/Polygon.h"


class Field {
public:
	Field();
	 ~Field();
	Field(const int16_t iWidth, const int16_t iHeight);
	void addPoly(BasePolygon* iPoly);
	void setWidth(int16_t iWidth);
	void setHeight(int16_t iHeight);
	void cleanField();
	const std::vector<BasePolygon*>& getPolyList()const;
private:
	std::vector<BasePolygon*> mPolyList;
	int16_t mWidth;
	int16_t mHeight;
};