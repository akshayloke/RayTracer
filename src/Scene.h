#pragma once

#include <vector>
#include "cinder\Vector.h"
#include "cinder\Camera.h"
#include "cinder\Surface.h"
#include "cinder\params\Params.h"
#include "Primitive.h"

class Scene {
public:
	Scene(const ci::CameraPersp* _cam);
	virtual ~Scene();

	void Setup(ci::params::InterfaceGlRef _params);
	void RenderGL();
	void Render(ci::Surface8u *surface);
	ci::ColorA Raytrace(const ci::Ray& inRay, int inDepth, float& inDist, const float inRefractIndex);

protected:

private:
	std::vector<Primitive*> m_primitives;
	const ci::Camera*	m_camera;
};