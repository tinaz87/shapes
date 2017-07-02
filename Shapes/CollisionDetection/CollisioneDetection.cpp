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
		float getOverlap(const Projection& interval) {  
			// make sure they overlap
			if (this->Overlap(interval)) {
				return min(this->mMax, interval.mMax) - max(this->mMin, interval.mMin);
			}
			return 0;
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
	bool detectCollision(const BasePolygon* iPoly1, const BasePolygon* iPoly2, float& oOverlap, Vector2D& oMTVector) {

		if (iPoly1->getType() != BasePolygon::CIRCLE && iPoly2->getType() != BasePolygon::CIRCLE)
		{
			const BasePolygon::points_list& pAxes1 = iPoly1->getEdgesNormal();
			const BasePolygon::points_list& pAxes2 = iPoly2->getEdgesNormal();
			oOverlap = FLT_MAX;
			Vector2D pSmallest;
			for (int i = 0; i < pAxes1.size(); ++i) {
				const Vector2D& axis = pAxes1[i];
				// project both shapes onto the axis
				Projection p1 = projectShape2Axis(iPoly1, axis);
				Projection p2 = projectShape2Axis(iPoly2, axis);
				// do the projections overlap?
				if (!p1.Overlap(p2)) {
					// then we can guarantee that the shapes do not overlap
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
				// project both shapes onto the axis
				Projection p1 = projectShape2Axis(iPoly1, axis);
				Projection p2 = projectShape2Axis(iPoly2, axis);
				// do the projections overlap?
				if (!p1.Overlap(p2)) {
					// then we can guarantee that the shapes do not overlap
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
		else {
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
			}
			else {
				PolyCircle* pCircle = nullptr;
				const BasePolygon* pNotCircle = iPoly2;
				if (iPoly1->getType() == BasePolygon::CIRCLE)
					pCircle = (PolyCircle*)iPoly1;
				else {
					pCircle = (PolyCircle*)iPoly2;
					pNotCircle = iPoly1;
				}

				const BasePolygon::points_list& pVertices = pNotCircle->getPointList();
				const Vector2D& pCenter = pCircle->getCenter();

				Vector2D pVertex = pVertices.at(pVertices.size() - 1);

				float pRadiusSquared = pCircle->getRadius() *pCircle->getRadius();
				for (int i = 0; i < pVertices.size(); ++i) {


					Vector2D pAxis = pCenter - pVertex;
					float pAxMag = pAxis.Magnitude();
					float pCircleRadius = pCircle->getRadius();

					LogDebug("%02d - Controllo vertice %s, raggio cerchio %f, centro %s", i ,pVertex.toString().c_str(), pCircleRadius, pCenter.toString().c_str());
					LogDebug("Distanza centro-vertice %f", pAxMag);

					if (pAxMag <= pCircleRadius) {						
						LogDebug("vertici vicini");
						return true;
					}
					Vector2D pCurrentVertex = pVertices.at(i);



					//Vector2D pAxis2 = pCenter - pCurrentVertex;

					Vector2D pEdge = pCurrentVertex - pVertex;

					float pEdgeMagSquare = pEdge.Magnitude();
					pEdgeMagSquare *= pEdgeMagSquare;


					//var ap axis= [point[0] - linePoint1[0], point[1] - linePoint1[1]];
					//var ab edge= [linePoint2[0] - linePoint1[0], linePoint2[1] - linePoint1[1]];

					/*function dotProduct2(v1, v2) {
						return (v1[0] * v2[0]) + (v1[1] * v2[1]);
					}

					function scale2(v, s) {
						v[0] * s;
						v[1] * s;
						return v;
					}*/

					float coef = pEdge.dotProduct(pAxis) / pEdgeMagSquare;
					//return[linePoint1[0] + (coef * ab[0]), linePoint1[1] + (coef * ab[1])];

					Vector2D pPointOnEdge(pVertex.mXCoordinate + coef * pEdge.mXCoordinate, pVertex.mYCoordinate + coef * pEdge.mYCoordinate);
					LogDebug("point %s,v1 %s v2 %s", pPointOnEdge.toString().c_str(), pVertex.toString().c_str(), pCurrentVertex.toString().c_str());

					bool isPointOnSegment = false;/*isProjectedPointOnLine([lineX1, lineY1],
						[lineX2, lineY2],
						[projectedPoint[0], projectedPoint[1]]);*/

					isPointOnSegment = pVertex.mXCoordinate < pPointOnEdge.mXCoordinate && pPointOnEdge.mXCoordinate < pCurrentVertex.mXCoordinate;
					isPointOnSegment |= pVertex.mXCoordinate > pPointOnEdge.mXCoordinate && pPointOnEdge.mXCoordinate > pCurrentVertex.mXCoordinate;

					isPointOnSegment |= pVertex.mYCoordinate > pPointOnEdge.mYCoordinate && pPointOnEdge.mYCoordinate > pCurrentVertex.mYCoordinate;
					isPointOnSegment |= pVertex.mYCoordinate < pPointOnEdge.mYCoordinate && pPointOnEdge.mYCoordinate < pCurrentVertex.mYCoordinate;

					if (isPointOnSegment) {
						drawCircle(pPointOnEdge.mXCoordinate, pPointOnEdge.mYCoordinate, 3);

						if (pPointOnEdge.Magnitude() <= pCircleRadius) {
							LogDebug("interezione");
							return true;
						}
					}

					/*
					 //x1 < x < x2
	//y1 < y < y2
	if ((linePoint1[0] < point[0] && point[0] < linePoint2[0]) ||
		(linePoint1[0] > point[0] && point[0] > linePoint2[0]) ||
		(linePoint1[1] < point[1] && point[1] < linePoint2[1]) ||
		(linePoint1[1] > point[1] && point[1] > linePoint2[1])) {
		return true;
	}

	return false;
					*/

					
					/*float pDet = pAxis.mXCoordinate * pAxis2.mYCoordinate - pAxis2.mXCoordinate*pAxis.mYCoordinate;

					float discrimant = pCircleRadius * pCircleRadius * pEdgeMagSquare - pDet * pDet;

					if (discrimant > 0) {
						LogDebug("discriminant %f", discrimant);
						continue;
						return true;
					}*/

					/*
										float pEdgeMagnintude = pEdge.Magnitude();
										if (pEdgeMagnintude)
										{
											float pDotEdgeAxis = pEdge.dotProduct(pAxis); //http://www.chimica-online.it/fisica/prodotto-scalare.htm

											if (pDotEdgeAxis && pDotEdgeAxis <= pEdgeMagnintude * pEdgeMagnintude) {


												Vector2D projection = pVertex + pEdge * (pDotEdgeAxis / (pEdgeMagnintude * pEdgeMagnintude));

												pAxis = projection - pCenter;

												LogDebug("Edge: %s, Mag: %f, Axis: %s, Proj: %s", pEdge.toString().c_str(), pEdgeMagnintude, pAxis.toString().c_str(), projection.toString().c_str());
												if (pAxis.Magnitude() <= pCircle->getRadius())
												{
													LogDebug("pAxis.Magnitude() <= pCircle->getRadius()");
													//return true;
												}
												else
												{
													if (pEdge.mXCoordinate > 0)
													{
														if (pAxis.mYCoordinate > 0)
														{
															LogDebug("x , y > 0");
															//return false;
														}
													}
													else if (pEdge.mXCoordinate < 0)
													{
														if (pAxis.mYCoordinate < 0)
														{
															LogDebug("x , y<0");
															//return false;
														}
													}
													else if (pEdge.mYCoordinate > 0)
													{
														if (pAxis.mXCoordinate < 0)
														{
															LogDebug("y>0 x<0");
															//return false;
														}
													}
													else
													{
														if (pAxis.mXCoordinate > 0)
														{
															LogDebug("x>0");
															//return false;
														}
													}
													LogDebug("inside");
													//return true;
												}


											}


										}

									*/
					pVertex = pCurrentVertex;

				}

				/*
					  float radiusSquared = circle.Radius * circle.Radius;

	Vector vertex = _points[_points.Length - 1];

	Vector circleCenter = circle.Position;

	float nearestDistance = Single.MaxValue;
	bool nearestIsInside = false;
	int nearestVertex = -1;
	bool lastIsInside = false;

	for (int i = 0; i < _points.Length; i++)
	{
	  Vector nextVertex =_points[i];

	  Vector axis = circleCenter - vertex;

	  float distance = axis.LengthSquared() - radiusSquared;

	  if (distance <= 0)
	  {
		return true;
	  }

	  bool isInside = false;

	  Vector edge = nextVertex - vertex;

	  float edgeLengthSquared = edge.LengthSquared();

	  if (edgeLengthSquared != 0)
	  {
		float dot = edge.Dot(axis);

		if (dot >= 0 && dot <= edgeLengthSquared)
		{
		  Vector projection = vertex + (dot / edgeLengthSquared) * edge;

		  axis = projection - circleCenter;

		  if (axis.LengthSquared() <= radiusSquared)
		  {
			return true;
		  }
		  else
		  {
			if (edge.X > 0)
			{
			  if (axis.Y > 0)
			  {
				return false;
			  }
		  }
		  else if (edge.X < 0)
		  {
			if (axis.Y < 0)
			{
			  return false;
			}
		  }
		  else if (edge.Y > 0)
		  {
			if (axis.X < 0)
			{
			  return false;
			}
		  }
		  else
		  {
			if (axis.X > 0)
			{
			  return false;
			}
		  }

		  isInside = true;
		}
	  }
	}

	if (distance < nearestDistance)
	{
	  nearestDistance = distance;
	  nearestIsInside = isInside || lastIsInside;
	  nearestVertex = i;
	}

	  vertex = nextVertex;
	  lastIsInside = isInside;
	}

	if (nearestVertex == 0)
	{
	  return nearestIsInside || lastIsInside;
	}
	else
	{
	  return nearestIsInside;
	}
				*/



				/*
				// Compute vectors
					v0 = C - A
					v1 = B - A
					v2 = P - A

					// Compute dot products
					dot00 = dot(v0, v0)
					dot01 = dot(v0, v1)
					dot02 = dot(v0, v2)
					dot11 = dot(v1, v1)
					dot12 = dot(v1, v2)

					// Compute barycentric coordinates
					invDenom = 1 / (dot00 * dot11 - dot01 * dot01)
					u = (dot11 * dot02 - dot01 * dot12) * invDenom
					v = (dot00 * dot12 - dot01 * dot02) * invDenom

					// Check if point is in triangle
					return (u >= 0) && (v >= 0) && (u + v < 1)

				*/
			}

		}



		return false;
	}
}