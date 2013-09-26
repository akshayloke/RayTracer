#pragma once

#include <vector>
#include "cinder\Vector.h"
#include "cinder\Camera.h"
#include "cinder\Surface.h"
#include "Primitive.h"

class Scene {
public:
	Scene(const ci::CameraPersp* _cam);
	virtual ~Scene();

	void Setup();
	void RenderGL();
	void Render(ci::Surface8u *surface);
	ci::ColorA Raytrace(const ci::Ray& ray);

protected:

private:
	std::vector<Primitive*> m_primitives;
	const ci::Camera*	m_camera;
	
};