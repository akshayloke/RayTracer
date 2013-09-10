#include "SpherePrimitive.h"

SpherePrimitive::SpherePrimitive() : Sphere() {
}

SpherePrimitive::SpherePrimitive(const cinder::Vec3f& _center, const float _radius)
	: Sphere(_center, _radius) {
}

SpherePrimitive::~SpherePrimitive() {
}

Primitive::E_INTERSECT_RESULT SpherePrimitive::Intersect(const cinder::Ray& inRay, float& inDist) {
	float a = inRay.getDirection().dot(inRay.getDirection());
	float b = 2 * (inRay.getOrigin() - mCenter).dot(inRay.getDirection());
	float c = (inRay.getOrigin() - mCenter).dot(inRay.getOrigin() - mCenter) - mRadius * mRadius;

	float result[2];
	int intersectResult = cinder::solveQuadratic(a, b, c, result);
	if (intersectResult == 0) {
		return MISS;
	}
	else if (intersectResult == 1) {
		inDist = result[0];
		return HIT;
	}
	else { //(intersectResult = 2)
		if (result[1] < result[0]) {
			float temp = result[0];
			result[0] = result[1];
			result[1] = temp;
		}

		if (result[1] < 0) {
			return MISS;
		}

		if (result[0] * result[1] < 0) {
			return HIT_INSIDE;
		}

		if (result[0] > 0) {
			inDist = result[0];
			return HIT;
		}

		return MISS;
	}
}

ci::Vec3f SpherePrimitive::GetNormal(const ci::Vec3f& inPoint) {
	return (inPoint - mCenter).normalized();
}