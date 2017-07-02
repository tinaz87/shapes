#include <stdafx.h>
#include <climits>
#include "../ShapesClass/Polygon.h"
#include "../ShapesClass/Circle.h"
#include "CollisionDetection.h"
#include "../main.h"
namespace collision_detection {

	class Projection {
	public:
		Projection() :mMin(0), mMax(0) {}
		Projection(const float iMin, const float iMax) :mMin(iMin), mMax(iMax) {}
		bool Overlap(const Projection& iProj) {
			if (this->mMax > iProj.mMin) {
				return true;
			}

			if (this->mMin > iProj.mMax) {
				return true;
			}

			return false;
		}
	private:
		float mMin;
		float mMax;
	};

	Projection projectShape2Axis(const BasePolygon* iPoly, const Vector2D& iAxis) {

		const BasePolygon::points_list& pVertices = iPoly->getPointList();
		float min = iAxis.dotProduct(pVertices.at(0));
		float max = min;
		for (int i = 1; i < pVertices.size(); ++i) {
			// NOTE: the axis must be normalized to get accurate projections
			float p = iAxis.dotProduct(pVertices.at(i));
			if (p < min) {
				min = p;
			}
			else if (p > max) {
				max = p;
			}
		}
		Projection proj(min, max);
		return proj;
	}
	bool detectCollision(const BasePolygon* iPoly1, const BasePolygon* iPoly2) {

		if (iPoly1->getType() == BasePolygon::CIRCLE && iPoly2->getType() == BasePolygon::CIRCLE)
		{
			PolyCircle* pCircle1 = (PolyCircle*)iPoly1;
			PolyCircle* pCircle2 = (PolyCircle*)iPoly2;

			const Vector2D& c1 = pCircle1->getCenter();
			const Vector2D& c2 = pCircle2->getCenter();
			const Vector2D& v = c1 - c2;

			if (v.Magnitude() < pCircle1->getRadius() + pCircle2->getRadius()) {
				LogDebug("cerchi collidono mag %f ,r1 %f (%s), r2 %f (%s)", v.Magnitude(), pCircle1->getRadius(), c1.toString().c_str(), pCircle2->getRadius(), c2.toString().c_str());
				return true;
			}


		}else {
			const BasePolygon::points_list& pAxes1 = iPoly1->getEdgesNormal();
			const BasePolygon::points_list& pAxes2 = iPoly2->getEdgesNormal();
			oOverlap = FLT_MAX;
			Vector2D pSmallest;
			for (int i = 0; i < pAxes1.size(); ++i) {
				const Vector2D& axis = pAxes1[i];
				
				Projection p1 = projectShape2Axis(iPoly1, axis);
				Projection p2 = projectShape2Axis(iPoly2, axis);
				
				if (!p1.Overlap(p2)) {
					
					return false;
				}
				else {
					float o = p1.getOverlap(p2);
					if (o < oOverlap)
					{
						oOverlap = o;
						oMTVector = axis;
					}
				}
			}

			for (int i = 0; i < pAxes2.size(); ++i) {
				const Vector2D& axis = pAxes2[i];
				
				Projection p1 = projectShape2Axis(iPoly1, axis);
				Projection p2 = projectShape2Axis(iPoly2, axis);
				
				if (!p1.Overlap(p2)) {
					
					return false;
				}
				else {
					float o = p1.getOverlap(p2);
					if (o < oOverlap)
					{
						oOverlap = o;
						oMTVector = axis;
					}
				}
			}

			return true;

		}
	//	else {
	//		if (iPoly1->getType() == BasePolygon::CIRCLE && iPoly2->getType() == BasePolygon::CIRCLE)
	//		{
	//			PolyCircle* pCircle1 = (PolyCircle*)iPoly1;
	//			PolyCircle* pCircle2 = (PolyCircle*)iPoly2;

	//			const Vector2D& c1 = pCircle1->getCenter();
	//			const Vector2D& c2 = pCircle2->getCenter();
	//			const Vector2D& v = c1 - c2;

	//			if (v.Magnitude() < pCircle1->getRadius() + pCircle2->getRadius()) {
	//				LogDebug("cerchi collidono mag %f ,r1 %f (%s), r2 %f (%s)", v.Magnitude(), pCircle1->getRadius(), c1.toString().c_str(), pCircle2->getRadius(), c2.toString().c_str());
	//				return true;
	//			}
	//		}
	//		else {
	//			PolyCircle* pCircle = nullptr;
	//			const BasePolygon* pNotCircle = iPoly2;
	//			if (iPoly1->getType() == BasePolygon::CIRCLE)
	//				pCircle = (PolyCircle*)iPoly1;
	//			else {
	//				pCircle = (PolyCircle*)iPoly2;
	//				pNotCircle = iPoly1;
	//			}

	//			const BasePolygon::points_list& pVertices = pNotCircle->getPointList();
	//			const Vector2D& pCenter = pCircle->getCenter();

	//			Vector2D pVertex = pVertices.at(pVertices.size() - 1);

	//			float pRadiusSquared = pCircle->getRadius() *pCircle->getRadius();
	//			for (int i = 0; i < pVertices.size(); ++i) {


	//				Vector2D pAxis = pCenter - pVertex;
	//				float pAxMag = pAxis.Magnitude();
	//				float pCircleRadius = pCircle->getRadius();

	//				LogDebug("%02d - Controllo vertice %s, raggio cerchio %f, centro %s", i ,pVertex.toString().c_str(), pCircleRadius, pCenter.toString().c_str());
	//				LogDebug("Distanza centro-vertice %f", pAxMag);

	//				if (pAxMag <= pCircleRadius) {						
	//					LogDebug("vertici vicini");
	//					return true;
	//				}
	//				Vector2D pCurrentVertex = pVertices.at(i);



	//				//Vector2D pAxis2 = pCenter - pCurrentVertex;

	//				Vector2D pEdge = pCurrentVertex - pVertex;

	//				float pEdgeMagSquare = pEdge.Magnitude();
	//				pEdgeMagSquare *= pEdgeMagSquare;


	//				float coef = pEdge.dotProduct(pAxis) / pEdgeMagSquare;

	//				Vector2D pPointOnEdge(pVertex.mXCoordinate + coef * pEdge.mXCoordinate, pVertex.mYCoordinate + coef * pEdge.mYCoordinate);
	//				LogDebug("point %s,v1 %s v2 %s", pPointOnEdge.toString().c_str(), pVertex.toString().c_str(), pCurrentVertex.toString().c_str());

	//				bool isPointOnSegment = false;/*isProjectedPointOnLine([lineX1, lineY1],
	//					[lineX2, lineY2],
	//					[projectedPoint[0], projectedPoint[1]]);*/

	//				isPointOnSegment = pVertex.mXCoordinate < pPointOnEdge.mXCoordinate && pPointOnEdge.mXCoordinate < pCurrentVertex.mXCoordinate;
	//				isPointOnSegment |= pVertex.mXCoordinate > pPointOnEdge.mXCoordinate && pPointOnEdge.mXCoordinate > pCurrentVertex.mXCoordinate;

	//				isPointOnSegment |= pVertex.mYCoordinate > pPointOnEdge.mYCoordinate && pPointOnEdge.mYCoordinate > pCurrentVertex.mYCoordinate;
	//				isPointOnSegment |= pVertex.mYCoordinate < pPointOnEdge.mYCoordinate && pPointOnEdge.mYCoordinate < pCurrentVertex.mYCoordinate;

	//				if (isPointOnSegment) {
	//					drawCircle(pPointOnEdge.mXCoordinate, pPointOnEdge.mYCoordinate, 3);

	//					if (pPointOnEdge.Magnitude() <= pCircleRadius) {
	//						LogDebug("interezione");
	//						return true;
	//					}
	//				}


	//				/*
	//									float pEdgeMagnintude = pEdge.Magnitude();
	//									if (pEdgeMagnintude)
	//									{
	//										float pDotEdgeAxis = pEdge.dotProduct(pAxis); //http://www.chimica-online.it/fisica/prodotto-scalare.htm

	//										if (pDotEdgeAxis && pDotEdgeAxis <= pEdgeMagnintude * pEdgeMagnintude) {


	//											Vector2D projection = pVertex + pEdge * (pDotEdgeAxis / (pEdgeMagnintude * pEdgeMagnintude));

	//											pAxis = projection - pCenter;

	//											LogDebug("Edge: %s, Mag: %f, Axis: %s, Proj: %s", pEdge.toString().c_str(), pEdgeMagnintude, pAxis.toString().c_str(), projection.toString().c_str());
	//											if (pAxis.Magnitude() <= pCircle->getRadius())
	//											{
	//												LogDebug("pAxis.Magnitude() <= pCircle->getRadius()");
	//												//return true;
	//											}
	//											else
	//											{
	//												if (pEdge.mXCoordinate > 0)
	//												{
	//													if (pAxis.mYCoordinate > 0)
	//													{
	//														LogDebug("x , y > 0");
	//														//return false;
	//													}
	//												}
	//												else if (pEdge.mXCoordinate < 0)
	//												{
	//													if (pAxis.mYCoordinate < 0)
	//													{
	//														LogDebug("x , y<0");
	//														//return false;
	//													}
	//												}
	//												else if (pEdge.mYCoordinate > 0)
	//												{
	//													if (pAxis.mXCoordinate < 0)
	//													{
	//														LogDebug("y>0 x<0");
	//														//return false;
	//													}
	//												}
	//												else
	//												{
	//													if (pAxis.mXCoordinate > 0)
	//													{
	//														LogDebug("x>0");
	//														//return false;
	//													}
	//												}
	//												LogDebug("inside");
	//												//return true;
	//											}


	//										}


	//									}

	//								*/
	//				pVertex = pCurrentVertex;

	//			}
	//		}

	//	}



		return false;
	}
}