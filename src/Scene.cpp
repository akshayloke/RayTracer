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
	Primitive* primitive;
	
	//ground plane
	primitive = new PlanePrimitive(ci::Vec3f(0, -50, 0), ci::Vec3f(0, 1, 0));
	primitive->SetName("Ground Plane");
	primitive->GetMaterial().SetDiffuseColor(ci::ColorA(0.1f, 0.2f, 0.3f));
	primitive->GetMaterial().SetSpecularColor(ci::ColorA(1.0f, 1.0f, 1.0f));
	primitive->GetMaterial().SetDiffuseCoefficient(1.0f);
	primitive->GetMaterial().SetSpecularCoefficient(0.0f);
	m_primitives.push_back(primitive);
	//top plane
	primitive = new PlanePrimitive(ci::Vec3f(0, 50, 0), ci::Vec3f(0, -1, 0));
	primitive->SetName("Ground Plane");
	primitive->GetMaterial().SetDiffuseColor(ci::ColorA(1.0f, 0.0f, 0.0f));
	primitive->GetMaterial().SetSpecularColor(ci::ColorA(1.0f, 1.0f, 1.0f));
	primitive->GetMaterial().SetDiffuseCoefficient(1.0f);
	primitive->GetMaterial().SetSpecularCoefficient(0.0f);
	m_primitives.push_back(primitive);

	//side plane
	primitive = new PlanePrimitive(ci::Vec3f(50, 0, 0), ci::Vec3f(-1, 0, 0));
	primitive->SetName("Ground Plane");
	primitive->GetMaterial().SetDiffuseColor(ci::ColorA(0.2f, 0.1f, 0.3f));
	primitive->GetMaterial().SetSpecularColor(ci::ColorA(1.0f, 1.0f, 1.0f));
	primitive->GetMaterial().SetDiffuseCoefficient(1.0f);
	primitive->GetMaterial().SetSpecularCoefficient(0.0f);
	m_primitives.push_back(primitive);
	//side plane
	primitive = new PlanePrimitive(ci::Vec3f(-50, 0, 0), ci::Vec3f(1, 0, 0));
	primitive->SetName("Ground Plane");
	primitive->GetMaterial().SetDiffuseColor(ci::ColorA(0.2f, 0.1f, 0.3f));
	primitive->GetMaterial().SetSpecularColor(ci::ColorA(1.0f, 1.0f, 1.0f));
	primitive->GetMaterial().SetDiffuseCoefficient(1.0f);
	primitive->GetMaterial().SetSpecularCoefficient(0.0f);
	m_primitives.push_back(primitive);

	//side plane
	primitive = new PlanePrimitive(ci::Vec3f(0, 0, 50), ci::Vec3f(0, 0, -1));
	primitive->SetName("Ground Plane");
	primitive->GetMaterial().SetDiffuseColor(ci::ColorA(1.0f, 1.0f, 1.0f));
	primitive->GetMaterial().SetSpecularColor(ci::ColorA(1.0f, 1.0f, 1.0f));
	primitive->GetMaterial().SetDiffuseCoefficient(1.0f);
	primitive->GetMaterial().SetSpecularCoefficient(0.0f);
	m_primitives.push_back(primitive);
	//side plane
	primitive = new PlanePrimitive(ci::Vec3f(0, 0, -50), ci::Vec3f(0, 0, 1));
	primitive->SetName("Ground Plane");
	primitive->GetMaterial().SetDiffuseColor(ci::ColorA(1.0f, 1.0f, 1.0f));
	primitive->GetMaterial().SetSpecularColor(ci::ColorA(1.0f, 1.0f, 1.0f));
	primitive->GetMaterial().SetDiffuseCoefficient(1.0f);
	primitive->GetMaterial().SetSpecularCoefficient(0.0f);
	m_primitives.push_back(primitive);


	//big sphere
	primitive = new SpherePrimitive(ci::Vec3f(5, 5, 0), 3);
	primitive->SetName("Big Sphere");
	primitive->GetMaterial().SetDiffuseColor(ci::ColorA(1.0f, 1.0f, 1.0f));
	primitive->GetMaterial().SetSpecularColor(ci::ColorA(1.0f, 1.0f, 1.0f));
	primitive->GetMaterial().SetDiffuseCoefficient(1.0f);
	primitive->GetMaterial().SetSpecularCoefficient(1.0f);
	primitive->GetMaterial().SetReflectionCoefficient(0.7f);
	m_primitives.push_back(primitive);
	//small sphere
	primitive = new SpherePrimitive(ci::Vec3f(0, 0, 0), 2);
	primitive->SetName("Small Sphere");
	primitive->GetMaterial().SetDiffuseColor(ci::ColorA(0.5f, 0.5f, 0.1f));
	primitive->GetMaterial().SetSpecularColor(ci::ColorA(1.0f, 1.0f, 1.0f));
	primitive->GetMaterial().SetDiffuseCoefficient(1.0f);
	primitive->GetMaterial().SetSpecularCoefficient(1.0f);
	primitive->GetMaterial().SetReflectionCoefficient(0.1f);
	m_primitives.push_back(primitive);
	//light1
	primitive = new SpherePrimitive(ci::Vec3f(10, 10, -10), 1);
	primitive->SetName("Light 1");
	primitive->GetMaterial().SetDiffuseColor(ci::ColorA(1.0f, 1.0f, 1.0f));
	primitive->SetIsLight(true);
	m_primitives.push_back(primitive);
	////light2
	primitive = new SpherePrimitive(ci::Vec3f(-10, 10, -10), 1);
	primitive->SetName("Light 2");
	primitive->GetMaterial().SetDiffuseColor(ci::ColorA(0.7f, 0.7f, 0.7f));
	primitive->SetIsLight(true);
	m_primitives.push_back(primitive);

	//PARAMS
	/*m_params = ci::params::InterfaceGl("RayTracer", Vec2i(200, 200));
	m_params.addParam("Sphere pos", m_primitives[1]->GetName*/
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
	Color8u bgColor(25, 25, 25);
	while (iter.line()) {
		while (iter.pixel()) {
			float inDist = 10000.0f;
			ColorA color = Raytrace(m_camera->generateRay(iter.x()/(float)width, iter.y()/(float)height, aspectRatio), 0, inDist);
			iter.r() = ci::math<float>::clamp(bgColor.r * (1.0f - color.a) + color.r * 255.0f, 0.0f, 255.0f);
			iter.g() = ci::math<float>::clamp(bgColor.g * (1.0f - color.a) + color.g * 255.0f, 0.0f, 255.0f);
			iter.b() = ci::math<float>::clamp(bgColor.b * (1.0f - color.a) + color.b * 255.0f, 0.0f, 255.0f);
		}
		//iter.line();
	}
}

