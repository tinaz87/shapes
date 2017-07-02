#pragma once
#include <stdint.h>
class BasePolygon;
namespace shape_builder {
	/*
	iX,iY polygon center coordinate
	*/
	BasePolygon* createPolygon(const int16_t iX, const int16_t iY);
}
