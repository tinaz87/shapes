#include <stdafx.h>
#include "ShapeBuilder.h"
#include "../ShapesClass/Polygon.h"
#include "../ShapesClass/Rectangle.h"
#include "../ShapesClass/Circle.h"
#include "../ShapesClass/Triangle.h"
#include <time.h>

namespace shape_builder {
	/*
	iX,iY polygon center coordinate
	*/
	BasePolygon* createPolygon(const int16_t iX, const int16_t iY) {
		
		static int pNow = 0;
		pNow++;

		BasePolygon::POLYGON_TYPE pType =static_cast<BasePolygon::POLYGON_TYPE>((pNow % BasePolygon::POLYGON_COUNT) + 1);
		BasePolygon* pPoly = nullptr;
		switch (pType)
		{
		case BasePolygon::RECTANGLE: {
			pPoly = new PolyRectangle;
			break;
		}
		case BasePolygon::CIRCLE: {
			pPoly = new PolyCircle;
			break;
		}
		case BasePolygon::TRIANGLE: {
			pPoly = new PolyTriangle;
			break;
		}
		default:
			break;
		}


		if (pPoly)
			pPoly->setPivotPoint(iX, iY);

		return pPoly;

	}
}