ci::ColorA Scene::Raytrace(const ci::Ray& inRay, int inDepth, float& inDist) {
	if (inDepth > 3)
		return ci::ColorA::black();

	Primitive* hitPrim = NULL;
	for (int i=0; i<m_primitives.size(); i++) {
		Primitive* prim = m_primitives[i];
		Primitive::E_INTERSECT_RESULT result = prim->Intersect(inRay, inDist);
		if (result == Primitive::HIT) {
			hitPrim = prim;
		}
	}

	if (!hitPrim)
		return ci::ColorA::black();

	if (hitPrim->IsLight()) 
		return hitPrim->GetMaterial().GetDiffuseColor();
	else {
		ci::Vec3f hitPoint = inRay.getOrigin() + inRay.getDirection() * inDist;
		ci::ColorA accumColor(0, 0, 0, 0);
		{//shading
			for (int i=0; i<m_primitives.size(); i++) {
				Primitive* prim = m_primitives[i];
				if (prim->IsLight()) {
					Primitive* light = prim;
					//shadow feeler
					float shade = 1.0f;
					ci::Vec3f L = (((SpherePrimitive*)light)->getCenter() - hitPoint).normalized();
					float lightToHitPointDist = (((SpherePrimitive*)light)->getCenter() - hitPoint).length();
					ci::Ray shadowFeelerRay(hitPoint + L * ci::EPSILON_VALUE, L);
					float LDist = 1000.0f;
					for (int j = 0; j<m_primitives.size(); j++) {
						Primitive* primJ = m_primitives[j];
						if (!primJ->IsLight()) {
							Primitive::E_INTERSECT_RESULT result = primJ->Intersect(shadowFeelerRay, LDist);
							if (result == Primitive::HIT && LDist <= lightToHitPointDist) {
								shade = 0.0f;
								break;
							}
						}
					}

					ci::Vec3f N = hitPrim->GetNormal(hitPoint);
					float dotLN = L.dot(N);
					ci::Vec3f R = (L - 2.0f * dotLN * N).normalized();
					ci::Vec3f V = inRay.getDirection().normalized();
					if (dotLN > 0) {
						//calculate diffuse component
						float diffuseC = dotLN * hitPrim->GetMaterial().GetDiffuseCoefficient();
						accumColor += diffuseC 
										* hitPrim->GetMaterial().GetDiffuseColor() 
										* light->GetMaterial().GetDiffuseColor()
										* shade;

						float dotVR = V.dot(R);
						if (dotVR > 0) {
							//calculate specular component
							float specularC = ci::math<float>::pow(dotVR, 20) * hitPrim->GetMaterial().GetSpecularCoefficient();
							accumColor += specularC 
											* hitPrim->GetMaterial().GetSpecularColor() 
											* light->GetMaterial().GetDiffuseColor() 
											* shade;
						}
					}
				}
			}
		}

		{//reflection
			if (hitPrim->GetMaterial().GetReflectionCoefficient() > 0.0f) {
				ci::Vec3f N = hitPrim->GetNormal(hitPoint);
				ci::Vec3f V = inRay.getDirection().normalized();
				float dotVN = V.dot(N);
				ci::Vec3f R = (V - 2.0f * dotVN * N).normalized();
				float reflectDist = 10000.0f;
				ci::ColorA reflectedColor = Raytrace(ci::Ray(hitPoint + R * ci::EPSILON_VALUE * 2, R), inDepth + 1, reflectDist);
				accumColor += reflectedColor * hitPrim->GetMaterial().GetDiffuseColor() * hitPrim->GetMaterial().GetReflectionCoefficient();
			}
		}

		return accumColor;
	}
}