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
		inDist = rayOriginToPlanePoint.dot(mNormal) / denominator;
		if (inDist >= 0)
			return HIT;
		else
			return MISS;
	}
	return MISS;
}

void PlanePrimitive::RenderGL() {
	
}
