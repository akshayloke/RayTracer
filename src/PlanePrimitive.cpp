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
	if (abs(denominator) > ci::EPSILON_VALUE) {
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

ci::Vec3f PlanePrimitive::GetNormal(const ci::Vec3f& inPoint) {
	return getNormal();
}

void PlanePrimitive::RenderGL() {
	
}

void PlanePrimitive::AddParams(ci::params::InterfaceGlRef _params) {
	Primitive::AddParams(_params);
	_params->addParam(GetName() + "::Normal", &mNormal, "group=" + GetName() + " label='Normal'");
	_params->addParam(GetName() + "::Distance", &mDistance, "group=" + GetName() + " label='Distance'");
}