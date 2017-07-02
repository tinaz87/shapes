#pragma once
class BasePolygon;
class Vector2D;
namespace collision_detection{
	bool detectCollision(const BasePolygon* iPoly1, const BasePolygon* iPoly2, float& oOverlap, Vector2D& oMTVector);
}
