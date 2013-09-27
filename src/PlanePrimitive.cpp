#include "PlanePrimitive.h"
#include "cinder/gl/gl.h"

PlanePrimitive::PlanePrimitive() : Primitive(), Plane() {
}

PlanePrimitive::PlanePrimitive(const ci::Vec3f& _point, const ci::Vec3f& _normal)
	: Primitive(), Plane(_point, _normal) {
}

PlanePrimitive::~PlanePrimitive() {
}

Primitive::E_INTERSECT_RESULT PlanePrimitive::Intersect(const cinder::Ray& inRay, float& inDist) {
	float denominator = inRay.getDirection().dot(mNormal);
	if (denominator > ci::EPSILON_VALUE) {
		ci::Vec3f rayOriginToPlanePoint = getPoint() - inRay.getOrigin();
		float result = rayOriginToPlanePoint.dot(mNormal) / denominator;
		if (result > 0)
			if (result < inDist) {
				inDist = result;
				return HIT;
			}
			else
				return MISS;
		else
			return MISS;
	}
	return MISS;
}

void PlanePrimitive::RenderGL() {
	
}