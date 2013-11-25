#pragma once

#include "Primitive.h"
#include "cinder/Plane.h"

class PlanePrimitive: public Primitive, public cinder::Plane<float> {
public:
	PlanePrimitive();
	PlanePrimitive(const ci::Vec3f& _point, const ci::Vec3f& _normal);
	PlanePrimitive(const ci::Vec3f& _v1, const ci::Vec3f& _v2, const ci::Vec3f& _v3);
	PlanePrimitive(float a, float b, float c, float d);
	virtual ~PlanePrimitive();

	virtual Primitive::E_INTERSECT_RESULT Intersect(const ci::Ray& inRay, float& inDist);
	virtual cinder::Vec3f GetNormal(const ci::Vec3f& inPoint);

	virtual void RenderGL();

protected:
private:
};