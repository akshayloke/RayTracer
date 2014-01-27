#pragma once

#include "Primitive.h"
#include "cinder/Sphere.h"
#include "cinder\params\Params.h"

class SpherePrimitive: public Primitive, public ci::Sphere {
public:
	SpherePrimitive();
	SpherePrimitive(const cinder::Vec3f& _center, const float _radius);
	virtual ~SpherePrimitive();

	virtual Primitive::E_INTERSECT_RESULT Intersect(const cinder::Ray& inRay, float& inDist);
	virtual cinder::Vec3f GetNormal(const ci::Vec3f& inPoint);

	virtual void RenderGL();
	virtual void AddParams(ci::params::InterfaceGlRef _params);

protected:
private:	
};