#include "Scene.h"
#include "PlanePrimitive.h"
#include "SpherePrimitive.h"
#include "Material.h"

Scene::Scene() {
}

Scene::~Scene() {
}

void Scene::InitScene() {
	//ground plane
	Primitive* primitive = new PlanePrimitive(ci::Vec3f(0, 0, 0), ci::Vec3f(0, 1, 0));
	primitive->SetName("Ground Plane");
	primitive->GetMaterial().SetDiffuseColor(ci::ColorA(0.5f, 0.2f, 0.1f));
	primitive->GetMaterial().SetSpecularColor(ci::ColorA(1.0f, 1.0f, 1.0f));
	primitive->GetMaterial().SetDiffuseCoefficient(1.0f);
	primitive->GetMaterial().SetSpecularCoefficient(1.0f);
	m_primitives.push_back(primitive);
	//big sphere
	primitive = new SpherePrimitive(ci::Vec3f(0, 0, 0), 10);
	primitive->SetName("Big Sphere");
	primitive->GetMaterial().SetDiffuseColor(ci::ColorA(0.5f, 0.2f, 0.1f));
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
	//light1
	primitive = new SpherePrimitive(ci::Vec3f(0, 0, 0), 10);
	primitive->SetName("Light 1");
	primitive->GetMaterial().SetDiffuseColor(ci::ColorA(0.5f, 0.2f, 0.1f));
	primitive->SetIsLight(true);
	m_primitives.push_back(primitive);
	//light2
	primitive = new SpherePrimitive(ci::Vec3f(0, 0, 0), 10);
	primitive->SetName("Light 2");
	primitive->GetMaterial().SetDiffuseColor(ci::ColorA(0.5f, 0.2f, 0.1f));
	primitive->SetIsLight(true);
	m_primitives.push_back(primitive);
}