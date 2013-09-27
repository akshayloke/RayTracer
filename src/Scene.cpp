#include "Scene.h"
#include "PlanePrimitive.h"
#include "SpherePrimitive.h"
#include "Material.h"
#include "cinder\gl\Light.h"
#include "cinder\Surface.h"

using namespace ci;

Scene::Scene(const CameraPersp* _cam) : 
	m_camera(_cam) {
}

Scene::~Scene() {
}

void Scene::Setup() {
	//ground plane
	Primitive* primitive = new PlanePrimitive(ci::Vec3f(0, 0, 0), ci::Vec3f(0, 1, 0));
	primitive->SetName("Ground Plane");
	primitive->GetMaterial().SetDiffuseColor(ci::ColorA(0.5f, 0.2f, 0.1f));
	primitive->GetMaterial().SetSpecularColor(ci::ColorA(1.0f, 1.0f, 1.0f));
	primitive->GetMaterial().SetDiffuseCoefficient(1.0f);
	primitive->GetMaterial().SetSpecularCoefficient(1.0f);
	m_primitives.push_back(primitive);
	//big sphere
	primitive = new SpherePrimitive(ci::Vec3f(5, 5, 0), 5);
	primitive->SetName("Big Sphere");
	primitive->GetMaterial().SetDiffuseColor(ci::ColorA(0.5f, 0.2f, 1.0f));
	primitive->GetMaterial().SetSpecularColor(ci::ColorA(1.0f, 1.0f, 1.0f));
	primitive->GetMaterial().SetDiffuseCoefficient(1.0f);
	primitive->GetMaterial().SetSpecularCoefficient(1.0f);
	m_primitives.push_back(primitive);
	//small sphere
	primitive = new SpherePrimitive(ci::Vec3f(0, 0, 0), 5);
	primitive->SetName("Small Sphere");
	primitive->GetMaterial().SetDiffuseColor(ci::ColorA(0.5f, 0.2f, 0.1f));
	primitive->GetMaterial().SetSpecularColor(ci::ColorA(1.0f, 1.0f, 1.0f));
	primitive->GetMaterial().SetDiffuseCoefficient(1.0f);
	primitive->GetMaterial().SetSpecularCoefficient(1.0f);
	m_primitives.push_back(primitive);
	////light1
	//primitive = new SpherePrimitive(ci::Vec3f(0, 0, 0), 10);
	//primitive->SetName("Light 1");
	//primitive->GetMaterial().SetDiffuseColor(ci::ColorA(0.5f, 0.2f, 0.1f));
	//primitive->SetIsLight(true);
	//m_primitives.push_back(primitive);
	////light2
	//primitive = new SpherePrimitive(ci::Vec3f(0, 0, 0), 10);
	//primitive->SetName("Light 2");
	//primitive->GetMaterial().SetDiffuseColor(ci::ColorA(0.5f, 0.2f, 0.1f));
	//primitive->SetIsLight(true);
	//m_primitives.push_back(primitive);
}

void Scene::RenderGL() {
	gl::Light light( gl::Light::DIRECTIONAL, 0 );
	light.setDirection( Vec3f( 1, 1, 1 ).normalized() );
	light.update( *m_camera );
	light.setDiffuse(ci::ColorAf(0, 1, 0));
	light.enable();

	glColor3f( 1, 1, 1 );
	for (int i=0; i<m_primitives.size(); i++) {
		m_primitives[i]->RenderGL();
	}

	light.disable();
}

void Scene::Render(ci::Surface8u *surface) {
	Surface8u::Iter iter = surface->getIter();
	int width = surface->getWidth();
	int height = surface->getHeight();
	float aspectRatio = width / (float)height;
	Color8u bgColor(0, 95, 255);
	while (iter.line()) {
		while (iter.pixel()) {
			float inDist = 10000.0f;
			ColorA color = Raytrace(m_camera->generateRay(iter.x()/(float)width, iter.y()/(float)height, aspectRatio), 0, inDist);
			iter.r() = bgColor.r * (1.0f - color.a) + color.r * 255.0f;
			iter.g() = bgColor.g * (1.0f - color.a) + color.g * 255.0f;
			iter.b() = bgColor.b * (1.0f - color.a) + color.b * 255.0f;
		}
		//iter.line();
	}
}

ci::ColorA Scene::Raytrace(const ci::Ray& inRay, int inDepth, float& inDist) {
	if (inDepth > 2)
		return ci::ColorA::black();

	Primitive* hitPrim = NULL;
	for (int i=0; i<m_primitives.size(); i++) {
		Primitive* prim = m_primitives[i];
		Primitive::E_INTERSECT_RESULT result = prim->Intersect(inRay, inDist);
		if (result != Primitive::MISS) {
			hitPrim = prim;
		}
	}

	if (!hitPrim)
		return ci::ColorA::black();

	if (hitPrim->IsLight()) 
		return ci::ColorA::white();
	else {
		return hitPrim->GetMaterial().GetDiffuseColor();
	}
}