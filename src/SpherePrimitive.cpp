#include "SpherePrimitive.h"
#include "cinder/gl/gl.h"

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
		if (result[0] < inDist) {
			inDist = result[0];
			return HIT;
		}
		else
			return MISS;		
	}
	else { //(intersectResult = 2)
		if (result[1] < result[0]) {
			/*float temp = result[0];
			result[0] = result[1];
			result[1] = temp;*/
			std::swap(result[0], result[1]);
		}

		if (result[1] < 0) {
			return MISS;
		}

		if (result[0] * result[1] < 0) {
			if (result[1] < inDist) {
				inDist = result[1];
				return HIT_INSIDE;
			}
			else
				return MISS;
		}

		if (result[0] > 0) {
			if (result[0] < inDist) {
				inDist = result[0];
				return HIT;
			}
			else
				return MISS;
		}

		return MISS;
	}
}

ci::Vec3f SpherePrimitive::GetNormal(const ci::Vec3f& inPoint) {
	return (inPoint - mCenter).normalized();
}

void SpherePrimitive::RenderGL() {
	ci::gl::color(GetMaterial().GetDiffuseColor());
	ci::gl::drawSphere(mCenter, mRadius);
	glColor3f( 1, 1, 1 );
}

void SpherePrimitive::AddParams(ci::params::InterfaceGlRef _params) {
	Primitive::AddParams(_params);
	_params->addParam(GetName() + "::Center", &mCenter, "group=" + GetName() + " label='Center'");
	_params->addParam(GetName() + "::Radius", &mRadius, "group=" + GetName() + " label='Radius'");
}
